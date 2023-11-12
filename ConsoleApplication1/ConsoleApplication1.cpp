#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "Container.h"
#include "ListContainer.h"
#include "DequeContainer.h"
#include "StackContainer.h"
#include "Keeper.h"

#define MAX_CONTAINERS 10

void interactWithContainer(Container* container) {
    int choice;

    do {
        std::cout << "\n1. Добавить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Вернуться в главное меню\n";
        std::cout << "Выберите действие (1-3): ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            std::cout << "Введите значение для добавления: ";
            std::cin >> value;
            container->insert(value);
            break;
        }
        case 2: {
            int removedValue = container->remove();
            std::cout << "Удаленный элемент: " << removedValue << '\n';
            break;
        }
        case 3: {
            std::cout << "Возврат в главное меню.\n";
            break;
        }
        default: {
            std::cout << "Некорректный выбор. Попробуйте еще раз.\n";
        }
        }
    } while (choice != 3);
}

void saveToFile(const std::string& filename, Keeper& keeper) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла для сохранения.\n";
        return;
    }

    file << keeper.containersCount << '\n';

    for (int i = 0; i < keeper.containersCount; ++i) {
        file << keeper.containers[i]->getType() << '\n';
        keeper.containers[i]->serialize(file);
        file << '\n';
    }

    std::cout << "Данные сохранены в файл " << filename << ".\n";
}

void loadFromFile(const std::string& filename, Keeper& keeper) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла для загрузки.\n";
        return;
    }

    keeper.~Keeper(); // Очищаем текущие контейнеры

    int count;
    file >> count;

    for (int i = 0; i < count; ++i) {
        std::string type;
        file >> type;

        Container* newContainer = nullptr;

        if (type == "Список") {
            newContainer = new ListContainer();
        }
        else if (type == "Дек") {
            newContainer = new DequeContainer();
        }
        else if (type == "Стек") {
            newContainer = new StackContainer();
        }

        if (newContainer != nullptr) {
            newContainer->deserialize(file);
            keeper.addContainer(newContainer);
        }
        else {
            std::cerr << "Неизвестный тип контейнера в файле.\n";
            break;
        }
    }

    std::cout << "Данные загружены из файла " << filename << ".\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    Keeper keeper;

    int choice;

    do {
        std::cout << "\n1. Добавить контейнер\n";
        std::cout << "2. Взаимодействие с контейнером\n";
        std::cout << "3. Удалить контейнер\n";
        std::cout << "4. Вывести контейнеры на экран\n";
        std::cout << "5. Сохранить в файл все контейнеры\n";
        std::cout << "6. Загрузить из файла все контейнеры\n";
        std::cout << "7. Выход\n";
        std::cout << "Выберите действие (1-7): ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "\nВыберите тип контейнера:\n";
            std::cout << "1. Список\n";
            std::cout << "2. Дек\n";
            std::cout << "3. Стек\n";
            int containerType;
            std::cin >> containerType;

            Container* newContainer = nullptr;

            switch (containerType) {
            case 1: {
                newContainer = new ListContainer();
                break;
            }
            case 2: {
                newContainer = new DequeContainer();
                break;
            }
            case 3: {
                newContainer = new StackContainer();
                break;
            }
            default: {
                std::cout << "Некорректный тип контейнера.\n";
                break;
            }
            }

            if (newContainer != nullptr) {
                keeper.addContainer(newContainer);
            }
            break;
        }
        case 2: {
            if (keeper.containersCount > 0) {
                std::cout << "Выберите контейнер для взаимодействия (0-" << keeper.containersCount - 1 << "): ";
                int indexToInteract;
                std::cin >> indexToInteract;

                if (indexToInteract >= 0 && indexToInteract < keeper.containersCount) {
                    interactWithContainer(keeper.containers[indexToInteract]);
                }
                else {
                    std::cout << "Некорректный индекс контейнера.\n";
                }
            }
            else {
                std::cout << "Нет добавленных контейнеров. Добавьте контейнер сначала.\n";
            }
            break;
        }
        case 3: {
            if (keeper.containersCount > 0) {
                std::cout << "Выберите контейнер для удаления (0-" << keeper.containersCount - 1 << "): ";
                int indexToRemove;
                std::cin >> indexToRemove;

                if (indexToRemove >= 0 && indexToRemove < keeper.containersCount) {
                    keeper.removeContainer(indexToRemove);
                }
                else {
                    std::cout << "Некорректный индекс контейнера.\n";
                }
            }
            else {
                std::cout << "Нет добавленных контейнеров. Удаление невозможно.\n";
            }
            break;
        }
        case 4: {
            keeper.displayContainers();
            break;
        }
        case 5: {
            std::string filename = "text.txt"; // Фиксированное имя файла
            saveToFile(filename, keeper);
            break;
        }
        case 6: {
            std::string filename = "text.txt"; // Фиксированное имя файла
            loadFromFile(filename, keeper);
            break;
        }
        case 7: {
            std::cout << "Выход из программы.\n";
            break;
        }
        default: {
            std::cout << "Некорректный выбор. Попробуйте еще раз.\n";
        }
        }
    } while (choice != 7);

    return 0;
}
