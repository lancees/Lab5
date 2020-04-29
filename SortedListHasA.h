// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT sorted list using ADT list.
 Listing 12-3.
 @file SortedListHasA.h */

#ifndef _SORTED_LIST_HAS_A
#define _SORTED_LIST_HAS_A

#include <random>
#include <chrono>
#include <memory>
#include "SortedListInterface.h"
#include "ListInterface.h"
#include "LinkedList.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class SortedListHasA : public SortedListInterface<ItemType>
{
protected:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
private:
   std::unique_ptr<ListInterface<ItemType>> listPtr;
	
public:
   SortedListHasA();
   SortedListHasA(const SortedListHasA<ItemType>& sList);
   virtual ~SortedListHasA();
   
   bool insertSorted(const ItemType& newEntry);
   bool removeSorted(const ItemType& anEntry);
   int getPosition(const ItemType& newEntry) const;
   
   // The following methods have the same specifications
   // as given in ListInterface:

   bool isEmpty() const;
   int getLength() const;
   bool remove(int position);
   void clear();
   ItemType getEntry(int position) const;

   int randInt();
}; // end SortedListHasA




template<class ItemType>
SortedListHasA<ItemType>::SortedListHasA()
: listPtr(std::make_unique<LinkedList<ItemType>>()) , distribution(1,100), generator(std::chrono::system_clock::now().time_since_epoch().count())
{
    std::cout << distribution(generator);
}  // end default constructor

template<class ItemType>
SortedListHasA<ItemType>::SortedListHasA(const SortedListHasA<ItemType>& sList)
: listPtr(std::make_unique<LinkedList<ItemType>>()), distribution(1,100), generator(std::chrono::system_clock::now().time_since_epoch().count())
{
    //  add items to our list using public methods
    for(int position = 1; position <= sList.getLength(); position++)
    {
        listPtr->insert(position, sList.getEntry(position));
    }  // end for
}  // end copy constructor

template<class ItemType>
SortedListHasA<ItemType>::~SortedListHasA()
{
    clear();
}  // end destructor

template<class ItemType>
bool SortedListHasA<ItemType>::insertSorted(const ItemType& newEntry)
{
    int newPosition = std::abs(getPosition(newEntry));
    return listPtr->insert(newPosition, newEntry);;
}  // end insertSorted

template<class ItemType>
bool SortedListHasA<ItemType>::removeSorted(const ItemType& anEntry)
{
    bool ableToRemove = false;
    if (!isEmpty())
    {
        int position = getPosition(anEntry);
        
        ableToRemove = position > 0;
        if (ableToRemove)
        {
            ableToRemove = listPtr->remove(position);
        }  // end if
    }  // end if
    
    return ableToRemove;
}  // end removeSorted

template<class ItemType>
int SortedListHasA<ItemType>::getPosition(const ItemType& anEntry) const
{
    int position = 1;
    int length = listPtr->getLength();
    
    while ( (position <= length) && (anEntry > listPtr->getEntry(position)) )
    {
        position++;
    } // end while
    
    if ( (position > length) || (anEntry != listPtr->getEntry(position)) )
        position = -position;
    
    return position;
}  // end getPosition

//=====================
// List operations:

template<class ItemType>
bool SortedListHasA<ItemType>::remove(int position)
{
    return listPtr->remove(position);
}  // end remove

template<class ItemType>
void SortedListHasA<ItemType>::clear()
{
    listPtr->clear();
}  // end clear

template<class ItemType>
ItemType SortedListHasA<ItemType>::getEntry(int position) const
{
    return listPtr->getEntry(position);
}  // end getEntry

template<class ItemType>
bool SortedListHasA<ItemType>::isEmpty() const
{
    return listPtr->isEmpty();
}  // end isEmpty

template<class ItemType>
int SortedListHasA<ItemType>::getLength() const
{
    return listPtr->getLength();
}  // end getLength

template<class ItemType>
int SortedListHasA<ItemType>::randInt() {
    return distribution(generator);
}

//  End of implementation file.

std::ostream & operator << (std::ostream &out, const SortedListHasA<int> &sl)
{
    for (int i = 1; i<= sl.getLength(); i++) {
        out << sl.getEntry(i) << ",";
    }
    out << std::endl;
    return out;
}


#endif 
