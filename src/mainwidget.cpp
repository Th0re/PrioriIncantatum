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
#include "lightninggenerator.h"

#include <QMouseEvent>
#include <QtMath>

#include <math.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////
//============================= LIFECYCLE ====================================

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    angularSpeed(0)
{
    overallTimer.start();
    randomOn = false;
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete harry;
    delete floor;
    delete middleFountain;
    delete leftFountain;
    delete rightFountain;
    delete leftLightning;
    delete rightLightning;
    doneCurrent();
}

//============================= OPERATIONS ===================================
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


void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    }
    else
    {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    }
    update();

}
//! [1]

void MainWidget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Escape)
    {
        exit(0);
    }
    if (e->key() == Qt::Key_Left)
    {
        projection.translate(QVector3D(.5,.0,.0));
    }
    if (e->key() == Qt::Key_Right)
    {
        projection.translate(QVector3D(-.5,.0,.0));
    }
    if (e->key() == Qt::Key_Up)
    {
        projection.translate(QVector3D(.0,.0,.5));
    }
    if (e->key() == Qt::Key_Down)
    {
        projection.translate(QVector3D(.0,.0,-.5));
    }
    if (e->key() == Qt::Key_PageUp)
    {
        projection.translate(QVector3D(.0,-.5,.0));
    }
    if (e->key() == Qt::Key_PageDown)
    {
        projection.translate(QVector3D(.0,.5,.0));
    }
    if (e->key() == Qt::Key_Space)
    {
        randomOn = !randomOn;
    }
    if (e->key() == Qt::Key_H)
    {
        drift += 0.6;
    }
    if (e->key() == Qt::Key_V)
    {
        drift -= 0.6;
    }
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

    // Enable blending
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable point antialiasing
    glEnable(GL_POINT_SMOOTH);
    // Enable point sprites
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_PROGRAM_POINT_SIZE);

    //glClearColor(0.5,0.5,0.5,1);

//! [2]

    harry = new Humanoid(3.0, 14.0, 5.0, 180.0, 90.0);
    floor = new Floor(30., QVector3D(.5, .5, 1.), QVector3D(.05, .05, .4));

    QList<QVector3D> colors;
    colors.append(QVector3D(1.,.0,.0));
    colors.append(QVector3D(1.,1.,.0));
    colors.append(QVector3D(0.,1.,.0));
    colors.append(QVector3D(1.,1.,1.));
    middleFountain = new ParticuleFountain(10000, colors, QMatrix4x4(), 80., 5., 2000, 16., 10.);

    QMatrix4x4 rotationMatrix;
    rotationMatrix(0,0) = qCos(M_PI/3);
    rotationMatrix(0,1) = -qSin(M_PI/3);
    rotationMatrix(1,0) = qSin(M_PI/3);
    rotationMatrix(1,1) = qCos(M_PI/3);
    colors.clear();
    colors.append(QVector3D(1.,.0,.0));
    leftFountain = new ParticuleFountain(100, colors, rotationMatrix, 20., 25., 2000, 8., 0.);

    rotationMatrix(0,0) = qCos(-M_PI/3);
    rotationMatrix(0,1) = -qSin(-M_PI/3);
    rotationMatrix(1,0) = qSin(-M_PI/3);
    rotationMatrix(1,1) = qCos(-M_PI/3);
    colors.clear();
    colors.append(QVector3D(.0,1.0,.0));
    rightFountain = new ParticuleFountain(100, colors, rotationMatrix, 20., 25., 2000, 8., 0.);


    leftLightning = new Lightning(QVector3D(1.,.0,.0), QVector3D(1.,1.,1.), 10.);
    rightLightning = new Lightning(QVector3D(.0,1.,.0), QVector3D(1.,1.,1.), 10.);

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

    // Compile vertex shader
    if (!particleShaders.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/particlevertex.glsl"))
        close();

    // Compile fragment shader
    if (!particleShaders.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/particlefragment.glsl"))
        close();

    // Link shader pipeline
    if (!particleShaders.link())
        close();

}
//! [3]


//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 200.0, fov = 65.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Bind shader pipeline for use
    if (!program.bind())
        close();
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//! [6]
    // Calculate model view transformation
    QMatrix4x4 baseMatrix;
    baseMatrix.translate(0.0, -5.0, -35.0);
    baseMatrix.rotate(rotation);

    QMatrix4x4 matrix(baseMatrix);
    matrix.translate(.0, -5.0, .0);
    program.setUniformValue("mvp", projection * matrix);
    floor->drawGeometry(&program);

    matrix = baseMatrix;
    matrix.translate(20.0, -5.0, -1.0);
    matrix.rotate(10, 0.0, 1.0, 0.0);
    harry->drawGeometry(&program, projection, matrix);

    matrix.rotate(174.3, 0.0, 1.0, 0.0);
    matrix.translate(2.05, 12.0, .5);
    QMatrix4x4 homotetie;
    homotetie.setToIdentity();
    homotetie(0,0) = 1.8-drift/10.;
    matrix *= homotetie;
    program.setUniformValue("mvp", projection * matrix);
    rightLightning->drawGeometry(&program);

    matrix = baseMatrix;
    matrix.translate(-20.0, -5.0, 1.0);
    matrix.rotate(190, 0.0, 1.0, 0.0);
    harry->drawGeometry(&program, projection, matrix);

    matrix.rotate(174.3, 0.0, 1.0, 0.0);
    matrix.translate(2.05, 12.0, .5);
    homotetie(0,0) = 1.8+drift/10.;
    matrix *= homotetie;
    program.setUniformValue("mvp", projection * matrix);
    leftLightning->drawGeometry(&program);

    // Bind shader pipeline for use
    if (!particleShaders.bind())
        close();
    matrix = baseMatrix;
    matrix.translate(.0, 7., .0);
    middleFountain->setPos(QVector3D(drift,.0,.0));
    middleFountain->drawGeometry(&particleShaders, (int)overallTimer.elapsed(), projection * matrix, matrix);
    leftFountain->setPos(QVector3D(drift,.0,.0));
    leftFountain->drawGeometry(&particleShaders, (int)overallTimer.elapsed(), projection * matrix, matrix);
    rightFountain->setPos(QVector3D(drift,.0,.0));
    rightFountain->drawGeometry(&particleShaders, (int)overallTimer.elapsed(), projection * matrix, matrix);
    if (drift < -16.)
    {
        drift+=.6;
    }
    else if (drift > 16.)
    {
        drift-=.6;
    }
    else
    {
        if (randomOn) {
            drift += 0.4 - rand()*0.8/RAND_MAX;
        }
    }

}
