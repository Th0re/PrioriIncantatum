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
    ParticuleFountain(int nbParticles, QVector4D color, QMatrix4x4 rotationMatrix, float speedFactor, float pointSize);
    ParticuleFountain() : ParticuleFountain(5000, QVector4D(1.0,1.0,1.0,1.0), QMatrix4x4(), 60., 5.) {}

    virtual ~ParticuleFountain();

    void drawGeometry(QOpenGLShaderProgram *particleShader, int elapsedTime);


private:
    void initGeometry(QMatrix4x4 rotationMatrix, float speedFactor);
    int nbParticles;
    float pointSize;

    QOpenGLTexture *texture;
    QVector4D color;

    QOpenGLBuffer arrayBuf;

};

#endif // PARTICULEFOUNTAIN_H
