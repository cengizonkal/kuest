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
    int id{};
    //text to show
    std::string text{};
    //has options
    std::vector<Option> options;

    void print() {
        std::cout << text << std::endl;
        //print options
        for (auto &option: options) {
            option.print();
        }
    }

};

class Story {
    //has narrative list
    std::list<Narrative> narratives;

    void loadNarratives() {
        sqlite3 *db;
        sqlite3_open("story.db", &db);
        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db, "SELECT id,text FROM narrative", -1, &stmt, NULL);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Narrative n;
            n.id = sqlite3_column_int(stmt, 1);
            n.text = (char *) sqlite3_column_text(stmt, 2);
            //load options
            sqlite3_stmt *stmt2;
            sqlite3_prepare_v2(db, "SELECT text,required_skill,dc,success,failure FROM option WHERE narrative_id = ?", -1, &stmt2, NULL);

            narratives.push_back(n);

        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

//load from database
};

class Player {
    //current narrative
    Narrative *narrative;
    //skills
    int skills[6];

};


int main() {

    return 0;
}
