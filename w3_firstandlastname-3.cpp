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
	Person(const string& first_name, const string& last_name, int year) {
		first_names[year] = first_name;
		last_names[year] = last_name;
		birthyear = year;
	}

	void ChangeFirstName(int year, const string& first_name) {
		if (birthyear <= year) {
			const string cur_name = FindNameByYear(first_names, year);
			if (first_name != cur_name) {
				first_names[year] = first_name;
			}
		}
	}
	
	void ChangeLastName(int year, const string& last_name) {
		if (birthyear <= year) {
			const string cur_name = FindNameByYear(last_names, year);
			if (last_name != cur_name) {
				last_names[year] = last_name;
			}
		}
	}
	
	string GetFullName(int year) const {
		if (birthyear <= year) {
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
		else return "No person";
	}
	
	string GetFullNameWithHistory(int year) const {
		if (birthyear <= year) {
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
			else if (first_name_history.empty() && !last_name_history.empty()) {
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
		else return "No person";
	}

private:
	map<int, string> first_names;
	map<int, string> last_names;
	int birthyear;
};

int main() {
	Person person("Polina", "Sergeeva", 1960);
	for (int year : {1959, 1960}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : {1965, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	system("pause");
	return 0;
}
