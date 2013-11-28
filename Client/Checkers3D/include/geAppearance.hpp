/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Appearance class.
 */

#ifndef GEAPPEARANCE_HPP_
#define GEAPPEARANCE_HPP_

#include "hoIncludes.hpp"
#include "geTexture.hpp"

#define MATERIAL_TYPE_COLOR 0
#define MATERIAL_TYPE_MATERIAL 1

using namespace std;

class geAppearance {
private:
    GLfloat emissive[4];
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;

public:
    geAppearance();
    geAppearance(geColor iEmissive, geColor iAmbient, geColor iDiffuse, geColor iSpecular, GLdouble iShininess);

    void apply();

    void setEmissive(geColor input);
    void setEmissive(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha);
    void setAmbient(geColor input);
    void setAmbient(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha);
    void setDiffuse(geColor input);
    void setDiffuse(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha);
    void setSpecular(geColor input);
    void setSpecular(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha);
    void setShininess(GLdouble input);

    virtual ~geAppearance();
};

#endif
