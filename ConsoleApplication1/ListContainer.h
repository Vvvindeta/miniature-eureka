#ifndef LIST_CONTAINER_H
#define LIST_CONTAINER_H

#include "Container.h"

class ListContainer : public Container {
private:
    struct Node {
        int data;
        Node* next;

        Node(int value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
    };

    Node* head;

public:
    ListContainer();
    ~ListContainer() override;
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

#endif // LIST_CONTAINER_H
