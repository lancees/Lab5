#include <iostream>
#include "SortedListHasA.h"

int main() {
    SortedListHasA<int> mySortedList =  SortedListHasA<int>();
    std::cout << " (Inserting 21 Random Integers, 1-100)" << std::endl;
    int firstInt;
    int ri;
    for (int i = 1; i <= 21; i++) {
        ri =mySortedList.randInt();
        if (i == 1) {
            firstInt = ri;
        }
        mySortedList.insertSorted(ri);
        std::cout << ri << std::endl;
    }
    int firstInsertPos = mySortedList.getPosition(firstInt);
    std::cout << " (Removing " << firstInt << " int stored at " << firstInsertPos << " pos" << std::endl;
    mySortedList.remove(firstInsertPos);
    std::cout << " (Sorted 20 Integers)" << std::endl;
    for (int i = 1; i <= mySortedList.getLength(); i++) {
        std::cout << mySortedList.getEntry(i) << std::endl;
    }
    return 0;
}




