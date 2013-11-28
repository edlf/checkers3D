/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Light class.
 */

#include "hoIncludes.hpp"

using namespace std;

class geLight {
protected:
    GLenum openGLid;
    bool enabled;

    GLfloat location[4];
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];

    /* Internal */
    static unsigned short int currentNumberOfLights;
    GLUquadric* gluQuadric;
    GLfloat kc, kl, kq;

public:
    /* Sets */
    void setLocation(GLdouble iX, GLdouble iY, GLdouble iZ);
    void setLocation(gePoint input);
    void setAmbient(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha);
    void setAmbient(geColor input);
    void setDiffuse(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha);
    void setDiffuse(geColor input);
    void setSpecular(GLdouble iR, GLdouble iG, GLdouble iB, GLdouble iAlpha);
    void setSpecular(geColor input);

    void toggleEnable();

    /* Gets */
    bool getLightEnableStatus();

    virtual void draw() {
    }
    virtual void update() {
    }
    void enable();
    void disable();

    virtual ~geLight() {
    }
};

class geOmniLight: public geLight {
protected:

public:
    geOmniLight(bool iEnable, gePoint iLocation, geColor iAmbient, geColor iDiffuse, geColor iSpecular);

    void draw();
    void update();
    virtual ~geOmniLight() {
    }
};

class geSpotLight: public geLight {
protected:
    GLfloat angle;
    GLfloat exponent[1];
    GLfloat direction[4];

public:
    geSpotLight(bool iEnable, gePoint iLocation, geColor iAmbient, geColor iDiffuse, geColor iSpecular, GLdouble iAngle, GLdouble iExponent, gePoint iDirection);

    void setAngle(GLdouble input);
    void setExponent(GLdouble input);
    void setDirection(GLdouble iX, GLdouble iY, GLdouble iZ);
    void setDirection(gePoint input);

    void draw();
    void update();
    virtual ~geSpotLight() {
    }
};
