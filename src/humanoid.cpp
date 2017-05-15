#include "humanoid.h"

Humanoid::Humanoid()
{
    torso(0),
    head(0),
    leftArm(0),
    rightArm(0),
    leg1(0),
    leg2(0)
}

Humanoid::~Humanoid()
{
    delete torso;
    delete head;
    delete leftArm;
    delete rightArm;
    delete leg1;
    delete leg2;
}
