#include<iostream>
#include"../src/String.cpp"
#include"../src/Vector.cpp"
using namespace std;


int main(){
	String str1 = "Hello";
	String str2 = "World!";
	str2 = str1 + " " +"World!";
	Vector<String> vec_s;
	vec_s.push_back(String("Hello"));
	cout<<vec_s[0];
	// cout<<str1<<endl;
}