#include <iostream>
#include "LinearList.h"

using std::cout;
using std::find;

int main() {

    arrayList<int> a(10);

    for (int i = 0; i < 40; i++) {
        a.insert(i, i);
    }

    cout << "listSize: " << a.size() << endl;
    cout << "arrayLength: " << a.capacity() << endl;
    cout << a << endl;

    cout << endl;

    while (a.size() > 9) {
        a.erase(0);
    }
    cout << "listSize: " << a.size() << endl;
    cout << "arrayLength: " << a.capacity() << endl;
    cout << a << endl;

    cout << "value in 7 index: " << a.get(7) << endl;
    cout << "index of 39: " << a.indexOf(39) << endl;

    return 0;
}

