#include "cylinder.h"

#include <QVector2D>
#include <QVector3D>
#include <QMatrix3x3>

/////////////////////////////// PUBLIC ///////////////////////////////////////
//============================= LIFECYCLE ====================================

Cylinder::Cylinder(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B, float ray) : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry(PT_A, COLOR_A, PT_B, COLOR_B, ray);
}

Cylinder::~Cylinder()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

//============================= OPERATIONS ===================================


/**************************************************************************
* Name: drawGeometry
* Description: Used to display the shape using shaders
* Inputs:
- *program: ShaderProgram used to colorize the cylinder
* Returns:
- void
**************************************************************************/
void Cylinder::drawGeometry(QOpenGLShaderProgram *program)
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
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_SHORT, 0);
}

/**************************************************************************
* Name: initGeometry
* Description: Used to create the shape of
* the cylinder and interpolate the color
* Inputs:
- PT_A: center of the first face
- COLOR_A: Color of the first face
- PT_B: center of the second face
- COLOR_B: Color of the second face
* Returns:
- void
**************************************************************************/
void Cylinder::initGeometry(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B, float ray)
{

    // Coordonées des points d'une des face du cylindre si celui-ci passe par P1 (x1, y1, z1)
    // et dont l'axe est colinéaire à l'axe z
    QVector3D pt1 = QVector3D(PT_A.x(), PT_A.y() + ray, PT_A.z());
    QVector3D pt2 = QVector3D(PT_A.x(), PT_A.y() - ray, PT_A.z() + ray);
    QVector3D pt3 = QVector3D(PT_A.x(), PT_A.y() - ray, PT_A.z() - ray);

    // Coordonné des point 4, 5 et 6 de la deuxième face

    QVector3D pt4 = QVector3D(PT_B.x(), PT_B.y() + ray, PT_B.z());
    QVector3D pt5 = QVector3D(PT_B.x(), PT_B.y() - ray, PT_B.z() + ray);
    QVector3D pt6 = QVector3D(PT_B.x(), PT_B.y() - ray, PT_B.z() - ray);

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

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 5;
    indices[4] = 0;
    indices[5] = 3;
    indices[6] = 1;
    indices[7] = 4;
    indices[8] = 5;
    indices[9] = 3;

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));
}
