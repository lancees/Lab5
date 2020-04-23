// Example overload operators and friend

#include <iostream>
#include <random>
#include <chrono>
#include <memory>

// base class missing copy constructor and assignment operator overloading
// base class does overload insertion operator with friend function
class Bag {
protected:
    const static int BAG_SIZE = 3;
    int * bag;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

public:
    Bag() : distribution(1,100), generator(std::chrono::system_clock::now().time_since_epoch().count())
    {
        bag = new int[BAG_SIZE];
        std::cout << "default ";
        shake();
    }
    ~Bag () {
        std::cout << this->bag << " delete" << std::endl;
        delete [] bag;
    }

    void shake() {
        std::cout << "shake" << std::endl;
        for (int i =0; i < BAG_SIZE; i++)
        {
            bag[i] = distribution(generator);
        }
    }

    friend std::ostream& operator <<(std::ostream& out, const Bag &bag);
};

std::ostream& operator <<(std::ostream& out, const Bag &bag)
{
    out << "bag:";
    for (int i =0; i < Bag::BAG_SIZE; i++)
    {
        out << " " << bag.bag[i];
    }
    return out;
}


class BetterBag : public Bag {

public:
    BetterBag() : Bag() {}

    BetterBag(const BetterBag& otherBag) {
        std::cout << "copy " << std::endl;
        bag = new int[BAG_SIZE];
        for (int i =0; i < Bag::BAG_SIZE; i++)
            bag[i] = otherBag.bag[i];
    }

    BetterBag &operator =(const BetterBag& rhs)
    {
        std::cout << "=" << std::endl;
        if(this == &rhs)
            return *this;

        for (int i =0; i < Bag::BAG_SIZE; i++)
            bag[i] = rhs.bag[i];
        return *this;
    }
};


int main()
{
    Bag bag1;
    Bag bag2(bag1), bag3;
    bag3 = bag1;
    std::cout << "1 " << bag1 << std::endl;
    std::cout << "2 " << bag2 << std::endl;
    std::cout << "3 " << bag3 << std::endl;

    bag1.shake();

    std::cout << "1 " << bag1 << std::endl;
    std::cout << "2 " << bag2 << std::endl;
    std::cout << "3 " << bag3 << std::endl;

    std::cout << std::endl << "Betterbag"<< std::endl;

    BetterBag bagb1;
    BetterBag bagb2(bagb1), bagb3;

    std::cout << "1 " << bagb1 << std::endl;
    std::cout << "2 " << bagb2 << std::endl;
    std::cout << "3 " << bagb3 << std::endl;

    bagb3 = bagb1;
    std::cout << "3 " << bagb3 << std::endl;
    bagb1.shake();

    std::cout << "1 " << bagb1 << std::endl;
    std::cout << "2 " << bagb2 << std::endl;
    std::cout << "3 " << bagb3 << std::endl;

}