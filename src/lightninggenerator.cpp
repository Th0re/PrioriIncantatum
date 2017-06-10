#include "lightninggenerator.h"
#include "time.h"
#include "cylinder.h"

LightningGenerator::LightningGenerator()
{
    curDetail = 10;
}

LightningGenerator::LightningGenerator(float prec){
    curDetail = prec;
}

void LightningGenerator::DrawLightning(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B, float displace, QOpenGLShaderProgram *program)
{
  if (displace < curDetail) {
      Cylinder temp = Cylinder(PT_A, COLOR_A, PT_B, COLOR_B); // ajouter le programe en paramètre pour draw les cylindres

      temp.drawGeometry(program);
  }
  else {
    QVector3D PT_MID;
    QVector3D COLOR_MID;

    // Point milieu entre A et B, points centraux des deux faces
    PT_MID.setX((PT_B.x() + PT_A.x())/2);
    PT_MID.setY((PT_B.y() + PT_A.y())/2);
    PT_MID.setZ((PT_B.z() + PT_A.z())/2);

    // Déplacement de ce point milieu de manière aléatoire pour simuler l'irégularité d'un arc électrique
    PT_MID.setX(PT_MID.x() + (rand()/((float)RAND_MAX) - 0.5) * displace);
    PT_MID.setY(PT_MID.y() + (rand()/((float)RAND_MAX) - 0.5) * displace);
    PT_MID.setZ(PT_MID.z() + (rand()/((float)RAND_MAX) - 0.5) * displace);

    //Interpolation linéaire de la couleur
    COLOR_MID.setX((COLOR_A.x() + COLOR_B.x())/2);
    COLOR_MID.setY((COLOR_A.y() + COLOR_B.y())/2);
    COLOR_MID.setZ((COLOR_A.z() + COLOR_B.z())/2);

    displace = displace/2; // plus on avance dans le détail plus les déplacement doivent être petit

    LightningGenerator::DrawLightning(PT_A, COLOR_A, PT_MID, COLOR_MID, displace, program);
    LightningGenerator::DrawLightning(PT_MID, COLOR_MID, PT_B, COLOR_B, displace, program);
  }
}
