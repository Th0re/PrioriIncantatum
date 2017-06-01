#ifndef HUMANOID_H
#define HUMANOID_H

#include "cuboid.h"

class Humanoid : protected QOpenGLFunctions
{
public:
    Humanoid(float lenght, float height, float width);
    Humanoid(float armsAngle, float lenght, float height, float width);
    Humanoid(float lenght, float height, float width, float leftArmAngle, float rightArmAngle);
    ~Humanoid();

    void changeLeftArmAngle(float newAngle);
    void changeRightArmAngle(float newAngle);

    void drawGeometry(QOpenGLShaderProgram *program);


private:
    Cuboid *torso, *head, *leftArm, *rightArm, *leg1, *leg2;
    float leftArmAngle, rightArmAngle;
};

#endif // HUMANOID_H
