#ifndef PARTICLE_H
#define PARTICLE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class Particle : protected QOpenGLFunctions
{
public:
    Particle();
    virtual ~Particle();

    void drawGeometry(QOpenGLShaderProgram *program);

private:
    void initGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // PARTICLE_H
