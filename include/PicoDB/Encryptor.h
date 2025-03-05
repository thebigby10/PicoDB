#ifndef ENCRYPTOR_H // Include guard start
#define ENCRYPTOR_H
#include<iostream>
#include"Vector.h"
#include"String.h"

using namespace std;

class Encryptor{
private:
	int key;
public:
	Encryptor(int key){
		this->key = key;
	};
	//Uses basic XOR cipher
	String encryptData(String data) const{
		String encrypted_data = data;
		for(int i=0;i<data.length();i++){
			encrypted_data[i] = data[i] ^ key;
		}
		return encrypted_data;
	}
	String decryptData(String data) const{
		String decrypted_data = data;
		for(int i=0;i<data.length();i++){
			decrypted_data[i] = data[i] ^ key;
		}
		return decrypted_data;
	}
	//FUTURE IMPLEMENTATIOM
	//XOR with a One-Time Pad (OTP)
	//Vigenère Cipher
	//RC4 Stream Cipher

};
#endif