#include "particulefountain.h"

//ParticuleFountain::ParticuleFountain(int nbOfParticules, float width, float top, float bottom)
//{
//}

struct ParticleData
{
    float index;
    float angle;
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

void ParticuleFountain::initGeometry() {

    ParticleData particles[nbParticles];

    for (int i = 0; i < nbParticles; i++) {
        ParticleData particle;
        particle.angle = 3.14*2*random()/((float)RAND_MAX);
        particle.index = i/(float)nbParticles;
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

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int angleLocation = particleShader->attributeLocation("angle");
    particleShader->enableAttributeArray(angleLocation);
    particleShader->setAttributeBuffer(angleLocation, GL_FLOAT, offset, 3, sizeof(ParticleData));


    particleShader->setUniformValue("time", elapsedTime);

    texture->bind();

    glPointSize(5.);
    glDrawArrays(GL_POINTS, 0, nbParticles);
}
