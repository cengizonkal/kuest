#include "Story.h"

void Story::loadNarratives() {
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
    for (auto &narrative: narratives) {
        sqlite3_stmt *stmt2;
        sqlite3_prepare_v2(db,
                           "SELECT id,text,required_skill,dc,success,fail FROM options where narrative_id = ? order by id",
                           -1, &stmt2, nullptr);
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
