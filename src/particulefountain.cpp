#include "particulefountain.h"

#include <QtMath>

//ParticuleFountain::ParticuleFountain(int nbOfParticules, float width, float top, float bottom)
//{
//}

struct ParticleData
{
    float index;
    float weight;
    QVector3D baseSpeed;
    float lifespan;
};

ParticuleFountain::ParticuleFountain(int nbParticles)
{
    initializeOpenGLFunctions();

    QImage image = QImage(QString(":/particle.bmp"), "BMP");
    if (image.isNull()) {
        throw 42;
    } else {
        texture = new QOpenGLTexture(image);
    }

    this->nbParticles = nbParticles;
    arrayBuf.create();

    initGeometry();

}

ParticuleFountain::~ParticuleFountain()
{
    arrayBuf.destroy();
    delete texture;
}

// return a random float between 0 and 1
float rnd() {
    return random()/((float)RAND_MAX);
}

void ParticuleFountain::initGeometry() {

    ParticleData particles[nbParticles];

    for (int i = 0; i < nbParticles; i++) {
        ParticleData particle;
        particle.weight = 8. + 4.*rnd();
        particle.index = i/(float)nbParticles;
        qreal angle = M_PI*2*rnd();
        float dist = 40. + 40.*rnd();
        QVector3D speed(dist*qCos(angle), 60.+30.*rnd(),dist*qSin(angle));
        particle.baseSpeed = speed;
        particle.lifespan = 20000;

        particles[i] =  particle;
    }

    arrayBuf.bind();
    arrayBuf.allocate(particles, nbParticles*sizeof(ParticleData));
}

void ParticuleFountain::drawGeometry(QOpenGLShaderProgram *particleShader, int elapsedTime)
{


    arrayBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int indexLocation = particleShader->attributeLocation("index");
    particleShader->enableAttributeArray(indexLocation);
    particleShader->setAttributeBuffer(indexLocation, GL_FLOAT, offset, 3, sizeof(ParticleData));

    // Offset for texture coordinate
    offset += sizeof(float);

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int weightLocation = particleShader->attributeLocation("weight");
    particleShader->enableAttributeArray(weightLocation);
    particleShader->setAttributeBuffer(weightLocation, GL_FLOAT, offset, 3, sizeof(ParticleData));

    // Offset for texture coordinate
    offset += sizeof(float);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int baseSpeedLocation = particleShader->attributeLocation("baseSpeed");
    particleShader->enableAttributeArray(baseSpeedLocation);
    particleShader->setAttributeBuffer(baseSpeedLocation, GL_FLOAT, offset, 3, sizeof(ParticleData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int lifespanLocation = particleShader->attributeLocation("lifespan");
    particleShader->enableAttributeArray(lifespanLocation);
    particleShader->setAttributeBuffer(lifespanLocation, GL_FLOAT, offset, 3, sizeof(ParticleData));


    particleShader->setUniformValue("time", elapsedTime);

    texture->bind();

    glPointSize(25.);
    glDrawArrays(GL_POINTS, 0, nbParticles);
}
