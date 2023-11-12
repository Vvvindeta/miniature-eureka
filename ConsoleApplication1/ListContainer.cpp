#include "ListContainer.h"
#include <iostream>

ListContainer::ListContainer() : head(nullptr) {
    std::cout << "����������� ������ ������ ������." << std::endl;
}

ListContainer::~ListContainer() {
    std::cout << "���������� ������ ������ ������." << std::endl;
    clear();
}

void ListContainer::insert(int value) {
    Node* newNode = new Node(value, head);
    head = newNode;
}

int ListContainer::remove() {
    if (head != nullptr) {
        int headData = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return headData;
    }

    throw std::out_of_range("������ ����.");
}

std::string ListContainer::getType() const {
    return "������";
}

int ListContainer::getSize() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

int ListContainer::getData() const {
    if (head != nullptr) {
        return head->data;
    }
    return -1; // �������� �� ���������
}

void ListContainer::setData(int value) {
    if (head != nullptr) {
        head->data = value;
    }
}

void ListContainer::serialize(std::ostream& os) const {
    Node* current = head;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
}

void ListContainer::deserialize(std::istream& is) {
    clear();
    int size;
    is >> size;
    for (int i = 0; i < size; i++) {
        int value;
        is >> value;
        insert(value);
    }
}

void ListContainer::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}
