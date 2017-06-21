#include "lightninggenerator.h"
#include "time.h"
#include "cylinder.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////
//============================= LIFECYCLE ====================================

LightningGenerator::LightningGenerator()
{
    curDetail = 10;
}

LightningGenerator::LightningGenerator(float prec)
{
    curDetail = prec;
}

//============================= OPERATIONS ===================================

/**************************************************************************
* Name: drawLightning
* Description: Initializes a particle
* Inputs:
- PT_A: center of the first face for the cylinder
- COLOR_A: Color of the first face for the cylinder
- PT_B: center of the second face for the cylinder
- COLOR_B: Color of the second face for the cylinder
- ray: used to create the cylinder
- displace: Base displacement of the point
- *program:
* Returns:
- void
**************************************************************************/
void LightningGenerator::drawLightning(QVector3D PT_A, QVector3D COLOR_A, QVector3D PT_B, QVector3D COLOR_B, float ray,float displace, QOpenGLShaderProgram *program)
{
  if (displace < curDetail)
  {
      Cylinder temp = Cylinder(PT_A, COLOR_A, PT_B, COLOR_B, ray);

      temp.drawGeometry(program);
  }
  else
  {
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

    LightningGenerator::drawLightning(PT_A, COLOR_A, PT_MID, COLOR_MID, ray, displace, program);
    LightningGenerator::drawLightning(PT_MID, COLOR_MID, PT_B, COLOR_B, ray, displace, program);
  }
}
