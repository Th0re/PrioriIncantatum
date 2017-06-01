#ifndef HUMANOID_H
#define HUMANOID_H

#include "cuboid.h"

class Humanoid : protected QOpenGLFunctions
{
public:
    Humanoid(float lenght, float height, float width);
    Humanoid(float armsAngle, float lenght, float height, float width);
    Humanoid(float lenght, float height, float width, float leftArmAngle, float rightArmAngle);
    Humanoid();
    ~Humanoid();

    void setLeftArmAngle(float newAngle);
    void setRightArmAngle(float newAngle);
    float getLeftArmAngle();
    float getRightArmAngle();

    void drawGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection, QMatrix4x4 baseMatrix);


private:
    Cuboid *torso, *head, *leftArm, *rightArm, *leg1, *leg2;
    float lenght, height, width, leftArmAngle, rightArmAngle;
};

#endif // HUMANOID_H
