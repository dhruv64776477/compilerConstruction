#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of Fibonacci terms: ";
    cin >> n;

    int first = 0, second = 1;

    cout << "Fibonacci series: ";
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            cout << first;
        } else {
            cout << ", " << first;
        }

        int next = first + second;
        first = second;
        second = next;
    }

    cout << endl;
    return 0;
}
