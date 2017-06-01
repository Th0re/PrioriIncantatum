#include "humanoid.h"


Humanoid::Humanoid(float lenght, float height, float width, float leftArmAngle, float rightArmAngle) {

    torso = new Cuboid(lenght,7*height/14.0,2*width/5.0);
    head = new Cuboid(2*lenght/3.0,2*height/14.0,2*width/5.0);
    leftArm = new Cuboid(1*lenght/3.0,4*height/14.0,1*width/5.0);
    rightArm = new Cuboid(1*lenght/3.0,4*height/14.0,1*width/5.0);
    leg1 = new Cuboid(1*lenght/3.0,5*height/14.0,1*width/5.0);
    leg2 = new Cuboid(1*lenght/3.0,5*height/14.0,1*width/5.0);
    this->leftArmAngle = leftArmAngle;
    this->rightArmAngle = rightArmAngle;
}

Humanoid::Humanoid(float lenght, float height, float width, float armsAngle) : Humanoid(lenght, height, width, armsAngle, armsAngle) {}

Humanoid::Humanoid(float lenght = 3.0, float height = 14.0, float width = 5.0) : Humanoid(lenght, height, width, 0.0) {}


Humanoid::~Humanoid()
{
    delete torso;
    delete head;
    delete leftArm;
    delete rightArm;
    delete leg1;
    delete leg2;
}

void Humanoid::changeLeftArmAngle(float newAngle) {
    this->leftArmAngle = newAngle;
}

void Humanoid::changeRightArmAngle(float newAngle) {
    this->rightArmAngle = newAngle;
}

void Humanoid::drawGeometry(QOpenGLShaderProgram *program) {

    QMatrix4x4 matrix, baseMatrix;

    // Set modelview-projection matrix
    program->setUniformValue("mvp", matrix);
    // Draw cube geometry
    torso->drawGeometry(program);

    matrix.translate(-1.0, 7.0, 0.0);
    program->setUniformValue("mvp", matrix);

    head->drawGeometry(program);

    matrix = baseMatrix;
    matrix.translate(-1.5-1, 6.9, 0.5);
    matrix.rotate(this->leftArmAngle, 1, 0);
    program->setUniformValue("mvp", matrix);

    leftArm->drawGeometry(program);

    matrix = baseMatrix;
    matrix.translate(1.5, 6.9, 0.5);
    matrix.rotate(this->rightArmAngle, 1, 0, 0);
    program->setUniformValue("mvp", matrix);

    rightArm->drawGeometry(program);

    matrix = baseMatrix;
    matrix.translate(-1.5, -5.0, 0.5);
    program->setUniformValue("mvp", matrix);

    leg1->drawGeometry(program);

    matrix = baseMatrix;
    matrix.translate(0.5, -5.0, 0.5);
    program->setUniformValue("mvp", matrix);

    leg2->drawGeometry(program);
}

