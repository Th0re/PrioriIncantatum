#include "particulefountain.h"

#include <QtMath>


ParticuleFountain::ParticuleFountain(int nbParticles, QVector3D color,
                         QMatrix4x4 rotationMatrix, float speedFactor,
                         float pointSize, int lifespan, float baseWeight, float maxDrift)
{
    initializeOpenGLFunctions();

    this->color = color;
    this->pointSize = pointSize;
    this->maxDrift = maxDrift;
    this->pos = QVector3D();
    this->lifespan = lifespan;

    QImage image = QImage(QString(":/particle.bmp"), "BMP");
    if (image.isNull()) {
        throw 42;
    } else {
        texture = new QOpenGLTexture(image);
    }

    this->nbParticles = nbParticles;
    arrayBuf.create();

    this->rotationMatrix = rotationMatrix;
    this->speedFactor = speedFactor;
    this->baseWeight = baseWeight;

    this->particlesData = new ParticleBufferData[nbParticles];

    initGeometry();

}

ParticuleFountain::~ParticuleFountain()
{
    arrayBuf.destroy();
    delete texture;
}

// return a random float between 0 and 1
float rnd()
{
    return random()/((float)RAND_MAX);
}

void ParticuleFountain::initGeometry()
{


    for (int i = 0; i < nbParticles; i++)
    {
        Particle particle;
        particle.init(rotationMatrix, speedFactor, baseWeight, lifespan - (int)(i*lifespan/(float)nbParticles), pos, 0, color);
        particles.append(particle);
    }

}

void ParticuleFountain::drawGeometry(QOpenGLShaderProgram *particleShader, int elapsedTime)
{


    arrayBuf.bind();

    for( int i = 0; i < nbParticles; ++i) {
        if (!particles[i].update(elapsedTime, lifespan))
        {
            particles[i].init(rotationMatrix, speedFactor, baseWeight, lifespan, pos, elapsedTime, color);
        }

        particlesData[i].position = particles[i].position;
        float alpha;
        if ( particles[i].lifespan/lifespan > .5)
            alpha = 1.;
        else
            alpha = .5 + .5*particles[i].lifespan/lifespan;
        particlesData[i].color = QVector4D(particles[i].color, alpha);

    }
    arrayBuf.allocate(particlesData, nbParticles*sizeof(ParticleBufferData));


    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int posLocation = particleShader->attributeLocation("pos");
    particleShader->enableAttributeArray(posLocation);
    particleShader->setAttributeBuffer(posLocation, GL_FLOAT, offset, 3, sizeof(ParticleBufferData));

    // Offset for color
    offset = sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex color data
    int colorLocation = particleShader->attributeLocation("color");
    particleShader->enableAttributeArray(colorLocation);
    particleShader->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 4, sizeof(ParticleBufferData));
    texture->bind();

    glPointSize(pointSize);
    glDrawArrays(GL_POINTS, 0, nbParticles);
}

void ParticuleFountain::Particle::init(QMatrix4x4 rotationMatrix, float speedFactor, float baseWeight, int lifespan, QVector3D pos, int elapsedTime, QVector3D color)
{
    this->weight = baseWeight + baseWeight*rnd()/2;
    qreal angle = M_PI*2*rnd();
    float dist = speedFactor + speedFactor*rnd()/2.;
    QVector3D speed(dist*qCos(angle), speedFactor+speedFactor*rnd()/2,dist*qSin(angle));
    this->speed = rotationMatrix * speed;
    this->lifespan = lifespan;
    this->lastUpdate = elapsedTime;
    this->position = pos;
    this->color = color;
}

bool ParticuleFountain::Particle::update(int elapsedTime, int maxLifespan)
{
    int time = elapsedTime - lastUpdate;
    lastUpdate = elapsedTime;

    lifespan -= time;

    if (lifespan > 0) {
        speed += QVector3D(.0, -9.81*time*weight/maxLifespan, .0);
        position += speed*time/maxLifespan;
        return true;
    }
    else
    {
        return false;
    }
}
