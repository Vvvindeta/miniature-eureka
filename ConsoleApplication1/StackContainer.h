#ifndef STACK_CONTAINER_H
#define STACK_CONTAINER_H

#include "Container.h"

class StackContainer : public Container {
private:
    struct Node {
        int data;
        Node* next;

        Node(int value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
    };

    Node* top;

public:
    StackContainer();
    ~StackContainer() override;

    void insert(int value) override;
    int remove() override;
    std::string getType() const override;
    int getSize() const override;
    int getData() const override;
    void setData(int value) override;
    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

    void clear();
};

#endif // STACK_CONTAINER_H
