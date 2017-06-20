#include "lightning.h"

Lightning::Lightning(QVector3D colorA, QVector3D colorB, float size)
{
    lightningGenerator = LightningGenerator(1);
    this->colorA = colorA;
    this->colorB = colorB;
    this->size = size;
}

void Lightning::drawGeometry(QOpenGLShaderProgram *program) {
    lightningGenerator.drawLightning(QVector3D(.0,.0,.0), colorA, QVector3D(size, 0., 0.), colorB, .2, 2, program);
}
