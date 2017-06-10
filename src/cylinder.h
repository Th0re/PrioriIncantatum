#ifndef CYLINDER_H
#define CYLINDER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

class Cylinder : protected QOpenGLFunctions
{
    public:
        Cylinder(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B);
        virtual ~Cylinder();

        void drawGeometry(QOpenGLShaderProgram *program);

    private:
        VertexData vertices[6];
        int nbrVertices = 6;

        GLushort indices[8];
        int nbrIndices = 8;

        /*************************************************************************************
         * Méthode appel
         * ***********************************************************************************/
        void initGeometry(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B);

        QOpenGLBuffer arrayBuf;
        QOpenGLBuffer indexBuf;
};

#endif
