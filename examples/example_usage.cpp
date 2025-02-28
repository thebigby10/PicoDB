#include "../include/PicoDB/PicoDB.h"

int main(){
    PicoDB tempdb("example.db","/home/thebigby01/Codes/_github_repos/PicoDB/examples", "admin", "admin", ",;,");
    tempdb.createTable("users", {{"id", "INTEGER"}, {"name", "TEXT"}, {"email", "TEXT"}});
    // tempdb.insert("users", {{"id", "1"}, {"name", "John Doe"}, {"email", "john.doe@example.com"}});


}
