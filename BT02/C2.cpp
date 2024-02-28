#include <bits/stdc++.h>
using namespace std;
int n;
int main () {
	cin >> n;
	for (int i = n; i >= 1; i --)
		{
			for (int j = 1; j <= n-i; j ++)
				cout << " ";
			for (int l = 1; l <= i; l ++)
				cout <<"*";
			cout << endl;
		}
}