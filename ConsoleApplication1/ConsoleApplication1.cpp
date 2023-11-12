#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "Container.h"

#define MAX_CONTAINERS 10

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
    DequeContainer() : front(nullptr), rear(nullptr) {
        std::cout << "Конструктор класса дека вызван." << std::endl;
    }

    ~DequeContainer() override {
        std::cout << "Деструктор класса дека вызван." << std::endl;
        clear();
    }

    void insert(int value) override {
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

    int remove() override {
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

    std::string getType() const override {
        return "Дек";
    }

    int getSize() const override {
        int count = 0;
        Node* current = front;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    int getData() const override {
        if (front != nullptr) {
            return front->data;
        }
        return -1; // Значение по умолчанию
    }

    void setData(int value) override {
        if (front != nullptr) {
            front->data = value;
        }
    }

    void serialize(std::ostream& os) const override {
        Node* current = front;
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
        Node* current = front;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        front = rear = nullptr;
    }
};

class StackContainer : public Container {
private:
    struct Node {
        int data;
        Node* next;

        Node(int value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
    };

    Node* top;

public:
    StackContainer() : top(nullptr) {
        std::cout << "Конструктор класса стека вызван." << std::endl;
    }

    ~StackContainer() override {
        std::cout << "Деструктор класса стека вызван." << std::endl;
        clear();
    }

    void insert(int value) override {
        Node* newNode = new Node(value, top);
        top = newNode;
    }

    int remove() override {
        if (top != nullptr) {
            int topData = top->data;
            Node* temp = top;
            top = top->next;
            delete temp;
            return topData;
        }

        throw std::out_of_range("Стек пуст.");
    }

    std::string getType() const override {
        return "Стек";
    }

    int getSize() const override {
        int count = 0;
        Node* current = top;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    int getData() const override {
        if (top != nullptr) {
            return top->data;
        }
        return -1; // Значение по умолчанию
    }

    void setData(int value) override {
        if (top != nullptr) {
            top->data = value;
        }
    }

    void serialize(std::ostream& os) const override {
        Node* current = top;
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
        Node* current = top;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        top = nullptr;
    }
};

class Keeper {
private:
    

public:
    Container* containers[MAX_CONTAINERS];
    int containersCount;
    Keeper() : containersCount(0) {}
    
    ~Keeper() {
        for (int i = 0; i < containersCount; ++i) {
            delete containers[i];
        }
    }

    void addContainer(Container* container) {
        if (containersCount < MAX_CONTAINERS) {
            containers[containersCount++] = container;
            std::cout << "Контейнер успешно добавлен.\n";
        }
        else {
            std::cerr << "Достигнут максимальный лимит контейнеров.\n";
        }
    }

    void removeContainer(int index) {
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

    void displayContainers() const {
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
};

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
