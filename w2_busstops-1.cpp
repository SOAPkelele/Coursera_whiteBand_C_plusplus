#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void allBuses(const map<string, vector<string>>& m) {
	if (m.size() != 0) {
		for (auto& h : m) {
				cout << "Bus " << h.first << ": ";
				for (auto& l : h.second) {
					cout << l << " ";
				}
				cout << endl;
		}
		cout << endl;
	}
	else cout << "No buses" << endl;
}

int main() {
	map<string, vector<string>> buses;
	vector <string> busOrder;
	int q;
	cin >> q;
	string command, bName, stopN, station; 
	int stop_count;
	
	for (int i = 0; i < q; i++) {
		cin >> command;
		if (command == "NEW_BUS") {
			cin >> bName >> stop_count;
			vector<string>route (stop_count);
			for (int i = 0; i < stop_count; i++) {
				cin >> stopN;
				route.push_back(stopN);
			}
			busOrder.push_back(bName);
			buses[bName] = route;
		}
		else if (command == "BUSES_FOR_STOP") {
			cin >> station;
			int f = 0;
			for (auto l : busOrder) {
				for (auto m : buses[l]) {
					if (m == station) {
						f++;
						cout << l << " ";
					}
				}
			}
			if (f != 0) cout << endl;
			else cout << "No stop" << endl;
		}
		else if (command == "STOPS_FOR_BUS") {
			cin >> bName;
			if (buses.count(bName) >= 1) {
				for (auto n : buses[bName]) {
					if (n != "") {
						cout << "Stop " << n << ": ";
						int f = 0;
						for (auto l : busOrder) {
							for (auto m : buses[l]) {
								if (m == n) {
									if (bName != l) {
										cout << l << " ";
										f++;
									}
								}
							}
						}
						if (f != 0) cout << endl;
						else cout << "no interchange" << endl;
					}
				}
			}
			else cout << "No bus" << endl;
		}
		else if (command == "ALL_BUSES") {
			allBuses(buses);
		}
	}

	system("pause");
	return 0;
}