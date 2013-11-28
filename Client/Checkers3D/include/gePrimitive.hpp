/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Primitive class.
 */

#ifndef GEPRIMITIVE_HPP_
#define GEPRIMITIVE_HPP_

#include "hoIncludes.hpp"
#include "geTexture.hpp"
#include "geShader.hpp"

class gePrimitive {
    protected:
        GLdouble normal [3];
        void fghCircleTable (GLdouble **sint, GLdouble **cost, const int n);
        void calculateNormal (GLdouble v [3] [3], GLdouble out [3]);
        void normalizeVector (GLdouble vector [3]);

    public:
        virtual void draw (GLdouble s, GLdouble t);
        virtual ~gePrimitive ();
};

/* Rectangle class */
class geRectangle: public gePrimitive {
    private:
    GLdouble x1, y1, x2, y2;
        //unsigned int _numDivisions, dx, dy;

    public:
        geRectangle (ge2dPoint pt1, ge2dPoint pt2);
        geRectangle (GLdouble inX0, GLdouble inY0, GLdouble inX1, GLdouble inY1);

        void draw (GLdouble s, GLdouble t);
};

/* Cylinder */
class geCylinder: public gePrimitive {
    private:
        GLint slices, stacks;
        GLdouble baseRadius, topRadius, height;

        /* Internal precalc tables */
        GLdouble *sinCache;
        GLdouble *cosCache;
        GLdouble *sinCache2;
        GLdouble *cosCache2;
        GLdouble *sinCache3;
        GLdouble *cosCache3;

        /* Internal precalc vars */
        GLdouble angleStep;
        GLdouble zNormal;

        GLdouble deltaRadius, deltaAngle;

    public:
        geCylinder (GLdouble iBase, GLdouble iTop, GLdouble iHeight, unsigned int iSlices, unsigned int iStacks);

        void draw (GLdouble s, GLdouble t);

        void drawCircle (GLdouble radius);

        ~geCylinder ();
};

/* Sphere */
class geSphere: public gePrimitive {
    private:
        int slices, stacks;
        GLdouble radius;

        double *sint1, *cost1;
        double *sint2, *cost2;

    public:
        geSphere (GLdouble iRadius, int iSlices, int iStacks);

        void draw (GLdouble s, GLdouble t);

        ~geSphere ();
};

#endif /* GEPRIMITIVE_HPP_ */
