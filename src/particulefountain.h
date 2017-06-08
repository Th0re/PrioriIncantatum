#ifndef PARTICULEFOUNTAIN_H
#define PARTICULEFOUNTAIN_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "particle.h"

class ParticuleFountain : protected QOpenGLFunctions
{
public:
//    ParticuleFountain(int nbOfParticules, float width, float top, float bottom);
    ParticuleFountain(int nbParticles);
    ParticuleFountain() : ParticuleFountain(10000) {}

    virtual ~ParticuleFountain();

    void drawGeometry(QOpenGLShaderProgram *particleShader, int elapsedTime);


private:
    Particle *particle;
    int nbParticles;
    QList<float> angles;
};

#endif // PARTICULEFOUNTAIN_H
