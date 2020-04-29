//
// Created by Lance Sander on 4/28/20.
//
#include <iostream>
#include <random>
#include <chrono>
#include "SortedList.h"

int main() {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1,100);
    SortedList<int> sl = SortedList<int>();
    std::cout << " (Generating 21 random ints between 1 and 100)" << std::endl;
    int firstInt;
    for (int i = 1; i <= 21; i++) {
        int randInt = distribution(generator);
        if (i == 1) {
            firstInt = randInt;
        }
        std::cout << randInt << std::endl;
        sl.insertSorted(randInt);
    }
    std::cout << " (Removing first inserted " << firstInt << " at position " << sl.getPosition(firstInt) << ")" << std::endl;
    sl.removeSorted(firstInt);
    std::cout << " (Display remaining integers sorted)" << std::endl;

    for (int i = 1; i <= sl.getLength(); i++) {
        std::cout << sl.getEntry(i) << std::endl;
    }
//    sl.insert(1, 3);
//    sl.insert(1, 2);
//    sl.insert(1, 1);
//    sl.insert(1, 4);
//    sl.insertSorted(3);
//    sl.insertSorted(2);
//    sl.insertSorted(1);
//    sl.insertSorted(4);
//    sl.insertSorted(4);
//    sl.insertSorted(3);
//    sl.insertSorted(3);
//    sl.removeSorted(3);
    return 0;
}