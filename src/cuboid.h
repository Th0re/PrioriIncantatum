#ifndef CUBOID_H
#define CUBOID_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class Cuboid : protected QOpenGLFunctions
{
public:
    Cuboid(float length, float height, float width);
    Cuboid(float length);
    Cuboid();
    virtual ~Cuboid();

    void drawGeometry(QOpenGLShaderProgram *program);

private:
    void initGeometry(float length, float height, float width);

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // CUBOID_H
