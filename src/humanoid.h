#ifndef HUMANOID_H
#define HUMANOID_H

#include "cuboid.h"

class Humanoid
{
public:
    Humanoid();
    ~Humanoid();

private:
    Cuboid *torso, *head, *leftArm, *rightArm, *leg1,*leg2;
};

#endif // HUMANOID_H
