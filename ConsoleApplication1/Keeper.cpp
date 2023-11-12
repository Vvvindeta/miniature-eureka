#include "Keeper.h"
#include <iostream>

Keeper::Keeper() : containersCount(0) {}

Keeper::~Keeper() {
    for (int i = 0; i < containersCount; ++i) {
        delete containers[i];
    }
}

void Keeper::addContainer(Container* container) {
    if (containersCount < MAX_CONTAINERS) {
        containers[containersCount++] = container;
        std::cout << "��������� ������� ��������.\n";
    }
    else {
        std::cerr << "��������� ������������ ����� �����������.\n";
    }
}

void Keeper::removeContainer(int index) {
    if (index >= 0 && index < containersCount) {
        delete containers[index];
        for (int i = index; i < containersCount - 1; ++i) {
            containers[i] = containers[i + 1];
        }
        --containersCount;
        std::cout << "��������� ������� ������.\n";
    }
    else {
        std::cerr << "������������ ������ ��� �������� ����������.\n";
    }
}

void Keeper::displayContainers() const {
    if (containersCount > 0) {
        std::cout << "\n������ ����������� �����������:\n";
        for (int i = 0; i < containersCount; ++i) {
            std::cout << i << ". ���: " << containers[i]->getType() << ", ������: " << containers[i]->getSize() << ", ������: ";
            containers[i]->serialize(std::cout);
            std::cout << '\n';
        }
    }
    else {
        std::cout << "��� ����������� �����������.\n";
    }
}
