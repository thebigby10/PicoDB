#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

class FileHandler{
private:
	string file_path;
public:
	string readFile(bool encrypted){
		if(encrypted){
			//decrypt the file and return as string raw data : use encryptor class
		}
		else{
			// directly retrive and return raw data : use encryptro class
		}
	};
	bool writeFile(bool encrypted, string data){
		if(encrypted){
			//encrypt the data and store : use encryptor class
		}
		else{
			// directly store  : use encryptro class
		}
	}
};
