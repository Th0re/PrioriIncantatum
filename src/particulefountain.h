#ifndef PARTICULEFOUNTAIN_H
#define PARTICULEFOUNTAIN_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

class ParticuleFountain : protected QOpenGLFunctions
{
public:
//    ParticuleFountain(int nbOfParticules, float width, float top, float bottom);
    ParticuleFountain(int nbParticles);
    ParticuleFountain() : ParticuleFountain(5000) {}

    virtual ~ParticuleFountain();

    void drawGeometry(QOpenGLShaderProgram *particleShader, int elapsedTime);


private:
    void initGeometry();
    int nbParticles;

    QOpenGLTexture *texture;

    QOpenGLBuffer arrayBuf;

};

#endif // PARTICULEFOUNTAIN_H
