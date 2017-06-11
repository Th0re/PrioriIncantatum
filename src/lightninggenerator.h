#ifndef LIGHTNINGGENERATOR_H
#define LIGHTNINGGENERATOR_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class LightningGenerator
{
public:
    float curDetail; // Détail que l'on veux sur l'arc

    LightningGenerator(); // Constructeur

    LightningGenerator(float prec);

    void drawLightning(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B, float ray, float displace, QOpenGLShaderProgram *program); // Méthode récursive de création de l'arc
};

#endif // LIGHTNINGGENERATOR_H
