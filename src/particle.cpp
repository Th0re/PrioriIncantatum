#include "particle.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

Particle::Particle()  : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}


Particle::~Particle() {
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Particle::initGeometry() {
    VertexData vertices[] = {
        {QVector3D(0.0f, 1.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)},
        {QVector3D(-0.5f, 0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.0f, 0.0f, 0.5f), QVector3D(0.0f, 0.0f, 1.0f)},
        {QVector3D(0.5f, 0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.0f, 0.0f, 0.5f), QVector3D(0.0f, 0.0f, 1.0f)},
    };


    const int nbrVertices = 5;

    GLushort indices[] = {
        0,1,2,3,4
    };

    const int nbrIndices = 5;

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));
}

void Particle::drawGeometry(QOpenGLShaderProgram *program)
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

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_SHORT, 0);
}
