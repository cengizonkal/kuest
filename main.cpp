#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <list>

enum Skills {
    strength,
    dexterity,
    constitution,
    intelligence,
    wisdom,
    charisma
};

class Narrative;

class Option {
public:
    //text to show
    std::string text;
    //required skill
    Skills required_skill;
    int dc; //difficulty class
    //what happens if you succeed
    Narrative *success;
    //what happens if you fail
    Narrative *failure;

    void print() const {
        std::cout << text << std::endl;
    }

};

class Narrative {
public:
    int id = 0;
    std::string text;
    std::vector<Option> options;

    void print() {
        std::cout << text << std::endl;
        //print options
        for (int i = 0; i < options.size(); i++) {
            std::cout << i << ". ";
            options[i].print();
        }


    }

};

class Story {
    //has narrative list
    std::vector<Narrative> narratives;
public:
    void loadNarratives() {
        sqlite3 *db;
        sqlite3_open("kuest.db", &db);


        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db, "SELECT id,narrative FROM narratives order by id", -1, &stmt, nullptr);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Narrative n;
            n.id = sqlite3_column_int(stmt, 0);
            n.text = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            narratives.push_back(n);
        }
        sqlite3_finalize(stmt);


        //load options
        //for each narrative load options
        for (auto & narrative : narratives) {
            sqlite3_stmt *stmt2;
            sqlite3_prepare_v2(db, "SELECT id,text,required_skill,dc,success,fail FROM options where narrative_id = ? order by id", -1, &stmt2, nullptr);
            sqlite3_bind_int(stmt2, 1, narrative.id);
            while (sqlite3_step(stmt2) == SQLITE_ROW) {
                Option o;
                o.text = reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 1));
                o.required_skill = static_cast<Skills>(sqlite3_column_int(stmt2, 2));
                o.dc = sqlite3_column_int(stmt2, 3);
                o.success = &narratives[sqlite3_column_int(stmt2, 4)];
                o.failure = &narratives[sqlite3_column_int(stmt2, 5)];
                narrative.options.push_back(o);
            }
        }


        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    Narrative *getNarrative(int id) {
        return &narratives[id];
    }

//load from database
};

class Player {

public:
    int skills[6] = {1, 2, 3, 4, 5, 6};

    Narrative *currentNarrative;
    void setCurrentNarrative(Narrative *n) {
        currentNarrative = n;
    }

    void choose(int option) {
        //check if option is valid
        if (option < 0 || option >= currentNarrative->options.size()) {
            std::cout << "Invalid option" << std::endl;
            return;
        }
        //check if skill is high enough
        if (skills[currentNarrative->options[option].required_skill] >= currentNarrative->options[option].dc) {
            //success
            currentNarrative = currentNarrative->options[option].success;
        } else {
            //failure
            currentNarrative = currentNarrative->options[option].failure;
        }

    }

};


int main() {

    Story story;
    story.loadNarratives();

    Player player;
    player.setCurrentNarrative(story.getNarrative(0));
    while (!player.currentNarrative->options.empty()) {
        player.currentNarrative->print();
        int choice;
        std::cin >> choice;
        player.choose(choice);
    }


    return 0;
}
