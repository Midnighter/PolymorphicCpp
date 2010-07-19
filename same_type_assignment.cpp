/* 
 * File:   main.cpp
 * Author: engineer
 *
 * Created on 13 July 2010, 20:05
 */

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <string>
//#include <iosfwd>

/*
 * 
 */

using std::cout;
using std::endl;

class Base {

protected:
    /* Data Members */
    int _b;

public:
    /* Constructors & Destructor */
    // default constructor
    Base(): _b(3)
    {
        cout << "Base default constructor" << endl;
    }
    // copy constructor
    Base(const Base& other): _b(other._b)
    {
        cout << "Base copy constructor" << endl;
    }
    // virtual "copy constructor"
    virtual Base* clone()
    {
        cout << "Base virtual clone" << endl;
        return new Base(*this);
    }
    // destructor
    virtual ~Base()
    {
        cout << "Base virtual destructor" << endl;
    }
    /* Operators */
    // virtual assignment operator
    virtual Base& operator=(Base& other)
    {
        cout << "Base virtual assignment operator" << endl;
        assert(typeid(*this) == typeid(other));
        if (this != &other) {
            this->_b = other._b;
        }
        return *this;
    }
    /* Member Functions */
    // virtual stream insertion
    virtual std::ostream& write(std::ostream& out)
    {
        return (out << this->_b);
    }
    // vary data members
    virtual void raffle()
    {
        this->_b = std::rand();
    }

};

class SubBase: public Base {

protected:
    /* Data Members */
    int _sb;

public:
    /* Constructors & Destructor */
    // default constructor
    SubBase(): Base(), _sb(5)
    {
        cout << "SubBase default constructor" << endl;
    }
    // copy constructor
    SubBase(const SubBase& other): Base(other), _sb(other._sb)
    {
        cout << "SubBase copy constructor" << endl;
    }
    // virtual "copy constructor"
    virtual Base* clone()
    {
        cout << "SubBase virtual clone" << endl;
        return new SubBase(*this);
    }
    // destructor
    virtual ~SubBase()
    {
        cout << "SubBase virtual destructor" << endl;
    }
    /* Operators */
    // virtual assignment operator
    virtual Base& operator=(Base& other)
    {
        cout << "SubBase virtual assignment operator" << endl;
        assert(typeid(*this) == typeid(other));
        if (this != &other) {
            SubBase& sub = static_cast<SubBase&>(other);
            Base::operator=(other);
            this->_sb = sub._sb;
        }
        return *this;
    }
    // assignment operator
    SubBase& operator=(SubBase& other)
    {
        cout << "SubBase assignment operator" << endl;
        assert(typeid(*this) == typeid(other));
        if (this != &other) {
            Base& base = static_cast<Base&>(other);
            this->operator=(base);
        }
        return *this;
    }
    /* Member Functions */
    // virtual stream insertion
    virtual std::ostream& write(std::ostream& out)
    {
        Base::write(out);
        return (out << ", " << this->_sb);
    }
    // vary data members
    virtual void raffle()
    {
        Base::raffle();
        this->_sb = std::rand();
    }

};

class SubSubBase: public SubBase {

protected:
    /* Data Members */
    int _ssb;

public:
    /* Cosntructors & Destructor */
    // default constructor
    SubSubBase(): SubBase(), _ssb(9)
    {
        cout << "SubSubBase default constructor" << endl;
    }
    // copy constructor
    SubSubBase(const SubSubBase& other): SubBase(other), _ssb(other._ssb)
    {
        cout << "SubSubBase copy constructor" << endl;
    }
    // virtual "copy constructor"
    virtual Base* clone()
    {
        cout << "SubSubBase virtual clone" << endl;
        return new SubSubBase(*this);
    }
    // destructor
    virtual ~SubSubBase()
    {
        cout << "SubSubBase virtual destructor" << endl;
    }
    /* Operators */
    // virtual assignment operator
    virtual Base& operator=(Base& other)
    {
        cout << "SubSubBase virtual assignment operator" << endl;
        assert(typeid(*this) == typeid(other));
        if (this != &other) {
            SubSubBase& sub = static_cast<SubSubBase&>(other);
            SubBase::operator=(other);
            this->_ssb = sub._ssb;
        }
        return *this;
    }
    // assignment operator
    SubSubBase& operator=(SubSubBase& other)
    {
        cout << "SubSubBase assignment operator" << endl;
        assert(typeid(*this) == typeid(other));
        if (this != &other) {
            Base& base = static_cast<Base&>(other);
            this->operator=(base);
        }
        return *this;
    }
    /* Member Functions */
    // virtual stream insertion
    virtual std::ostream& write(std::ostream& out)
    {
        SubBase::write(out);
        return (out << ", " << this->_ssb);
    }
    // vary data members
    virtual void raffle()
    {
        SubBase::raffle();
        this->_ssb = std::rand();
    }
    
};

std::ostream& operator<<(std::ostream& out, Base& b)
{
    return b.write(out);
}

int main(int argc, char** argv) {
    std::srand(1234567890);
    SubSubBase* the_one = new SubSubBase;
    cout << "The One's values: " << *the_one << endl;
    // use the virtual "copy constructor" here
    SubBase* the_other  = static_cast<SubBase*>(the_one->clone());
    cout << "The Other's values: " << *the_other << endl;
    // change data members randomly
    the_other->raffle();
    cout << "The Other's values: " << *the_other << endl;
    // use virtual assignment
    *the_one = *the_other;
    cout << "The One's values: " << *the_one << endl;
    SubSubBase* the_third = new SubSubBase;
    cout << "The Third's values: " << *the_third << endl;
    // use normal assignment operator which calls virtual one
    *the_third = *the_one;
    cout << "The Third's values: " << *the_third << endl;
    delete the_one;
    delete the_other;
    delete the_third;
    return (EXIT_SUCCESS);
}

