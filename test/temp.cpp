#include <iostream>

#include "../include/PicoDB/String.h"

using namespace std;

int main() {
    String s = "Hello World!";
    String x = "x";
    s = s + x;
    cout<<s<<endl;
    return 0;
}
