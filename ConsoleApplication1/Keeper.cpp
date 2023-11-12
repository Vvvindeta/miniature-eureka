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
        std::cout << "Контейнер успешно добавлен.\n";
    }
    else {
        std::cerr << "Достигнут максимальный лимит контейнеров.\n";
    }
}

void Keeper::removeContainer(int index) {
    if (index >= 0 && index < containersCount) {
        delete containers[index];
        for (int i = index; i < containersCount - 1; ++i) {
            containers[i] = containers[i + 1];
        }
        --containersCount;
        std::cout << "Контейнер успешно удален.\n";
    }
    else {
        std::cerr << "Некорректный индекс для удаления контейнера.\n";
    }
}

void Keeper::displayContainers() const {
    if (containersCount > 0) {
        std::cout << "\nСписок добавленных контейнеров:\n";
        for (int i = 0; i < containersCount; ++i) {
            std::cout << i << ". Тип: " << containers[i]->getType() << ", Размер: " << containers[i]->getSize() << ", Данные: ";
            containers[i]->serialize(std::cout);
            std::cout << '\n';
        }
    }
    else {
        std::cout << "Нет добавленных контейнеров.\n";
    }
}
