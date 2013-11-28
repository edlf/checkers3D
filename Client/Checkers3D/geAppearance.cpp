/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Appearance class methods.
 */

#include "include/geAppearance.hpp"

/* Creates a black appearance */
geAppearance::geAppearance() {
    setEmissive (0, 0, 0, 0);
    setAmbient  (0, 0, 0, 0);
    setDiffuse  (0, 0, 0, 0);
    setSpecular (0, 0, 0, 0);
    setShininess(0);
}

geAppearance::geAppearance(geColor iEmissive, geColor iAmbient, geColor iDiffuse, geColor iSpecular, GLdouble iShininess) {
    setEmissive(iEmissive);
    setAmbient(iAmbient);
    setDiffuse(iDiffuse);
    setSpecular(iSpecular);
    setShininess(iShininess);
}

void geAppearance::apply() {
    glDisable(GL_COLOR_MATERIAL);
    glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient);
}

void geAppearance::setEmissive(geColor input) {
    setEmissive(input.r, input.g, input.b, input.a);
}

void geAppearance::setEmissive(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha) {
    this->emissive[0] = (GLfloat) iR;
    this->emissive[1] = (GLfloat) iG;
    this->emissive[2] = (GLfloat) iB;
    this->emissive[3] = (GLfloat) iAlpha;
}

void geAppearance::setAmbient(geColor input) {
    setAmbient(input.r, input.g, input.b, input.a);

}

void geAppearance::setAmbient(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha) {
    this->ambient[0] = (GLfloat) iR;
    this->ambient[1] = (GLfloat) iG;
    this->ambient[2] = (GLfloat) iB;
    this->ambient[3] = (GLfloat) iAlpha;
}

void geAppearance::setDiffuse(geColor input) {
    setDiffuse(input.r, input.g, input.b, input.a);
}

void geAppearance::setDiffuse(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha) {
    this->diffuse[0] = (GLfloat) iR;
    this->diffuse[1] = (GLfloat) iG;
    this->diffuse[2] = (GLfloat) iB;
    this->diffuse[3] = (GLfloat) iAlpha;
}

void geAppearance::setSpecular(geColor input) {
    setSpecular(input.r, input.g, input.b, input.a);
}

void geAppearance::setSpecular(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha) {
    this->specular[0] = (GLfloat) iR;
    this->specular[1] = (GLfloat) iG;
    this->specular[2] = (GLfloat) iB;
    this->specular[3] = (GLfloat) iAlpha;
}

void geAppearance::setShininess(GLdouble input) {
    this->shininess = (GLfloat) input;
    // this->materialType = MATERIAL_TYPE_MATERIAL;
}

geAppearance::~geAppearance() {

}
