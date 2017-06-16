#ifndef PARTICULEFOUNTAIN_H
#define PARTICULEFOUNTAIN_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

class ParticuleFountain : protected QOpenGLFunctions
{
public:
//    ParticuleFountain(int nbOfParticules, float width, float top, float bottom);
    ParticuleFountain(int nbParticles, QVector4D color, QMatrix4x4 rotationMatrix, float speedFactor, float pointSize, int lifespan, float baseWeight, float maxDrift);
    ParticuleFountain() : ParticuleFountain(100000, QVector4D(1.0,1.0,1.0,1.0), QMatrix4x4(), 80., 5., 2000, 16., 10.) {}

    virtual ~ParticuleFountain();

    void drawGeometry(QOpenGLShaderProgram *particleShader, int elapsedTime);

    QVector3D getPos() { return pos; }
    void setPos(QVector3D newPos) { pos = newPos; }

private:
    struct ParticleData
    {
        float weight;
        QVector3D speed;
        QVector3D position;
        float lifespan;
        int lastUpdate;
        void init(QMatrix4x4 rotationMatrix, float speedFactor, float baseWeight, int lifespan, QVector3D pos, int elapsedTime);
        bool update(int elapsedTime, int maxLifespan);
    };

    void initGeometry();
    int nbParticles;
    float pointSize;
    QVector3D pos;
    QVector3D speed;
    int lifespan;
    float maxDrift;

    QMatrix4x4 rotationMatrix;
    float speedFactor;
    float baseWeight;

    QOpenGLTexture *texture;
    QVector4D color;

    QOpenGLBuffer arrayBuf;
    QList<ParticleData> particles;
    QVector3D *particlesPos;

};

#endif // PARTICULEFOUNTAIN_H
