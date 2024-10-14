#include<iostream>
#include "../src/FileUtils.cpp"
#include "../src/String.cpp"

using namespace std;

int main(){
	String s = "/home/thebigby01/db/StudentDB/studentt";
	cout<<fileExists(s)<<endl;
	if(!fileExists(s)){
		createFile(s);
		cout<<readFromFile(s)<<endl;
		writeToFile(s, "Helloooo?");
	}
	String data = readFromFile(s);
	data.trim();
	cout<<data<<endl;

}