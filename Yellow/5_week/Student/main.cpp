#include <iostream>
#include <string>
#include <vector>

using namespace std;

class People {
public:
	People(const string& name, const string profession)
		: name_(name),
		profession_(profession){}

	virtual void Walk(const string& destination) const = 0;
	
	const	string name_;
	const string profession_;
};

class Student : public People {
public:
		Student(const string& name, const string& favouriteSong) : People(name, "Student"){
			FavouriteSong = favouriteSong;
		}

		void Learn() const{
				cout << "Student: " << name_ << " learns" << endl;
		}

		void Walk(const string& destination) const override {
				cout << "Student: " << name_ << " walks to: " << destination << endl;
		}

		void SingSong() const{
				cout << "Student: " << name_ << " sings a song: " << FavouriteSong << endl;
		}

private:
		string FavouriteSong;
};


class Teacher : public People{
public:
		Teacher(const string& name, const string& subject) : People(name, "Teacher"){
			subject_ = subject;
		}

		void Teach() const{
				cout << "Teacher: " << name_ << " teaches: " << subject_ << endl;
		}

		void Walk(const string& destination) const override {
				cout << "Teacher: " << name_ << " walks to: " << destination << endl;
		}

private:
		string subject_;
};


class Policeman : public People{
public:
		Policeman(const string& name) : People(name, "Policeman"){};

		void Check(const People& p) const{
				cout << "Policeman: " << name_ << " checks " << p.profession_ << ". " << p.profession_
						 << "'s name is: "  << p.name_ << endl; 
		}

		void Walk(const string& destination) const override {
				cout << "Policeman: " << name_ << " walks to: " << destination << endl;
		}
};

void VisitPlaces(const People& t, const vector<string>& places) {
    for (const auto& p : places) {
        t.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
