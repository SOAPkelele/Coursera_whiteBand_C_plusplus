#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <locale>
#include <ctype.h>

using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string& first_name){
		// добавить факт изменения имени на first_name в год year
		fnamechanges[year] = first_name;
	}

	void ChangeLastName(int year, const string& last_name) {
		// добавить факт изменения фамилии на last_name в год year
		lnamechanges[year] = last_name;
	}

	string findFirstName(int year) {
		if (fnamechanges.count(year) == 1) {
			string firstname = fnamechanges[year];
			return firstname;
		}
		else { 
			int diff = year, y, ifexist = 0;
			for (const auto& i : fnamechanges) {
				if (i.first < year) {
					ifexist++;
					if ((year - i.first) < diff) {
						diff = year - i.first;
						y = i.first;
					}
				}
			}
			string firstname = fnamechanges[y];
			return firstname;
		}
	}

	string findLastName(int year) {
		if (lnamechanges.count(year) == 1) {
			string lastname = lnamechanges[year];
			return lastname;
		}
		else {
			int diff = year, y;
			for (const auto& i : lnamechanges) {
				if (i.first < year) {
					if ((year - i.first) < diff) {
						diff = year - i.first;
						y = i.first;
					}
				}
			}
			string lastname = lnamechanges[y];
			return lastname;
		}
	}
	
	string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
		int iffirstexist = 0, iflastexist = 0;
		for (const auto& i : fnamechanges) {
			if (i.first <= year) {
				iffirstexist++;
				break;
			}
		}

		for (const auto& i : lnamechanges) {
			if (i.first <= year) {
				iflastexist++;
				break;
			}
		}

		if (iffirstexist == 0 && iflastexist == 0) {
			return "Incognito"; 
		}
		else if (iffirstexist > 0 && iflastexist == 0) {
			return findFirstName(year) + " with unknown last name";
		}
		else if (iflastexist > 0 && iffirstexist == 0) {
			return findLastName(year) + " with unknown first name";
		}
		else {
			return findFirstName(year) + ' ' + findLastName(year);
		}
	}

private:
	map <int, string> fnamechanges;
	map <int, string> lnamechanges;
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	system("pause");
	return 0;
}


