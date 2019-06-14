#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>

using namespace std;

void dumpALL(const map<string, string>& m) {
	if (m.size() != 0) {
		for (auto& h : m) {
				cout << h.first << "/" << h.second << " ";
		}
		cout << endl;
	}
	else cout << "There are no countries in the world" << endl;
}

int main() {
	map<string, string> countries;
	int q;
	cin >> q;
	string command, country, capital, newName, oldName, tmp;

	for (int i = 0; i < q; i++) {
		cin >> command;
		if (command == "CHANGE_CAPITAL") {
			cin >> country >> capital;
			if (countries.count(country) == 1){
				if (countries[country] == capital) {
					cout << "Country " << country << " hasn't changed its capital" << endl;
				}
				else {
					cout << "Country " << country << " has changed its capital from " << countries[country] << " to " << capital << endl;
					countries[country] = capital;
				}
			}
			else {
				countries[country] = capital;
				cout << "Introduce new country " << country << " with capital " << capital << endl;
			}
		}
		else if (command == "RENAME") {
			cin >> oldName >> newName;
			if (oldName != newName && countries.count(newName) == 0 && countries.count(oldName) == 1) {
				cout << "Country " << oldName << " with capital " << countries[oldName] << " has been renamed to " << newName << endl;
				tmp = countries[oldName];
				countries.erase(oldName);
				countries[newName] = tmp;
			}
			else cout << "Incorrect rename, skip" << endl;
		}
		else if (command == "ABOUT") {
			cin >> country;
			if (countries.count(country) == 1) {
				cout << "Country " << country << " has capital " << countries[country] << endl;
			}
			else cout << "Country "<< country << " doesn't exist"<< endl;
		}
		else if (command == "DUMP") {
			dumpALL(countries);
		}
	}
	system("pause");
	return 0;
}