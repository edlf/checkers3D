/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Transform class.
 */

#ifndef GETRANSFORM_HPP_
#define GETRANSFORM_HPP_

#include "hoIncludes.hpp"

class geTransform {
protected:
    int transformNumber;
    GLdouble matrix[16];

public:
    geTransform(int number);

    virtual GLdouble* getTransformationMatrix();
    virtual void apply();

    virtual ~geTransform();
};

class geTransformTranslate: public geTransform {
private:
    GLdouble destination[3];

public:
    geTransformTranslate(gePoint in, int tN);
    geTransformTranslate(GLdouble x, GLdouble y, GLdouble z, int tN);

    GLdouble* getTransformationMatrix();

    void apply();
};

class geTransformRotate: public geTransform {
private:
    GLdouble axisArray[3];
    GLdouble angle;
    GLdouble angleRad;

    unsigned int getAxisId();

public:
    geTransformRotate(int iAxis, GLdouble iAngle, int tN);

    GLdouble* getTransformationMatrix();

    void apply();

};

class geTransformScale: public geTransform {
private:
    GLdouble scaleFactor[3];
public:
    geTransformScale(gePoint in, int tN);
    geTransformScale(GLdouble x, GLdouble y, GLdouble z, int tN);

    GLdouble* getTransformationMatrix();

    void apply();

};

#endif /* GETRANSFORM_HPP_ */
