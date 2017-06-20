#include "floor.h"

#include <QVector2D>
#include <QVector3D>
#include <QMatrix3x3>
#include <QtMath>


Floor::Floor(float ray, QVector3D centerColor, QVector3D borderColor) : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry(ray, centerColor, borderColor);
}

Floor::~Floor()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Floor::initGeometry(float ray, QVector3D centerColor, QVector3D borderColor)
{

    // Coordonées des points d'une des face du cylindre si celui-ci passe par P1 (x1, y1, z1)
    // et dont l'axe est colinéaire à l'axe z

    //Tableau des vertex

    vertices[0].position = QVector3D();
    vertices[0].color = centerColor;
    indices[0] = 0;
    for (int i = 1; i < 13; ++i)
    {
        vertices[i].position = QVector3D(sin(i*M_PI/6)*ray, .0, cos(i*M_PI/6)*ray);
        vertices[i].color = borderColor;
        indices[i] = i;
    }
    indices[13] = 1;

    // Table des indices



    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));
}

void Floor::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Draw cylinder geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_FAN, nbrIndices, GL_UNSIGNED_SHORT, 0);
}

