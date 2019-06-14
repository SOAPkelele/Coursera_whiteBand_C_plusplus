#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;


int main() {
	int q;
	cin >> q;

	map <string, set<string>>  dic;

	for (int i = 0; i < q; i++) {
		string command;
		cin >> command;
		if (command == "ADD") {
			string word1, word2;
			cin >> word1 >> word2;

			if (dic.count(word1) == 0) {
				set<string> s1;
				s1.insert(word2);
				dic[word1] = s1;
			}
			else {
				dic[word1].insert(word2);
			}

			if (dic.count(word2) == 0) {
				set<string> s2;
				s2.insert(word1);
				dic[word2] = s2;
			}
			else {
				dic[word2].insert(word1);
			}
		}
		else if (command == "COUNT") {
			string word;
			cin >> word;

			if (dic.count(word) == 1) {
				cout << dic[word].size() << endl;
			}
			else cout << "0" << endl;
		}
		else if (command == "CHECK") {
			string word1, word2;
			cin >> word1 >> word2;

			if (dic[word1].count(word2) == 1) {
				cout << "YES" << endl;
			}
			else cout << "NO" << endl;
		}
	}
	system("pause");
	return 0;
}