#ifndef DEQUE_CONTAINER_H
#define DEQUE_CONTAINER_H

#include "Container.h"

class DequeContainer : public Container {
private:
    struct Node {
        int data;
        Node* next;
        Node* prev;

        Node(int value, Node* nextNode = nullptr, Node* prevNode = nullptr)
            : data(value), next(nextNode), prev(prevNode) {}
    };

    Node* front;
    Node* rear;

public:
    DequeContainer();
    ~DequeContainer() override;

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

#endif // DEQUE_CONTAINER_H
