/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "cuboid.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

/////////////////////////////// PUBLIC ///////////////////////////////////////
//============================= LIFECYCLE ====================================

Cuboid::Cuboid(float length, float height, float width) : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry(length, height, width);
}

Cuboid::Cuboid(float length) : Cuboid(length, length, length) {}
Cuboid::Cuboid() : Cuboid(1.0) {}

Cuboid::~Cuboid()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

//============================= OPERATIONS ===================================

/**************************************************************************
* Name: initGeometry
* Description: Used to create the shape of the cuboid
* Inputs:
- length: length of the cuboid
- height: height of the cuboid
- width: width of the cuboid
* Returns:
- void
**************************************************************************/
void Cuboid::initGeometry(float length, float height, float width)
{

    VertexData vertices[] = {
        {QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.25f, 0.25f, 0.25f)},
        {QVector3D(length, 0.0f, 0.0f), QVector3D(0.5f, 0.5f, 0.5f)},
        {QVector3D(length, 0.0f, width), QVector3D(0.75f, 0.75f, 0.75f)},
        {QVector3D(length, height, width), QVector3D(0.5f, 0.5f, 0.5f)},
        {QVector3D(length, height, 0.0f), QVector3D(0.25f, 0.25f, 0.25f)},
        {QVector3D(0.0f, height, 0.0f), QVector3D(0.5f, 0.5f, 0.5f)},
        {QVector3D(0.0f, height, width), QVector3D(0.75f, 0.75f, 0.75f)},
        {QVector3D(0.0f, 0.0f, width), QVector3D(0.5f, 0.5f, 0.5f)},
    };


    const int nbrVertices = 8;

    GLushort indices[] = {
        1,0,4,5,6,0,7,2,6,3,4,2,1,0
    };

    const int nbrIndices = 14;

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));

}

/**************************************************************************
* Name: drawGeometry
* Description: Used to display the shape using shaders
* Inputs:
- *program: ShaderProgram used to colorize the cuboid
* Returns:
- void
**************************************************************************/
void Cuboid::drawGeometry(QOpenGLShaderProgram *program)
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
    glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_SHORT, 0);
}

