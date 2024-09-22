#pragma once

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Encryptor{
private:
	int key;
public:
	Encryptor(int key){
		this->key = key;
	};
	//Uses basic XOR cipher
	string encryptData(string data) const{
		string encrypted_data = data;
		for(int i=0;i<data.size();i++){
			encrypted_data[i] = data[i] ^ key;
		}
		return encrypted_data;
	}
	string decryptData(string data) const{
		string decrypted_data = data;
		for(int i=0;i<data.size();i++){
			decrypted_data[i] = data[i] ^ key;
		}
		return decrypted_data;
	}
	//FUTURE IMPLEMENTATIOM
	//XOR with a One-Time Pad (OTP)
	//Vigenère Cipher
	//RC4 Stream Cipher

};