#include<iostream>
#include<string>
#include<vector>
#include "Encryptor.h"

int main(){
	string data = "Hello World!";
	Encryptor encryptor(1012);
	string raw_data = encryptor.encryptData(data);
	cout<<raw_data<<endl;
	cout<<encryptor.decryptData(raw_data)<<endl;
}