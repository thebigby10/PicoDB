#include "../../include/PicoDB/Encryptor.h"

Encryptor::Encryptor(int key) : key(key) {}

String Encryptor::encryptData(String data) const{
	String encrypted_data = data;
	for(int i=0;i<data.length();i++){
		encrypted_data[i] = data[i] ^ key;
	}
	return encrypted_data;
}

String Encryptor::decryptData(String data) const{
	String decrypted_data = data;
	for(int i=0;i<data.length();i++){
		decrypted_data[i] = data[i] ^ key;
	}
	return decrypted_data;
}


class Encryptor{
private:
	int key;
public:
	Encryptor(int key){
		this->key = key;
	};
	//Uses basic XOR cipher
	
	
	//FUTURE IMPLEMENTATIOM
	//XOR with a One-Time Pad (OTP)
	//Vigenère Cipher
	//RC4 Stream Cipher

};
