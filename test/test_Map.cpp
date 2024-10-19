#include<iostream>
#include"../src/Map.cpp"
#include"../src/String.cpp"
using namespace std;

int main(){
	Map<String, int> a;
	a.insert(String("Apple"), 10);
	if( a.contains(String("Apple")) ){
		cout<<a.get("Apple")<<endl;
	}
	return 0;
}