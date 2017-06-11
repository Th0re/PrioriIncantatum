#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "lightninggenerator.h"

#include <QVector4D>



class Lightning : protected QOpenGLFunctions
{
public:
    Lightning(QVector3D colorA, QVector3D colorB, float size);
    Lightning() : Lightning(QVector3D(1.,1.,1.), QVector3D(1.,1.,1.), 10.) {}

    ~Lightning();

    void drawGeometry(QOpenGLShaderProgram *program);

private:
    LightningGenerator lightningGenerator;
    QVector3D colorA, colorB;
    float size;
};

#endif // LIGHTNING_H
