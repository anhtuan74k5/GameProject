#include <bits/stdc++.h>
using namespace std;
int main () {
	int n;
	cin >> n;
	int certain = n-1;
	for (int y = certain; y >= 0; y--)
		{
			for (int x = 0 - certain; x <= certain;  x++)
				{
					if (abs(x) + abs(y) <= abs(certain))
						cout << "*";
					else cout <<" ";
				}
			cout << endl;
		}
}