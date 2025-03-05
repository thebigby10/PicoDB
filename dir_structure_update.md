### Seperate Headers and Source Files
- Headers (.h) in include/
- Implementations (.cpp) in src/
-Before(Old):
```c++
#include "../src/Database.cpp"
#include "../src/Table.cpp"
#include "../src/String.cpp"
```
After(New):
```
#include "PicoDB/Database.h"
#include "PicoDB/Table.h"
#include "PicoDB/String.h"
```

[Done] ### Organize src/ into subdirectories 
- core/ → Database logic (tables, cells, queries).
- storage/ → File handling & encryption.
- utils/ → General utilities (string, vector, maps).

### Move Tests to tests/
- Each test file tests a specific module.
- Example:
    test_database.cpp → tests Database.cpp
    test_table.cpp → tests Table.cpp

### examples/ Directory
- Contains example programs demonstrating PicoDB usage
API_REFERENCE.md → Documents all functions.
DESIGN_OVERVIEW.md → Explains internal structure.

### Rename Files
- StringVectorConverter.cpp -> CSVParser.cpp
- FileHandler.cpp -> FileManager.cpp

### Rename Methods

### SQL-Like Methods
