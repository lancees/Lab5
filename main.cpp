#include <iostream>
#include "SortedListHasA.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    SortedListHasA<int> mySortedList =  SortedListHasA<int>();
    int a = 4;
    mySortedList.insertSorted(a);
    mySortedList.insertSorted(3);
    std::cout << mySortedList;
    return 0;



}




