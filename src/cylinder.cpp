#include "cylinder.h"

#include <QVector2D>
#include <QVector3D>
#include <QMatrix3x3>


Cylinder::Cylinder(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B) : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry(PT_A, COLOR_A, PT_B, COLOR_B);
}

Cylinder::~Cylinder(){
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Cylinder::drawGeometry(QOpenGLShaderProgram *program){
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
    glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, 0);
}

void Cylinder::initGeometry(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B){



    // Coordonées des points d'une des face du cylindre si celui-ci passe par P1 (x1, y1, z1)
    // et dont l'axe est colinéaire à l'axe z
    QVector3D pt1 = QVector3D(PT_A.x(), PT_A.y() + 0.4, PT_A.z());
    QVector3D pt2 = QVector3D(PT_A.x(), PT_A.y() - 0.4, PT_A.z() + 0.4);
    QVector3D pt3 = QVector3D(PT_A.x(), PT_A.y() - 0.4, PT_A.z() - 0.4);

    // Coordonné des point 4, 5 et 6 de la deuxième face

    QVector3D pt4 = QVector3D(PT_B.x(), PT_B.y() + 0.4, PT_B.z()); //pt1 + vectAB;

    QVector3D pt5 = QVector3D(PT_B.x(), PT_B.y() - 0.4, PT_B.z() + 0.4); //pt2 + vectAB;

    QVector3D pt6 = QVector3D(PT_B.x(), PT_B.y() - 0.4, PT_B.z() - 0.4); //pt3 + vectAB;

    //Tableau des vertex

    vertices[0].position = pt1;
    vertices[1].position = pt2;
    vertices[2].position = pt3;
    vertices[3].position = pt4;
    vertices[4].position = pt5;
    vertices[5].position = pt6;

    vertices[0].color = QVector3D(COLOR_A.x(), COLOR_A.y(), COLOR_A.z());
    vertices[1].color = QVector3D(COLOR_A.x(), COLOR_A.y(), COLOR_A.z());
    vertices[2].color = QVector3D(COLOR_A.x(), COLOR_A.y(), COLOR_A.z());
    vertices[3].color = QVector3D(COLOR_B.x(), COLOR_B.y(), COLOR_B.z());
    vertices[4].color = QVector3D(COLOR_B.x(), COLOR_B.y(), COLOR_B.z());
    vertices[5].color = QVector3D(COLOR_B.x(), COLOR_B.y(), COLOR_B.z());

    // Table des indices

    indices[0] = 5;
    indices[1] = 3;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 1;
    indices[5] = 3;
    indices[6] = 4;
    indices[7] = 5;

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));
}
