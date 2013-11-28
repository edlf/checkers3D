/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Camera class methods.
 */

#include "include/geCamera.hpp"

geCamera::geCamera(){
    this->geNear = 0;
    this->geFar = 500;
}

geCamera::geCamera(GLdouble iNear, GLdouble iFar) {
    this->geNear = iNear;
    this->geFar = iFar;
}

GLdouble geCamera::getNear() {
    return (this->geNear);
}

GLdouble geCamera::getFar() {
    return (this->geFar);
}

void geCamera::applyView(double aspectRatio) {
    /* Empty function, look at ortho or perspective cameras */
    (void) aspectRatio;
}

void geCamera::setPosition(gePoint in) {
    setX(in.x);
    setY(in.y);
    setZ(in.z);
}

void geCamera::setX(GLdouble x) {
    this->position[0] = x;
}

void geCamera::setY(GLdouble y) {
    this->position[1] = y;
}

void geCamera::setZ(GLdouble z) {
    this->position[2] = z;
}

void geCamera::rotateTo(int axis, float angle){
    (void) axis;
    (void) angle;
}

void geCamera::rotate(int axis, float angle){
    (void) axis;
    (void) angle;
}

void geCamera::setRotation(int axis, float angle){
    (void) axis;
    (void) angle;
}

void geCamera::moveTo(int axis, float value, float increment){
    (void) axis;
    (void) value;
    (void) increment;
}

void geCamera::translate(int axis, float value){
    (void) axis;
    (void) value;
}

void geCamera::printInfo(){
}

void geCamera::setPlayerCamera(unsigned short int player){
}

geCamera::~geCamera() {

}

geCameraOrtho::geCameraOrtho(GLdouble iNear, GLdouble iFar, GLdouble iLeft, GLdouble iRight, GLdouble iTop, GLdouble iBottom) :
        geCamera(iNear, iFar) {

    this->left = iLeft;
    this->right = iRight;
    this->top = iTop;
    this->bottom = iBottom;
}

void geCameraOrtho::applyView(double aspectRatio) {
    (void) aspectRatio;
    glOrtho(this->left, this->right, this->bottom, this->top, this->geNear, this->geFar);
}

void geCameraOrtho::printInfo(){
}


geCameraOrtho::~geCameraOrtho() {

}

geCameraPerspective::geCameraPerspective() {
    angle = 0;

    position[0] = 0;
    position[1] = 0;
    position[2] = -25;

    rotation[0] = 45;
    rotation[1] = 0;
    rotation[2] = 0;

    to[0] = 0;
    to[1] = 0;
    to[2] = 0;

    this->examineMode = true;
}

geCameraPerspective::geCameraPerspective(GLdouble iNear, GLdouble iFar, GLdouble iAngle, gePoint iFrom, gePoint iTo) :
        geCamera(iNear, iFar) {

    this->angle = iAngle;
    this->from[0] = iFrom.x;
    this->from[1] = iFrom.y;
    this->from[2] = iFrom.z;
    this->to[0] = iTo.x;
    this->to[1] = iTo.y;
    this->to[2] = iTo.z;

    this->examineMode = false;
}

void geCameraPerspective::applyView(double aspectRatio) {
    if (this->examineMode) {
        glFrustum(-aspectRatio * .04, aspectRatio * .04, -.04, .04, .1, 500.0);

        glTranslated(position[0], position[1], position[2]);

        glRotated(rotation[0], 1.f, 0.f, 0.f);
        glRotated(rotation[1], 0.f, 1.f, 0.f);
        glRotated(rotation[2], 0.f, 0.f, 1.f);

    } else {

        gluPerspective(this->angle, aspectRatio, this->geNear, this->geFar);
        gluLookAt(this->from[0], this->from[1], this->from[2], this->to[0], this->to[1], this->to[2], 0, 1, 0);

    }
}

void geCameraPerspective::rotateTo(int axis, float angle) {
    if (axis >= 0 && axis <= 2) {
        if (rotation[axis] < angle) {
            rotation[axis] += 0.5f;
        }
    }
}

void geCameraPerspective::rotate(int axis, float angle) {
    if (axis >= 0 && axis <= 2) {
        rotation[axis] += angle;
    }
}

void geCameraPerspective::setRotation(int axis, float angle) {
    if (axis >= 0 && axis <= 2) {
        rotation[axis] = angle;
    }
}

void geCameraPerspective::moveTo(int axis, float value, float increment) {
    if (axis >= 0 && axis <= 2) {
        if (position[axis] < value) {
            rotation[axis] += increment;
        }
    }
}

void geCameraPerspective::translate(int axis, float value) {
    this->examineMode = true;
    ///< Moves the camera along _axis_ by _value_ units.
    if (axis >= 0 && axis <= 2) {
        position[axis] += value;
    }
}

void geCameraPerspective::resetCamera() {
    angle = 0;

	position[0] = 0;
	position[1] = 0;
	position[2] = -22.25;

	rotation[0] = 55;
	rotation[1] = 0;
	rotation[2] = 0;

    to[0] = 0;
    to[1] = 0;
    to[2] = 0;
}

void geCameraPerspective::printInfo(){
	if (examineMode) {
			std::cout << "Position: ";
			std::cout << "X: " << position[0] << " Y:" << position[1] << " Z:" << position[2] << std::endl;
			std::cout << "Rotation: ";
			std::cout << "X: " << rotation[0] << " Y:" << rotation[1] << " Z:" << rotation[2] << std::endl;
	}
}

void geCameraPerspective::setPlayerCamera(unsigned short int player) {
	if (player == 1) {
		position[0] = 0;
		position[1] = 0;
		position[2] = -22.25;

		rotation[0] = 55;
		rotation[1] = 0;
		rotation[2] = 0;
	}

	if (player == 3) {
		position[0] = 0;
		position[1] = 0;
		position[2] = -22.25;

		rotation[0] = 55;
		rotation[1] = 180;
		rotation[2] = 0;
	}
}

geCameraPerspective::~geCameraPerspective() {

}
