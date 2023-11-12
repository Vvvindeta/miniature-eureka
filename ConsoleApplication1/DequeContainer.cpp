#include "DequeContainer.h"
#include <iostream>

DequeContainer::DequeContainer() : front(nullptr), rear(nullptr) {
    std::cout << "Конструктор класса дека вызван." << std::endl;
}

DequeContainer::~DequeContainer() {
    std::cout << "Деструктор класса дека вызван." << std::endl;
    clear();
}

void DequeContainer::insert(int value) {
    Node* newNode = new Node(value, nullptr, nullptr);

    if (front == nullptr) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        newNode->prev = rear;
        rear = newNode;
    }
}

int DequeContainer::remove() {
    if (front != nullptr) {
        int frontData = front->data;
        Node* temp = front;
        front = front->next;

        if (front != nullptr) {
            front->prev = nullptr;
        }
        else {
            rear = nullptr;
        }

        delete temp;
        return frontData;
    }

    throw std::out_of_range("Дек пуст.");
}

std::string DequeContainer::getType() const {
    return "Дек";
}

int DequeContainer::getSize() const {
    int count = 0;
    Node* current = front;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

int DequeContainer::getData() const {
    if (front != nullptr) {
        return front->data;
    }
    return -1; // Значение по умолчанию
}

void DequeContainer::setData(int value) {
    if (front != nullptr) {
        front->data = value;
    }
}

void DequeContainer::serialize(std::ostream& os) const {
    Node* current = front;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
}

void DequeContainer::deserialize(std::istream& is) {
    clear();
    int size;
    is >> size;
    for (int i = 0; i < size; i++) {
        int value;
        is >> value;
        insert(value);
    }
}

void DequeContainer::clear() {
    Node* current = front;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    front = rear = nullptr;
}
