#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
#include <sstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int maxDel(int a, int b) {
	while (a > 0 && b > 0) {
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}
	}
	return a + b;
}

class Rational {
public:
	Rational() {
		p = 0;
		q = 1;
	}

	Rational(int numerator, int denominator) {
		if (denominator < 0) {
			denominator = abs(denominator);
			numerator = -numerator;
		}
		int maxdel = maxDel(abs(numerator), abs(denominator));
		p = numerator / maxdel;
		q = denominator / maxdel;

		if (p / q > 0) {
			if (p < 0 && q < 0) {
				p = abs(p); q = abs(q);
			}
		}
		else if (p / q < 0) {
			if (q < 0) {
				q = abs(q);
				p = -p;
			}
		}
		else if (p == 0) {
			q = 1;
		}

	}

	int Numerator() const {
		return p;
	}

	int Denominator() const {
		return q;
	}

private:
	int p; // числитель
	int q; // знаменатель
};

bool operator == (const Rational&  lhs, const Rational&  rhs) {
	if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
		return true;
	}
	else return false;
}

Rational operator+ (const Rational&  lhs, const Rational&  rhs) {
	return Rational(lhs.Numerator()*rhs.Denominator() + rhs.Numerator()*lhs.Denominator(), lhs.Denominator()*rhs.Denominator());
}

Rational operator- (const Rational&  lhs, const Rational&  rhs) {
	return Rational(lhs.Numerator()*rhs.Denominator() - rhs.Numerator()*lhs.Denominator(), lhs.Denominator()*rhs.Denominator());
}

Rational operator /(const Rational&  lhs, const Rational&  rhs) {
	return Rational(lhs.Numerator()*rhs.Denominator(), rhs.Numerator()*lhs.Denominator());
}

Rational operator *(const Rational&  lhs, const Rational&  rhs) {
	return Rational(lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator());
}

ostream& operator <<(ostream& stream, const Rational&  x) {
	stream << x.Numerator() << "/" << x.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& input) {
	int a, b;
	stringstream temp;
	string line;
	stream >> line;
	if (line.empty()) return stream;
	temp << line;
	temp >> a;
	temp.ignore(1);
	temp >> b;
	input = { a, b };
	return stream;
}

bool operator< (const Rational&  lhs, const Rational&  rhs) {
	return lhs.Numerator()*rhs.Denominator() < rhs.Numerator()*lhs.Denominator();
}

bool operator> (const Rational&  lhs, const Rational&  rhs) {
	return lhs.Numerator()*rhs.Denominator() > rhs.Numerator()*lhs.Denominator();
}

int main() {
	{
		const set<Rational> rs = { { 1, 2 },{ 1, 25 },{ 3, 4 },{ 3, 4 },{ 1, 2 } };
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set" << endl;
			return 1;
		}

		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
			cout << "Rationals comparison works incorrectly" << endl;
			return 2;
		}
	}

	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
			return 3;
		}
	}


	cout << "OK" << endl;
	system("pause");
	return 0;
}
