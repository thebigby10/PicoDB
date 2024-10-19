# PicoDB
![Version](https://img.shields.io/badge/version-1.0.0-brightgreen) (proposed)



![C++](https://img.shields.io/badge/language-C%2B%2B-blue)
![CSV](https://img.shields.io/badge/data-CSV-orange)
![CMake](https://img.shields.io/badge/build-CMake-brightgreen)




PicoDB is a lightweight SQL simulation library built in C++ that uses CSV files to store and manage data. It supports basic SQL operations, allowing users to interact with data as if using a traditional SQL database, while leveraging CSV as the underlying storage mechanism.

---

## Features

- **Data Storage with CSV**: Simulates SQL databases using CSV files to store data.


- **Encryption**: Supports XOR cipher for basic encryption of data.


- **Basic SQL Operations**:


  - **SELECT, INSERT, UPDATE, DELETE**: Perform standard SQL operations.

  - **CREATE, ALTER, DROP TABLE**: Manage table schemas.
  
  - **JOIN Operations**: Basic INNER JOIN support.

  - **Primary & Foreign Keys**: Define relationships between tables.

  - **Aggregate Functions**: COUNT, SUM, AVG, MIN, MAX.

  - **Sorting & Filtering**: ORDER BY and WHERE clauses.

  - **Functions**: String, numeric, and date functions.



- **NoSQL Functionality**: Basic CRUD operations for simpler data manipulation.


- **Compression & Encryption**: Advanced algorithms for efficient storage and secure data management.

## Using PicoDB

1. **Create a database**:

    ```cpp
    Database db("studentdb", "/path/to/csv/files/", true); // true for encryption
    ```

2. **Create a table**:

    ```sql
    CREATE TABLE students (id INT, name VARCHAR, age INT);
    ```

3. **Insert data**:

    ```sql
    INSERT INTO students (id, name, age) VALUES (1, 'John Doe', 20);
    ```

4. **Query data**:

    ```sql
    SELECT * FROM students WHERE age > 18;
    ```

### Advanced Usage

- **Joins**: Perform inner joins to combine tables on a common key.
  
    ```sql
    SELECT students.name, courses.name
    FROM students
    INNER JOIN courses ON students.id = courses.student_id;
    ```

## Project Structure

Here is the proposed basic Project Structure. We are planning to update it over time.

```plaintext
/picoDB/
├── CMakeLists.txt      	# CMake build configuration
├── include/            	# Public headers
├── src/                	# Library implementation
├── test/               	# Unit tests
├── examples/           	# Example usage
├── docs/               	# Documentation
└── README.md           	# Project overview
 ``` 
 
## Here is the draw.io diagram for our project (rough)
![alt text](image.png)

