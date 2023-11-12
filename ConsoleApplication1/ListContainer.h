#pragma once
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
    ListContainer() : head(nullptr) {
        std::cout << "Конструктор класса списка вызван." << std::endl;
    }

    ~ListContainer() override {
        std::cout << "Деструктор класса списка вызван." << std::endl;
        clear();
    }

    void insert(int value) override {
        Node* newNode = new Node(value, head);
        head = newNode;
    }

    int remove() override {
        if (head != nullptr) {
            int headData = head->data;
            Node* temp = head;
            head = head->next;
            delete temp;
            return headData;
        }

        throw std::out_of_range("Список пуст.");
    }

    std::string getType() const override {
        return "Список";
    }

    int getSize() const override {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    int getData() const override {
        if (head != nullptr) {
            return head->data;
        }
        return -1; // Значение по умолчанию
    }

    void setData(int value) override {
        if (head != nullptr) {
            head->data = value;
        }
    }

    void serialize(std::ostream& os) const override {
        Node* current = head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
    }

    void deserialize(std::istream& is) override {
        clear();
        int size;
        is >> size;
        for (int i = 0; i < size; i++) {
            int value;
            is >> value;
            insert(value);
        }
    }



    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
};