#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

class Container {
public:
    virtual ~Container() {}
    virtual void insert(int value) = 0;
    virtual int remove() = 0;
    virtual std::string getType() const = 0;
    virtual int getSize() const = 0;
    virtual int getData() const = 0;
    virtual void setData(int value) = 0;
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
};