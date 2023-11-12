#ifndef KEEPER_H
#define KEEPER_H
#define MAX_CONTAINERS 10

#include "Container.h"

class Keeper {
public:
    Container* containers[MAX_CONTAINERS];
    int containersCount;
    Keeper();
    ~Keeper();

    void addContainer(Container* container);
    void removeContainer(int index);
    void displayContainers() const;
};

#endif // KEEPER_H
