#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <locale>
#include <ctype.h>

using namespace std;

string FindNameByYear(const map<int, string>& names, int year) {
	string name;  
	for (const auto& item : names) {
		if (item.first <= year) {
			name = item.second;
		}
		else {
			break;
		}
	}
	return name;
}

string NameHistory(const map<int, string>& names, int year) {
	const string name = FindNameByYear(names, year);
	
	vector<string> history;
	for (const auto& item : names) {
		if (item.first < year) {
			history.push_back(item.second);
		}
		else {
			break;
		}
	}


	string names_history;

	if (history.size() > 0) {
		int i;
		if (history[history.size() - 1] == name) {
			i = history.size() - 2;
		}
		else i = history.size() - 1;

		for (i; i >= 0; i--) {
			if (i != 0) {
				names_history += history[i] + ", ";
			}
			else {
				names_history += history[i];
			}
		}
	}
	return names_history;
}

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		const string cur_name = FindNameByYear(first_names, year);
		if (first_name != cur_name) {
			first_names[year] = first_name;
		}
	}
	
	void ChangeLastName(int year, const string& last_name) {
		const string cur_name = FindNameByYear(last_names, year);
		if (last_name != cur_name) {
			last_names[year] = last_name;
		}
	}
	
	string GetFullName(int year) {
		const string first_name = FindNameByYear(first_names, year);
		const string last_name = FindNameByYear(last_names, year);

		if (first_name.empty() && last_name.empty()) {
			return "Incognito";
		}
		else if (first_name.empty()) {
			return last_name + " with unknown first name";
		}
		else if (last_name.empty()) {
			return first_name + " with unknown last name";
		}
		else {
			return first_name + " " + last_name;
		}
	}
	
	string GetFullNameWithHistory(int year) {
		const string first_name = FindNameByYear(first_names, year);
		const string last_name = FindNameByYear(last_names, year);

		const string first_name_history = NameHistory(first_names, year);
		const string last_name_history = NameHistory(last_names, year);


		if (first_name.empty() && last_name.empty()) {
			return "Incognito";
		}
		else if (first_name.empty()) {
			if (last_name_history.empty()) {
				return last_name + " with unknown first name";
			}
			else {
				return last_name + " (" + last_name_history + ") with unknown first name";
			}
		}
		else if (last_name.empty()) {
			if (first_name_history.empty()) {
				return first_name + " with unknown last name";
			}
			else {
				return first_name + " (" + first_name_history + ") with unknown last name";
			}
		}
		else if (first_name_history.empty() && !last_name_history.empty()){
			return first_name + " " + last_name + " (" + last_name_history + ")";
		}
		else if (!first_name_history.empty() && last_name_history.empty()) {
			return first_name + " (" + first_name_history + ") " + last_name;
		}
		else if (first_name_history.empty() && last_name_history.empty()) {
			return first_name + " " + last_name;
		}
		else {
			return first_name + " (" + first_name_history + ") " + last_name + " (" + last_name_history + ")";
		}
	}

private:
	map<int, string> first_names;
	map<int, string> last_names;
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	cout << person.GetFullNameWithHistory(1990) << endl;

	person.ChangeFirstName(1966, "Pauline");
	cout << person.GetFullNameWithHistory(1966) << endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	cout << person.GetFullNameWithHistory(1967) << endl;

	
	system("pause");
	return 0;
}