#include "../src/Vector.cpp"
using namespace std;

class student{
private:
	int m_id;
public:
	student(int id){
		this->m_id = id;
	}
	student(){

	}
	int get_id(){
		return m_id;
	}
	void set_id(){
		this->m_id = m_id;
	}
};

int main(){
	Vector<student> s;
	s.push_back(student(10));
	s.push_back(student(100));
	s.add(1,student(50));
	s.push_back()

	Vector<student> b = s;
	Vector<student> c;
	c = b;

	s.erase(0);

	for(int i=0;i<s.get_size();i++){
		cout<<s[i].get_id()<<" ";
	}
	cout<<endl;
	return 0;
}