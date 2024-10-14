#include<iostream>
#include "../src/FileUtils.cpp"
#include "../src/String.cpp"

using namespace std;

int main(){
	String s = "/home/thebigby01/db/StudentDB/student";
	cout<<fileExists(s)<<endl;
	if(fileExists(s)){
		cout<<readFromFile(s)<<endl;
		writeToFile(s, "Helloooo?");
	}
	String data = readFromFile(s);
	data.trim();
	cout<<data<<endl;

}