#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		string a;
		cin >> a;
		if (a != "mumble" && stoi(a) != i) {
			cout << "something is fishy" << endl;
			return 0;
		}
	}
	cout << "makes sense" << endl;
	return 0;
}
