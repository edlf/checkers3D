/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Light class methods.
 */

#include "include/geLight.hpp"
#include "include/gePrimitive.hpp"

unsigned short int geLight::currentNumberOfLights = 0;

geOmniLight::geOmniLight(bool iEnable, gePoint iLocation, geColor iAmbient, geColor iDiffuse, geColor iSpecular) {
    if (currentNumberOfLights < 8) {
        this->openGLid = GL_LIGHT0 + currentNumberOfLights;
        currentNumberOfLights++;
    } else {
        throw geException("Too many lights exist!", true);
    }

    this->enabled = iEnable;

    setLocation(iLocation);
    setAmbient(iAmbient);
    setDiffuse(iDiffuse);
    setSpecular(iSpecular);

    gluQuadric = gluNewQuadric();
}

geSpotLight::geSpotLight(bool iEnable, gePoint iLocation, geColor iAmbient, geColor iDiffuse, geColor iSpecular, GLdouble iSpotAngle, GLdouble iSpotExponent, gePoint iSpotDirection) {
    if (currentNumberOfLights < 8) {
        this->openGLid = GL_LIGHT0 + currentNumberOfLights;
        currentNumberOfLights++;
    } else {
        throw geException("Too many lights exist!", true);
    }

    this->enabled = iEnable;

    setLocation(iLocation);
    setAmbient(iAmbient);
    setDiffuse(iDiffuse);
    setSpecular(iSpecular);

    setAngle(iSpotAngle);
    setExponent(iSpotExponent);
    setDirection(iSpotDirection);

    gluQuadric = gluNewQuadric();
}

/* Sets */
void geLight::setLocation(GLdouble iX, GLdouble iY, GLdouble iZ) {
    this->location[0] = (GLfloat) iX;
    this->location[1] = (GLfloat) iY;
    this->location[2] = (GLfloat) iZ;
    this->location[3] = 1.0f;
}

void geLight::setLocation(gePoint input) {
    setLocation(input.x, input.y, input.z);
}

void geLight::setAmbient(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha) {
    this->ambient[0] = (GLfloat) iR;
    this->ambient[1] = (GLfloat) iG;
    this->ambient[2] = (GLfloat) iB;
    this->ambient[3] = (GLfloat) iAlpha;
}

void geLight::setAmbient(geColor input) {
    setAmbient(input.r, input.g, input.b, input.a);
}

void geLight::setDiffuse(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha) {
    this->diffuse[0] = (GLfloat) iR;
    this->diffuse[1] = (GLfloat) iG;
    this->diffuse[2] = (GLfloat) iB;
    this->diffuse[3] = (GLfloat) iAlpha;
}

void geLight::setDiffuse(geColor input) {
    setDiffuse(input.r, input.g, input.b, input.a);
}

void geLight::setSpecular(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha) {
    this->specular[0] = (GLfloat) iR;
    this->specular[1] = (GLfloat) iG;
    this->specular[2] = (GLfloat) iB;
    this->specular[3] = (GLfloat) iAlpha;
}

void geLight::setSpecular(geColor input) {
    setSpecular(input.r, input.g, input.b, input.a);

}

void geSpotLight::setAngle(GLdouble input) {
    this->angle = (GLfloat) input;
}

void geSpotLight::setExponent(GLdouble input) {
    this->exponent[0] = (GLfloat) input;
}

void geSpotLight::setDirection(GLdouble iX, GLdouble iY, GLdouble iZ) {
    this->direction[0] = (GLfloat) iX;
    this->direction[1] = (GLfloat) iY;
    this->direction[2] = (GLfloat) iZ;
    this->direction[3] = 0.0f;
}

void geSpotLight::setDirection(gePoint input) {
    setDirection(input.x, input.y, input.z);
}

void geLight::toggleEnable() {
    this->enabled = !(this->enabled);
}

/* Gets */
bool geLight::getLightEnableStatus() {
    return (enabled);
}

void geOmniLight::draw() {
    update();
#ifdef LIGHT_SPHERE_ENABLED
    /* Draw sphere in the light location */
    glPushMatrix();
    glTranslated(location[0], location[1], location[2]);
    gluSphere(gluQuadric, 0.1, 16, 16);
    glPopMatrix();
#endif
}

void geSpotLight::draw() {
    update();
#ifdef LIGHT_SPHERE_ENABLED
    /* Draw sphere in the light location */
    glPushMatrix();
    glTranslated(location[0], location[1], location[2]);
    gluSphere(gluQuadric, 0.1, 16, 16);
    glPopMatrix();
#endif
}

void geOmniLight::update() {
    if (enabled) {
        glEnable(openGLid);

        glLightfv(openGLid, GL_AMBIENT, ambient);
        glLightfv(openGLid, GL_DIFFUSE, diffuse);
        glLightfv(openGLid, GL_SPECULAR, specular);
        glLightfv(openGLid, GL_POSITION, location);

    } else {
        glDisable(openGLid);
    }

}

void geSpotLight::update() {
    if (enabled) {
        glEnable(openGLid);

        glLightfv(openGLid, GL_AMBIENT, ambient);
        glLightfv(openGLid, GL_DIFFUSE, diffuse);
        glLightfv(openGLid, GL_SPECULAR, specular);
        glLightfv(openGLid, GL_POSITION, location);
        glLightfv(openGLid, GL_SPOT_DIRECTION, direction);
        glLightfv(openGLid, GL_SPOT_EXPONENT, exponent);

    } else {
        glDisable(openGLid);
    }

}

void geLight::enable() {
    this->enabled = true;
    update();
}

void geLight::disable() {
    this->enabled = false;
    update();
}

