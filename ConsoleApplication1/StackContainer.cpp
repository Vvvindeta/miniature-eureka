#include "StackContainer.h"
#include <iostream>

StackContainer::StackContainer() : top(nullptr) {
    std::cout << "����������� ������ ����� ������." << std::endl;
}

StackContainer::~StackContainer() {
    std::cout << "���������� ������ ����� ������." << std::endl;
    clear();
}

void StackContainer::insert(int value) {
    Node* newNode = new Node(value, top);
    top = newNode;
}

int StackContainer::remove() {
    if (top != nullptr) {
        int topData = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return topData;
    }

    throw std::out_of_range("���� ����.");
}

std::string StackContainer::getType() const {
    return "����";
}

int StackContainer::getSize() const {
    int count = 0;
    Node* current = top;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

int StackContainer::getData() const {
    if (top != nullptr) {
        return top->data;
    }
    return -1; // �������� �� ���������
}

void StackContainer::setData(int value) {
    if (top != nullptr) {
        top->data = value;
    }
}

void StackContainer::serialize(std::ostream& os) const {
    Node* current = top;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
}

void StackContainer::deserialize(std::istream& is) {
    clear();
    int size;
    is >> size;
    for (int i = 0; i < size; i++) {
        int value;
        is >> value;
        insert(value);
    }
}

void StackContainer::clear() {
    Node* current = top;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    top = nullptr;
}
