//
// Created by Lance Sander on 4/28/20.
//
#include "SortedList.h"

int main() {
    SortedList<int> sl = SortedList<int>();
//    sl.insert(1, 3);
//    sl.insert(1, 2);
//    sl.insert(1, 1);
//    sl.insert(1, 4);
    sl.insertSorted(3);
    sl.insertSorted(2);
    sl.insertSorted(1);
    sl.insertSorted(4);
    sl.insertSorted(4);
    sl.insertSorted(3);
    sl.insertSorted(3);
    sl.removeSorted(3);
    for (int i = 1; i <= sl.getLength(); i++) {
        std::cout << sl.getEntry(i) << std::endl;
    }
    return 0;
}