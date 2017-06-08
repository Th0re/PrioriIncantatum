#include "particulefountain.h"

//ParticuleFountain::ParticuleFountain(int nbOfParticules, float width, float top, float bottom)
//{
//}

ParticuleFountain::ParticuleFountain(int nbParticles)
{
    particle = new Particle();
    this->nbParticles = nbParticles;
    for (int i = 0; i < nbParticles; i++) {
        angles.append(3.14*random());
    }
}

ParticuleFountain::~ParticuleFountain()
{
    delete particle;
}

void ParticuleFountain::drawGeometry(QOpenGLShaderProgram *particleShader, int elapsedTime)
{
    for (int i = 0; i < nbParticles; i++) {
        particleShader->setUniformValue("time", elapsedTime);
        particleShader->setAttributeValue("index", i/(float)nbParticles);
        particleShader->setAttributeValue("angle", angles[i]);
        particle->drawGeometry(particleShader);
    }
}
