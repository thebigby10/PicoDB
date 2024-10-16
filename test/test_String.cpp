#include<iostream>
#include"../src/String.cpp"
#include"../src/Vector.cpp"
using namespace std;


int main(){
	// String csv_data = "apple,__, banana,__, mango \n 10,__,20,__,30 \n 100,__,14,__,9";
	// size_t count;
	// String* d = csv_data.split(',__,',count );
	// for(size_t i=0;i<count;i++) {
	// 	cout<<[i]<<endl;
	// }
	double a = 102.2;
	cout<<toString(a) + String(" Hello!");
	// cout<<str1<<endl;
}