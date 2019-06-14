#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void printVec(const vector<int>& m) {
	for (const auto& x : m) {
		cout << x << " ";
	}
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	vector<int> numbers;

	if (n >= 0 && n <= 1000) {
		for (int i = 0; i < n; i++) {
			int num;
			cin >> num;
			numbers.push_back(num);
		}
	}

	sort(numbers.begin(), numbers.end(), [](int i, int j) { return abs(i) < abs(j); });

	printVec(numbers);

	system("pause");
	return 0;
}