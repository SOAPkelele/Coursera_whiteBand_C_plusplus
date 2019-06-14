#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <sstream>
#include <ctype.h>

using namespace std;

class Date {
public:
	Date() { year = 0; month = 1; day = 1; }
	Date(int new_year, int new_month, int new_day) {
		if (new_month < 1 || new_month >12) {
			throw invalid_argument("Month value is invalid: " + to_string(new_month));
		}else month = new_month;
		
		if (new_day < 1 || new_day > 31) {
			throw invalid_argument("Day value is invalid: " + to_string(new_day));
		}else day = new_day;

		year = new_year;
	}
	
	int GetYear() const {
		return year;
	}
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	}
private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		}
		else return lhs.GetMonth() < rhs.GetMonth();
	}
	else return lhs.GetYear() < rhs.GetYear();
}

class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		database[date].insert(event);
	}

	bool DeleteEvent(const Date& date, const string& event) {
		if (database.count(date) > 0) {
			if (database.at(date).count(event) == 1) {
				database[date].erase(event);
				return true;
			}
			else return false;
	}
		else {
			return false;
		}
	}

	int  DeleteDate(const Date& date) {
		if (database.count(date) > 0) {
			int N = database.at(date).size();
			database.erase(date);
			return N;
		}
		else return 0;
	}

	/*set<string> Find(const Date& date) const {
		set<string> events;
		if (database.at(date).size() != 0) {
			events = database.at(date);
			return events;
		}
		return events;
	}*/

	void Find(const Date & date) const {
		if (database.count(date) > 0) {
			for (const auto & i : database.at(date)) {
				cout << i << endl;
			}
		}
	}

	void Print() const {
		for (const auto& item : database) {
			if (item.first.GetYear() >= 0) {
				for (const auto& str : item.second) {
					cout << setfill('0');
					cout <<setw(4) << item.first.GetYear() << "-" <<  setw(2) << item.first.GetMonth() << "-" << setw(2) << item.first.GetDay() <<" " << str << endl;
				}
			}
		}
	}

private:
	map <Date, set<string>> database;
};

int main() {
	Database db;
	string line;

	while (getline(cin, line)) {
		try {
			stringstream ss(line);
			string command;
			ss >> command;

			if (command == "Add" || command == "Del" || command == "Find") {
				string date_string;
				ss >> date_string;
				stringstream date_stream(date_string);
				int year, month, day;
			
				try {
					//year
					char sym = date_stream.peek();
					date_stream >> year;
					if ((date_stream.peek() != '-') || (sym == '-' && year == 0) || (year > 9999)) throw invalid_argument("Wrong date format: " + date_string);
					else date_stream.ignore(1);

					//month
					date_stream >> month;
					if (date_stream.peek() != '-') throw invalid_argument("Wrong date format: " + date_string);
					else date_stream.ignore(1);

					//day
					if (date_stream.rdbuf()->in_avail() == 0) throw invalid_argument("Wrong date format: " + date_string);
					date_stream >> day;

					if (date_stream.rdbuf()->in_avail() != 0) throw invalid_argument("Wrong date format: " + date_string);
				}
				catch (exception& ex) {
					cout << ex.what() << endl;
					break;
				}

				string event;
				ss >> event;
				
				try {
					Date date(year, month, day);
					if (command == "Add") {
						db.AddEvent(date, event);
					}
					else if (command == "Del") {
						if (event != "") {
							if (db.DeleteEvent(date, event)) {
								cout << "Deleted successfully" << endl;
							}
							else {
								cout << "Event not found" << endl;
							}
						}
						else {
								cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
						}
					}
					else if (command == "Find") {
						/*if (db.Find(date).size() != 0) {
							for (const auto& i : db.Find(date)) {
								cout << i << endl;
							}
						}*/
						db.Find(date);
					}
				}
				catch (exception& ex) {
					cout << ex.what() << endl;
					break;
				}
			}
			else if (command == "Print") {
				db.Print();
			}
			else if (command != "") {
				try {
					throw invalid_argument("Unknown command: " + command);
				}
				catch (exception& ex) {
					cout << ex.what() << endl;
					break;
				}
			}
		}
		catch (exception& some) {

		}
	}

	system("pause");
	return 0;
}