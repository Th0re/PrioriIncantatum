#ifndef FLOOR_H
#define FLOOR_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

class Floor : protected QOpenGLFunctions
{

public:
    Floor(float ray, QVector3D centerColor, QVector3D borderColor);
    virtual ~Floor();

    // Méthode appelé
    void drawGeometry(QOpenGLShaderProgram *program);

private:
    VertexData vertices[13]; // Tableau contenant les vertices
    int nbrVertices = 13; // Nombre de vertices formant la forme

    GLushort indices[14]; // Tableau contenant les indices
    int nbrIndices = 14; // Nombre d'indice utilisé pour créer la forme

    void initGeometry(float ray, QVector3D centerColor, QVector3D borderColor);

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // FLOOR_H
