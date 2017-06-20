#include "humanoid.h"


Humanoid::Humanoid(float lenght, float height, float width, float leftArmAngle, float rightArmAngle)
{
    initializeOpenGLFunctions();

    this->lenght = lenght;
    this->height = height;
    this->width = width;

    torso = new Cuboid(3.0*lenght/3.0,7*height/14.0,3*width/5.0);
    head = new Cuboid(2*lenght/3.0,2*height/14.0,2*width/5.0);
    leftArm = new Cuboid(1*lenght/3.0,4*height/14.0,1*width/5.0);
    rightArm = new Cuboid(1*lenght/3.0,4*height/14.0,1*width/5.0);
    leg1 = new Cuboid(1*lenght/3.0,5*height/14.0,1*width/5.0);
    leg2 = new Cuboid(1*lenght/3.0,5*height/14.0,1*width/5.0);
    this->leftArmAngle = leftArmAngle;
    this->rightArmAngle = rightArmAngle;
}

Humanoid::Humanoid(float lenght, float height, float width, float armsAngle) : Humanoid(lenght, height, width, armsAngle, armsAngle) {}

Humanoid::Humanoid(float lenght, float height, float width) : Humanoid(lenght, height, width, 160.0) {}

Humanoid::Humanoid() : Humanoid(3.0, 14.0, 5.0) {}


Humanoid::~Humanoid()
{
    delete torso;
    delete head;
    delete leftArm;
    delete rightArm;
    delete leg1;
    delete leg2;
}

void Humanoid::setLeftArmAngle(float newAngle)
{
    this->leftArmAngle = newAngle;
}

void Humanoid::setRightArmAngle(float newAngle)
{
    this->rightArmAngle = newAngle;
}

float Humanoid::getLeftArmAngle()
{
    return this->leftArmAngle;
}

float Humanoid::getRightArmAngle()
{
    return this->rightArmAngle;
}


void Humanoid::drawGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection, QMatrix4x4 baseMatrix)
{

    QMatrix4x4 matrix(baseMatrix);

    matrix.translate(0.0, 5.0*height/14.0, 0.0);
    program->setUniformValue("mvp", projection * matrix);

    torso->drawGeometry(program);

    matrix = baseMatrix;
    matrix.translate(0.5*lenght/3.0, 12*height/14.0, 0.5*width/5.0);
    program->setUniformValue("mvp", projection * matrix);

    head->drawGeometry(program);

    matrix = baseMatrix;
    matrix.translate(2*lenght/3.0, 11.5*height/14.0, 3.0*width/5.0);
    matrix.rotate(this->leftArmAngle, 0, 0, 1);
    program->setUniformValue("mvp", projection * matrix);

    leftArm->drawGeometry(program);

    matrix = baseMatrix;
    matrix.translate(2*lenght/3.0, 11.5*height/14.0, -1*width/5.0);
    matrix.rotate(this->rightArmAngle, 0, 0, 1);
    program->setUniformValue("mvp", projection * matrix);

    rightArm->drawGeometry(program);

    matrix = baseMatrix;
    matrix.translate(1*lenght/3.0, 0.0, 0.0);
    program->setUniformValue("mvp", projection * matrix);

    leg1->drawGeometry(program);

    matrix = baseMatrix;
    matrix.translate(1*lenght/3.0, 0.0, 2.0*width/5.0);
    program->setUniformValue("mvp", projection * matrix);

    leg2->drawGeometry(program);
}

