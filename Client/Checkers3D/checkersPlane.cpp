/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#include "include/checkersPlane.hpp"

checkersPlane::checkersPlane(void) {
    numberOfDivisions = 1;
    _s = 1;
    _t = 1;
}

checkersPlane::checkersPlane(unsigned int n) {
    numberOfDivisions = n;
    _s = 1;
    _t = 1;
}

checkersPlane::checkersPlane(unsigned int n, GLdouble s, GLdouble t) {
    numberOfDivisions = n;
    _s = s;
    _t = t;
}

checkersPlane::~checkersPlane(void) {
}

void checkersPlane::draw() {
    glPushMatrix();
    glFrontFace(GL_CW);
    glTranslated(-0.5, 0.0, -0.5);
    glScaled(1.0 / numberOfDivisions, 1, 1.0 / numberOfDivisions);
    glNormal3d(0, -1, 0);

    for (unsigned int bx = 0; bx < numberOfDivisions; bx++) {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d((double) bx / numberOfDivisions, 0);
        glVertex3d((double) bx, 0, 0);

        for (unsigned int bz = 0; bz < numberOfDivisions; bz++) {
            glTexCoord2d(((double) bx + 1.0) / numberOfDivisions, (double) bz / numberOfDivisions);
            glVertex3d((double) bx + 1.0, 0.0, (double) bz);

            glTexCoord2d( (double) bx / numberOfDivisions, ((double) bz + 1.0) / numberOfDivisions);
            glVertex3d((double) bx, 0.0, (double) bz + 1.0);
        }

        glTexCoord2d(((double) bx + 1.0) / numberOfDivisions, 1.0);
        glVertex3d((double) bx + 1.0, 0.0, (double) numberOfDivisions);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glEnd();
    }

    glPopMatrix();
    glFrontFace(GL_CCW);
}
