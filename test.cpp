#include <bits/stdc++.h>
using namespace std;
bool checkPrime (int n) {
	if (n <= 1)
		return false;
	if (n == 2)
		return true;
	for (int i = 2; i * i <= n; i ++)
		if (n % i == 0)
			return false;
		return true;
}

int main () {
	int n;
	cin >> n;
	if (checkPrime(n))
		cout << "yes";
	else cout << "no";
	return 0;
}