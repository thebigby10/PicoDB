void testSelect() {
    PicoDB db("testdb", "/Users/musaddiqrafi/Desktop/codes/3rdSem/SPL project/PicoDB/test/rapidb", "admin", "admin");
    db.createTable("students", {
        {"id", "INT", "PRIMARY_KEY", ""},
        {"name", "STRING", "NOT_NULL", ""}
    });
    db.insertInto("students", {"id", "name"}, {"1", "John Doe"});

    Table result = db.select("students", {"id", "name"}, "");

    if (result.getRowCount() == 1 && std::string(result.getCell(0, 0)) == "1" && std::string(result.getCell(0, 1)) == "John Doe") {
        std::cout << "testSelect passed.\n";
    } else {
        std::cerr << "testSelect failed.\n";
    }
}