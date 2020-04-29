//
// Created by Lance Sander on 4/27/20.
//

#ifndef LAB5_SORTEDLIST_H
#define LAB5_SORTEDLIST_H

#include <memory>
#include <iostream>
#include "Node.h"
#include "PrecondViolatedExcep.h"
#include "SortedListInterface.h"

template <class ItemType>
class SortedList : SortedListInterface<ItemType> {
private:
    std::shared_ptr<Node<ItemType>> head;
    int itemCount;
    auto getNodeAt(int position) const;

public:
    SortedList();
    SortedList(const SortedList<ItemType>& sl);
    bool insertSorted(const ItemType &newEntry);
    bool removeSorted(const ItemType &anEntry);
    int getPosition(const ItemType &anEntry) const;
    bool isEmpty() const;
    int getLength() const;
    void clear();
    ItemType getEntry(int position) const;

    bool insert(int newPosition, const ItemType& newEntry);
    bool remove(int position);
    ~SortedList();

};

template<class ItemType>
SortedList<ItemType>::SortedList() : head(nullptr), itemCount(0) {
 //
}

template<class ItemType>
SortedList<ItemType>::SortedList(const SortedList<ItemType>& sl) : itemCount(sl.itemCount)
{
    auto origChainPtr = sl.head;
    if (origChainPtr == nullptr)
        head.reset();
    else {
        head = std::make_shared<Node<ItemType>>();
        head->setItem(origChainPtr->getItem());
        auto newChainPtr = head;
        origChainPtr = origChainPtr->getNext();
        while (origChainPtr != nullptr)
        {
            ItemType nextItem = origChainPtr->getItem();
            auto newNodePtr = std::make_shared<Node<ItemType>>(nextItem);
            newChainPtr->setNext(newNodePtr);
            newChainPtr = newChainPtr->getNext();
            origChainPtr = origChainPtr->getNext();
        }
        newChainPtr->setNext(nullptr);
    }
}

template<class ItemType>
bool SortedList<ItemType>::insertSorted(const ItemType &newEntry) {
    int sortedPos = 1;
    auto thisNode = head;
    for (int i = 1; i <= getLength(); i++) {
        ItemType thisItem = thisNode->getItem();
        if (thisItem < newEntry) {
            sortedPos++;
        }
        thisNode = thisNode->getNext();
    }
    return insert(sortedPos, newEntry);
}

template<class ItemType>
bool SortedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
    bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
    if (ableToInsert) {
        auto newNodePtr = std::make_shared<Node<ItemType>>(newEntry);
        if (newPosition == 1) {
            newNodePtr->setNext(head);
            head = newNodePtr;
        }
        else {
            auto prevPtr = getNodeAt(newPosition - 1);
            newNodePtr->setNext(prevPtr->getNext());
            prevPtr->setNext(newNodePtr);
        }
        itemCount++;
    }
    return ableToInsert;
}

template<class ItemType>
bool SortedList<ItemType>::removeSorted(const ItemType &anEntry) {
    return remove(getPosition(anEntry));
}

template<class ItemType>
bool SortedList<ItemType>::remove(int position) {
    bool ableToRemove = (position >= 1) && (position <= itemCount);
    if (ableToRemove) {
        if (position == 1) {
            head = head->getNext();
        }
        else {
            auto prevPtr = getNodeAt(position - 1);
            auto curPtr = prevPtr->getNext();
            prevPtr->setNext(curPtr->getNext());
        }
        itemCount--;
    }
    return ableToRemove;
}

template<class ItemType>
int SortedList<ItemType>::getPosition(const ItemType &anEntry) const {
    auto thisNode = head;
    int pos = 0;
    for (int i = 1; i <= getLength(); i++) {
        ItemType thisItem = thisNode->getItem();
        if (thisItem == anEntry) {
            pos = i;
        }
        thisNode = thisNode->getNext();
    }
    return pos;
}

template<class ItemType>
auto SortedList<ItemType>::getNodeAt(int position) const {
    auto curPtr = head;
    for (int skip = 1; skip < position; skip++)
        curPtr = curPtr->getNext();

    return curPtr;
}

template<class ItemType>
ItemType SortedList<ItemType>::getEntry(int position) const {
    bool ableToGet = (position >= 1) && (position <= itemCount);
    if (ableToGet) {
        auto nodePtr = getNodeAt(position);
        return nodePtr->getItem();
    }
    else {
        std::string message = "getEntry() called with an empty list or ";
        message  = message + "invalid position.";
        throw(PrecondViolatedExcep(message));
    }
}

template<class ItemType>
bool SortedList<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
int SortedList<ItemType>::getLength() const {
    return itemCount;
}

template<class ItemType>
void SortedList<ItemType>::clear() {
    head.reset();
    itemCount = 0;
}

template<class ItemType>
SortedList<ItemType>::~SortedList(){
    clear();
}

#endif //LAB5_SORTEDLIST_H
