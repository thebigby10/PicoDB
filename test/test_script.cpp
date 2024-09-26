#include<iostream>
#include<string>
#include<vector>
#include "../src/Encryption.cpp"
#include "../src/FileHandler.cpp"

int main(){
	string data = "Hello World!";
	Encryption encryption(1012);
	string raw_data = encryption.encryptData(data);

	FileHandler filehandler("stored_data.txt");
	filehandler.writeToFile(raw_data);
	filehandler.readFromFile();
	cout<<encryption.decryptData(raw_data)<<endl;
}