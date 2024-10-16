#include "../src/Vector.cpp"
#include "../src/String.cpp"
using namespace std;

class Student{
private:
	int id;
public:
	Student(int id){
		this->id = id;
	}
	int get_id(){
		return this->id;
	}
};

int main(){
	Vector<Vector<String> >v = {
		{"student_id", "INT", "PRIMARY_KEY", ""},
		{"student_name", "STRING", "NOT_NULL", ""},
		{"cgpa", "INT","DEFAULT 0", }, 
	};
	// v = {10,20,30};
	// cout<<v[1];
	return 0;
}