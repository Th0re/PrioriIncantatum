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
    ParticuleFountain(int nbParticles, QVector3D color, QMatrix4x4 rotationMatrix, float speedFactor, float pointSize, int lifespan, float baseWeight, float maxDrift);
    ParticuleFountain() : ParticuleFountain(10000, QVector3D(1.0,1.0,1.0), QMatrix4x4(), 80., 5., 2000, 16., 10.) {}

    virtual ~ParticuleFountain();

    void drawGeometry(QOpenGLShaderProgram *particleShader, int elapsedTime);

    QVector3D getPos() { return pos; }
    void setPos(QVector3D newPos) { pos = newPos; }

private:
    struct Particle
    {
        float weight;
        QVector3D speed;
        QVector3D position;
        float lifespan;
        int lastUpdate;
        QVector3D color;
        void init(QMatrix4x4 rotationMatrix, float speedFactor, float baseWeight, int lifespan, QVector3D pos, int elapsedTime, QVector3D color);
        bool update(int elapsedTime, int maxLifespan);
    };

    struct ParticleBufferData
    {
        QVector3D position;
        QVector4D color;
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
    QVector3D color;

    QOpenGLBuffer arrayBuf;
    QList<Particle> particles;
    ParticleBufferData *particlesData;

};

#endif // PARTICULEFOUNTAIN_H
