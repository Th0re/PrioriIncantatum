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

#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    torso(0),
    head(0),
    leftArm(0),
    rightArm(0),
    leg1(0),
    leg2(0),
    angularSpeed(0)
{
    leftArmRotation = 90;
    rightArmRotation = 90;
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete geometries;
    delete torso;
    delete head;
    delete leftArm;
    delete rightArm;
    delete leg1;
    delete leg2;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}
//! [1]

void MainWidget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape) {
        exit(0);
    }
    if (e->key() == Qt::Key_Left) {
        leftArmRotation = leftArmRotation + ( leftArmRotationUp? -3 : 3 );
        if (leftArmRotation > 180) {
            leftArmRotationUp = true;
        } else if (leftArmRotation < 0) {
            leftArmRotationUp = false;
        }
        printf("%f, %d \n", leftArmRotation, leftArmRotationUp);
    }
    if (e->key() == Qt::Key_Right) {
        rightArmRotation = rightArmRotation + ( rightArmRotationUp? -3 : 3 );
        if (rightArmRotation > 180) {
            rightArmRotationUp = true;
        } else if (rightArmRotation < 0) {
            rightArmRotationUp = false;
        }
    }
    update();
}


void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;
    torso = new Cuboid(3,7,2);
    head = new Cuboid(2);
    leftArm = new Cuboid(1,4,1);
    rightArm = new Cuboid(1,4,1);
    leg1 = new Cuboid(1,5,1);
    leg2 = new Cuboid(1,5,1);

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]


//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 50.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//! [6]
    // Calculate model view transformation
    QMatrix4x4 baseMatrix;
    baseMatrix.translate(0.0, -2.0, -20.0);
    baseMatrix.rotate(rotation);

    QMatrix4x4 matrix(baseMatrix);
    matrix.translate(-1.5, 0.0, 0.0);

    // Set modelview-projection matrix
    program.setUniformValue("mvp", projection * matrix);
    // Draw cube geometry
    torso->drawGeometry(&program);

    matrix = baseMatrix;
    matrix.translate(-1.0, 7.0, 0.0);
    program.setUniformValue("mvp", projection * matrix);

    head->drawGeometry(&program);

    matrix = baseMatrix;
    matrix.translate(-1.5-1, 6.9, 0.5);
    matrix.rotate(leftArmRotation, 1, 0);
    program.setUniformValue("mvp", projection * matrix);

    leftArm->drawGeometry(&program);

    matrix = baseMatrix;
    matrix.translate(1.5, 6.9, 0.5);
    matrix.rotate(rightArmRotation, 1, 0, 0);
    program.setUniformValue("mvp", projection * matrix);

    rightArm->drawGeometry(&program);

    matrix = baseMatrix;
    matrix.translate(-1.5, -5.0, 0.5);
    program.setUniformValue("mvp", projection * matrix);

    leg1->drawGeometry(&program);

    matrix = baseMatrix;
    matrix.translate(0.5, -5.0, 0.5);
    program.setUniformValue("mvp", projection * matrix);

    leg2->drawGeometry(&program);


}
