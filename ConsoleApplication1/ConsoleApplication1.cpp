#include <iostream>
#include <fstream>

class Base {
public:
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    int data;

    void serialize(std::ostream& os) const override {
        os << data << " ";
    }

    void deserialize(std::istream& is) override {
        is >> data;
    }
};

class Keeper {
private:
    static const int maxObjects = 100;
    Base* objects[maxObjects];
    int objectCount;

public:
    Keeper() : objectCount(0) {}

    void addObject(Base* obj) {
        if (objectCount < maxObjects) {
            objects[objectCount] = obj;
            objectCount++;
        }
    }

    void removeObject(int index) {
        if (index >= 0 && index < objectCount) {
            delete objects[index];
            for (int i = index; i < objectCount - 1; i++) {
                objects[i] = objects[i + 1];
            }
            objectCount--;
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < objectCount; i++) {
                objects[i]->serialize(file);
                file << std::endl;  
            }
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            objectCount = 0;
            while (!file.eof()) {

                Base* obj = new Derived;
                obj->deserialize(file);
                addObject(obj);
            }
        }
    }
};

int main() {
    Keeper keeper;

    Derived* obj1 = new Derived;
    Derived* obj2 = new Derived;
    obj1->data = 42;
    obj2->data = 123;
    keeper.addObject(obj1);
    keeper.addObject(obj2);

    keeper.saveToFile("objects.txt");

    Keeper loadedKeeper;
    loadedKeeper.loadFromFile("objects.txt");

    return 0;
}
