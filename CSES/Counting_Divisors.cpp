#include <iostream>

using namespace std;


int main() {
	
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		
		if (x == 1) {
			cout << 1 << endl;
		} else {
			int count = 2;
			for (int j = 2; j * j <= x; j++) {
				if (j * j == x) {
					count++;
				} else if (x % j == 0) {
					count+=2;
				}
			}
			cout << count << endl;
		}
	}
	return 0;
}
