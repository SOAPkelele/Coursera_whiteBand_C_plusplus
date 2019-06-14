#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <locale>
#include <ctype.h>

using namespace std;

bool compare(const string& h, const string& g) {
	string new1 = h, new2 = g;

	for (int i = 0; i < new1.length(); i++){
		new1[i] = tolower(new1[i]);
	}
	
	for (int i = 0; i < new2.length(); i++) {
		new2[i] = tolower(new2[i]);
	}

	return new1 < new2;
}

int main() {
	int n;
	cin >> n;

		vector<string> strings;

		for (int i = 0; i < n; i++) {
			string s;
				cin >> s;
				strings.push_back(s);
		}

		sort(strings.begin(), strings.end(), compare);

		for (auto m : strings) {
			cout << m << " ";
		}
		cout << endl;
	
	system("pause");
	return 0;
}