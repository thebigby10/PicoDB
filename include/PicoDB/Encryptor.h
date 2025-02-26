#ifndef ENCRYPTOR_H // Include guard start
#define ENCRYPTOR_H

#include <iostream>
#include "Vector.h"
#include "String.h"

using namespace std;

class Encryptor{
private:
    int key;

public:
    Encryptor(int key);

    // Encryption & decryption functions
    String encryptData(String data) const;
    String decryptData(String data) const;
};

#endif
