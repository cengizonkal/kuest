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
    int id;
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
            n.text= reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            //load options
            sqlite3_stmt *stmt2;
            sqlite3_prepare_v2(db, "SELECT text, required_skill, dc, success, fail FROM options WHERE narrative_id = ?",
                               -1, &stmt2, nullptr);
            sqlite3_bind_int(stmt2, 1, n.id);
            Option o;
            while (sqlite3_step(stmt2) == SQLITE_ROW) {
                o.text = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 0)));
                o.required_skill = (Skills) sqlite3_column_int(stmt2, 1);
                o.dc = sqlite3_column_int(stmt2, 2);
                o.success = getNarrative(sqlite3_column_int(stmt2, 3));
                o.failure = getNarrative(sqlite3_column_int(stmt2, 4));
                n.options.push_back(o);
            }

            narratives.push_back(n);

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
    Narrative *currentNarrative;
    int skills[6];

    void setCurrentNarrative(Narrative *n) {
        currentNarrative = n;
    }

};


int main() {

    Story story;
    story.loadNarratives();

    Player player;
    player.setCurrentNarrative(story.getNarrative(0));
    player.currentNarrative->print();

    return 0;
}
