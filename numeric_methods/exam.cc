#include <iostream>
using namespace std;

int main() {
    int a[6] = {4, 0, 3, 2, -6, 10};
    int x = -4;
    int temp = a[0];
    for (int i = 1; i < 6; i++) {
        temp = temp * x + a[i];
    }
    cout << temp;
    return 0;
}