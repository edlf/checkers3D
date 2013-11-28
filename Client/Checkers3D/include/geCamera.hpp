/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Camera class, UI camera stolen from CGFlib.
 */

#ifndef GECAMERA_HPP_
#define GECAMERA_HPP_

#include "hoIncludes.hpp"

class geCamera {
protected:
    GLdouble geNear, geFar;
    GLdouble position[3];
    GLdouble rotation[3];

public:
    geCamera();
    geCamera(GLdouble iNear, GLdouble iFar);

    GLdouble getNear();
    GLdouble getFar();

    /* applyView must be overridden, else nothing will happen */
    virtual void applyView(double aspectRatio);

    void setPosition(gePoint in);
    void setX(GLdouble x);
    void setY(GLdouble y);
    void setZ(GLdouble z);

    virtual void rotateTo(int axis, float angle);
    virtual void rotate(int axis, float angle);
    virtual void setRotation(int axis, float angle);
    virtual void moveTo(int axis, float value, float increment);
    virtual void translate(int axis, float value);
	virtual void printInfo();
	virtual void setPlayerCamera(unsigned short int player);

    virtual ~geCamera();
};

class geCameraOrtho: public geCamera {
private:
    GLdouble left, right, top, bottom;

public:
    geCameraOrtho(GLdouble iNear, GLdouble iFar, GLdouble iLeft, GLdouble iRight, GLdouble iTop, GLdouble iBottom);

    virtual void applyView(double aspectRatio);

	void printInfo();

    virtual ~geCameraOrtho();
};

class geCameraPerspective: public geCamera {
private:
    GLdouble angle;
    GLdouble from[3], to[3];
    /* If examine mode is true, camera has been manipulated by mouse */
    bool examineMode;

public:
    /* Special camera for GUI */
    geCameraPerspective();

    /* Regular camera for xml scene */
    geCameraPerspective(GLdouble iNear, GLdouble iFar, GLdouble iAngle, gePoint iFrom, gePoint iTo);

    virtual void applyView(double aspectRatio);

    virtual void rotateTo(int axis, float angle);   ///< Rotates the camera around _axis_ by _increment_ degrees, unless it has reached _angle_ degrees. Useful for stepping a rotation in an animation.
    virtual void rotate(int axis, float angle);                             ///< Rotates the camera around _axis_ by _angle_ degrees.
    virtual void setRotation(int axis, float angle);                        ///< Sets the rotation around _axis_ to be _angle_ degrees
    virtual void moveTo(int axis, float value, float increment = 0.5f);       ///< Moves the camera along _axis_ by _increment_ units, unless _value_ has been reached.
    virtual void translate(int axis, float value);                          ///< Moves the camera along _axis_ by _value_ units.
	
    void resetCamera();
	void setPlayerCamera(unsigned short int player);
	void printInfo();

    virtual ~geCameraPerspective();
};

#endif
