#include "../../include/PicoDB/Table.h"

Vector<String> Table::get_Row(){
		return headers;
	}
	//needs to change?
	int Table::get_RowSize(){
		return table_data.get_size();
	}

	// void extract_col_data(Vector<Vector<String>> temp_col_data) {
   //     int num_headers = temp_col_data.get_size();
	// 	for (int i=0; i<num_headers; i++) {
   //         this->headers.push_back(temp_col_data[i][0]);
   //         this->data_types.push_back(temp_col_data[i][1]);
   //         this->constraints.push_back(temp_col_data[i][2]);
   //     }
	// }

	//update table with new data
   void Table::extract_col_data(Vector<Vector<String>> temp_col_data) {
       int num_headers = temp_col_data.get_size();
       for (int i = 0; i < num_headers; ++i) {
           if (temp_col_data[i].get_size() > 0) {
               headers.push_back(temp_col_data[i][0]);
           }
           if (temp_col_data[i].get_size() > 1) {
               data_types.push_back(temp_col_data[i][1]);
           }
           if (temp_col_data[i].get_size() > 2) {
               constraints.push_back(temp_col_data[i][2]);
           }
       }
   }


	// to update table cells
	void Table::updateRecords (Vector<Vector<Cell>> cell_data) {
		this->table_data = cell_data;
	}

	void Table::updateSingleRecord (Vector<Cell> cell_data) {
		this->table_data.push_back(cell_data);
	}

   // Getter for table_name
	String Table::getTableName()   {
   		return table_name;
	}

	// Getter for headers
	Vector<String> Table::getHeaders()   {
		return headers;
	}

	// Getter for data_types
	Vector<String> Table::getDataTypes()   {
		return data_types;
	}

	// Getter for constraints
	Vector<String> Table::getConstraints()   {
		return constraints;
	}

	// Getter for table_data
	Vector<Vector<Cell>> Table::getTableData()   {
		return table_data;
	}

	// set header
	void Table::setHeaders(Vector<String> headers) {
		this->headers = headers;
	}