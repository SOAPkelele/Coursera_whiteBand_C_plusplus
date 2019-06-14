#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int tasksNum(const string& x) {
	int number = 1;
	for (auto c : x) {
		if (c == ' ') number++;
	}
	return number;
}

int main() {
	int q, day, month = 0;
	cin >> q;
	vector<string> tasks;
	vector<int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	tasks.resize(months[month], " ");
	string command, task;

	for (int i = 0; i < q; i++) {
		cin >> command;
		if (command == "ADD") {
			cin >> day >> task;
			if (tasks[day - 1] != " "){
				if (task != " ")
				tasks[day - 1] +=" " + task;
			}
			else tasks[day - 1] = task;
		}
		else if (command == "DUMP") {
			cin >> day;
			if (day > 0 && day <= months[month]) {
				if (tasks[day - 1] != " ") {
					cout << tasksNum(tasks[day - 1]) << " " << tasks[day - 1] << endl;
				}
				else cout << 0 << endl;
			}
		}
		else if (command == "NEXT") {
			if (month != 11) {
				if (months[month + 1] > months[month]) {
					tasks.resize(months[month + 1], " ");
				}
				else {
					for (int i = months[month+1]; i < months[month]; i++) { 
						if (tasks[months[month+1] - 1] != " ") {
							if (tasks[i] != " ")
							tasks[months[month+1] - 1] += " " + tasks[i];
						}
						else tasks[months[month+1] - 1] = tasks[i]; 
					}
					tasks.resize(months[month + 1]);
				}
				month++;
			}
			else {
				month = 0;
			}
		}
	}
	system("pause");
	return 0;
}