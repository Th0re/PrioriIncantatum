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
        Cylinder(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B, float ray);
        virtual ~Cylinder();

        // Méthode appelé
        void drawGeometry(QOpenGLShaderProgram *program);

    private:
        VertexData vertices[6]; // Tableau contenant les vertices
        int nbrVertices = 6; // Nombre de vertices formant la forme

        GLushort indices[10]; // Tableau contenant les indices
        int nbrIndices = 10; // Nombre d'indice utilisé pour créer la forme

        /*************************************************************************************
         * Méthode appel
         * ***********************************************************************************/
        void initGeometry(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B, float ray);

        QOpenGLBuffer arrayBuf;
        QOpenGLBuffer indexBuf;
};

#endif
