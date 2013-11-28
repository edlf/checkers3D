/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Primitive class methods.
 */

#include "include/gePrimitive.hpp"

/* Copy from GLUT
 * Compute lookup table of cos and sin values forming a circle
 *
 * Notes:
 *    It is the responsibility of the caller to free these tables
 *    The size of the table is (n+1) to form a connected loop
 *    The last entry is exactly the same as the first
 *    The sign of n can be flipped to get the reverse loop
 */

/* Primitive super class */
void gePrimitive::fghCircleTable(double **sint, double **cost, const int n) {
    unsigned int i;

    /* Table size, the sign of n flips the circle direction */

    const size_t size = (size_t) abs(n);

    /* Determine the angle between samples */

    const double angle = 2 * M_PI / (double) ((n == 0) ? 1 : n);

    /* Allocate memory for n samples, plus duplicate of first entry at the end */

    *sint = (double *) calloc(sizeof(double), size + 1);
    *cost = (double *) calloc(sizeof(double), size + 1);

    /* Bail out if memory allocation fails */

    if (!(*sint) || !(*cost)) {
        free(*sint);
        free(*cost);
        throw geException("Failed to allocate memory in fghCircleTable.", true);
    }

    /* Compute cos and sin around the circle */

    (*sint)[0] = 0.0;
    (*cost)[0] = 1.0;

    for (i = 1; i < size; i++) {
        (*sint)[i] = sin(angle * i);
        (*cost)[i] = cos(angle * i);
    }

    /* Last sample is duplicate of the first */

    (*sint)[size] = (*sint)[0];
    (*cost)[size] = (*cost)[0];
}

/* Calculates Normal For A Quad Using 3 Points */
void gePrimitive::calculateNormal(GLdouble v[3][3], GLdouble out[3]) {
    GLdouble v1[3], v2[3];                      // Vector 1 (x,y,z) & Vector 2 (x,y,z)
    static const int x = 0;                     // Define X Coord
    static const int y = 1;                     // Define Y Coord
    static const int z = 2;                     // Define Z Coord

    // Finds The Vector Between 2 Points By Subtracting
    // The x,y,z Coordinates From One Point To Another.

    // Calculate The Vector From Point 1 To Point 0
    v1[x] = v[0][x] - v[1][x];                  // Vector 1.x=Vertex[0].x-Vertex[1].x
    v1[y] = v[0][y] - v[1][y];                  // Vector 1.y=Vertex[0].y-Vertex[1].y
    v1[z] = v[0][z] - v[1][z];                  // Vector 1.z=Vertex[0].y-Vertex[1].z
    // Calculate The Vector From Point 2 To Point 1
    v2[x] = v[1][x] - v[2][x];                  // Vector 2.x=Vertex[0].x-Vertex[1].x
    v2[y] = v[1][y] - v[2][y];                  // Vector 2.y=Vertex[0].y-Vertex[1].y
    v2[z] = v[1][z] - v[2][z];                  // Vector 2.z=Vertex[0].z-Vertex[1].z
    // Compute The Cross Product To Give Us A Surface Normal
    out[x] = v1[y] * v2[z] - v1[z] * v2[y];             // Cross Product For Y - Z
    out[y] = v1[z] * v2[x] - v1[x] * v2[z];             // Cross Product For X - Z
    out[z] = v1[x] * v2[y] - v1[y] * v2[x];             // Cross Product For X - Y

    normalizeVector(out);
}

void gePrimitive::normalizeVector(GLdouble vector[3]) {
    GLdouble length;

    /* Vector Length */
    length = sqrt((vector[0] * vector[0]) + (vector[1] * vector[1]) + (vector[2] * vector[2]));

    if (length == 0.0) {
        length = 1.0;
    }

    vector[0] /= length;
    vector[1] /= length;
    vector[2] /= length;
}

void gePrimitive::draw(GLdouble s, GLdouble t) {
    /* Prevent warnings */
    (void) s;
    (void) t;
}

gePrimitive::~gePrimitive() {
}

/* Rectangle primitive */
geRectangle::geRectangle(ge2dPoint pt1, ge2dPoint pt2) {
    /* Check if rectangle is valid */
    if (pt1.x == pt2.x || pt1.y == pt2.y) {
        throw geException("Invalid rectangle defined: the sides must not be equal!", true);
    }

    x1 = pt1.x;
    y1 = pt1.y;
    x2 = pt2.x;
    y2 = pt2.y;

    /* end */
}

geRectangle::geRectangle(GLdouble inX0, GLdouble inY0, GLdouble inX1, GLdouble inY1) {
    /* Check if rectangle is valid */
    if (inX0 == inX1 || inY0 == inY1) {
        throw geException("Invalid rectangle defined: the sides must not be equal!", true);
    }

    x1 = inX0;
    y1 = inY0;
    x2 = inX1;
    y2 = inY1;

    /* end */
}

void geRectangle::draw(GLdouble s, GLdouble t) {
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glBegin(GL_POLYGON);
    if ((this->y2 < this->y1) && (this->x2 < this->x1)) {
        glNormal3d(0.0, 0.0, -1.0);
        glTexCoord2d(0.0, 0.0);
        glVertex3d(this->x2, this->y2, 0.0);
        glTexCoord2d((this->x1 - this->x2) / s, 0.0);
        glVertex3d(this->x1, this->y2, 0.0);
        glTexCoord2d((this->x2 - this->x1) / s, (this->y2 - this->y1) / t);
        glVertex3d(this->x1, this->y1, 0.0);
        glTexCoord2d(0.0, (this->y2 - this->y1) / t);
        glVertex3d(this->x2, this->y1, 0.0);
    } else {
        glNormal3d(0.0, 0.0, 1.0);
        glTexCoord2d(0.0, 0.0);
        glVertex3d(this->x1, this->y1, 0.0);
        glTexCoord2d((this->x2 - this->x1) / s, 0.0);
        glVertex3d(this->x2, this->y1, 0.0);
        glTexCoord2d((this->x2 - this->x1) / s, (this->y2 - this->y1) / t);
        glVertex3d(this->x2, this->y2, 0.0);
        glTexCoord2d(0.0, (this->y2 - this->y1) / t);
        glVertex3d(this->x1, this->y2, 0.0);
    }

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/* Cylinder primitive */
geCylinder::geCylinder(GLdouble iBase, GLdouble iTop, GLdouble iHeight, unsigned int iSlices, unsigned int iStacks) {
    this->baseRadius = iBase;
    this->topRadius = iTop;
    this->height = iHeight;
    this->slices = (GLint) iSlices;
    this->stacks = (GLint) iStacks;

    this->angleStep = 2 * M_PI / slices;

    /* Precalc */

    /* Allocs */
    sinCache = (GLdouble *) calloc(sizeof(GLdouble), (size_t) slices + 1);
    cosCache = (GLdouble *) calloc(sizeof(GLdouble), (size_t) slices + 1);
    sinCache2 = (GLdouble *) calloc(sizeof(GLdouble), (size_t) slices + 1);
    cosCache2 = (GLdouble *) calloc(sizeof(GLdouble), (size_t) slices + 1);
    sinCache3 = (GLdouble *) calloc(sizeof(GLdouble), (size_t) slices + 1);
    cosCache3 = (GLdouble *) calloc(sizeof(GLdouble), (size_t) slices + 1);

    GLdouble angle;
    GLdouble length;

    GLdouble xyNormalRatio;

    if (slices < 2 || stacks < 1 || baseRadius < 0.0 || topRadius < 0.0 || height < 0.0) {
        throw geException("Invalid values fed to geCylinder.", true);
    }

    /* Compute length (needed for normal calculations) */
    deltaRadius = baseRadius - topRadius;
    length = sqrt(deltaRadius * deltaRadius + height * height);

    if (length == 0.0) {
        throw geException("Invalid values fed to geCylinder", true);
    }

    zNormal = deltaRadius / length;
    xyNormalRatio = height / length;

    for (int i = 0; i < slices; i++) {
        angle = 2 * M_PI * i / slices;

        sinCache[i] = sin(angle);
        cosCache[i] = cos(angle);

        sinCache2[i] = xyNormalRatio * sin(angle);
        cosCache2[i] = xyNormalRatio * cos(angle);

        sinCache3[i] = xyNormalRatio * sin(angle);
        cosCache3[i] = xyNormalRatio * cos(angle);
    }

    sinCache[slices] = sinCache[0];
    cosCache[slices] = cosCache[0];
    sinCache2[slices] = sinCache2[0];
    cosCache2[slices] = cosCache2[0];
    sinCache3[slices] = sinCache3[0];
    cosCache3[slices] = cosCache3[0];

    this->deltaAngle = 2.0 * M_PI / (this->slices);
}

void geCylinder::draw(GLdouble s, GLdouble t) {
    /* Prevent warnings */
    (void) s;
    (void) t;

    glPushMatrix();

    GLdouble radiusLow, radiusHigh;
    GLdouble zLow, zHigh;

    /* Cover the base and top */
    if (baseRadius > 0.0) {
        drawCircle(this->baseRadius);
    }

    /* Top needs a translation */
    if (topRadius > 0.0) {
        glPushMatrix();
        glTranslated(0, 0, this->height);
        drawCircle(this->topRadius);
        glPopMatrix();
    }

    for (int j = 0; j < stacks; j++) {
        zLow = j * height / stacks;
        zHigh = (j + 1) * height / stacks;
        radiusLow = baseRadius - deltaRadius * ((float) j / stacks);
        radiusHigh = baseRadius - deltaRadius * ((float) (j + 1) / stacks);

        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= slices; i++) {
            glNormal3d(sinCache2[i], cosCache2[i], zNormal);

            glTexCoord2d(1 - i / slices, j / stacks);
            glVertex3d(radiusLow * sinCache[i], radiusLow * cosCache[i], zLow);
            glTexCoord2d(1 - i / slices, (j + 1) / stacks);
            glVertex3d(radiusHigh * sinCache[i], radiusHigh * cosCache[i], zHigh);
        }
    }
    glEnd();

    glPopMatrix();
}

/* Needs optimizations */
void geCylinder::drawCircle(GLdouble radius) {
    GLdouble vertex[4];
    GLdouble texcoord[2];

    glBegin(GL_TRIANGLE_FAN);

    /* draw the vertex at the center of the circle */
    texcoord[0] = 0.5;
    texcoord[1] = 0.5;
    glTexCoord2dv(texcoord);

    vertex[0] = vertex[1] = vertex[2] = 0.0;
    vertex[3] = 1.0;
    glVertex4dv(vertex);

    for (int i = this->slices; i > 0; i--) {
        texcoord[0] = (cosCache[i] + 1.0) * 0.5;
        texcoord[1] = (sinCache[i] + 1.0) * 0.5;
        glTexCoord2dv(texcoord);

        vertex[0] = cosCache[i] * radius;
        vertex[1] = sinCache[i] * radius;
        vertex[2] = 0.0;
        vertex[3] = 1.0;
        glVertex4dv(vertex);
    }

    texcoord[0] = (1.0 + 1.0) * 0.5;
    texcoord[1] = (0.0 + 1.0) * 0.5;
    glTexCoord2dv(texcoord);

    vertex[0] = 1.0 * radius;
    vertex[1] = 0.0 * radius;
    vertex[2] = 0.0;
    vertex[3] = 1.0;
    glVertex4dv(vertex);
    glEnd();
}

geCylinder::~geCylinder() {
    free(sinCache);
    free(cosCache);
    free(sinCache2);
    free(cosCache2);
    free(sinCache3);
    free(cosCache3);
}

/* Sphere primitive */
geSphere::geSphere(GLdouble iRadius, int iSlices, int iStacks) {
    this->radius = iRadius;
    this->slices = iSlices;
    this->stacks = iStacks;

    fghCircleTable(&sint1, &cost1, -this->slices);
    fghCircleTable(&sint2, &cost2, this->stacks * 2);
}

void geSphere::draw(GLdouble s, GLdouble t) {
    /* Prevent warnings */
    (void) s;
    (void) t;

    glPushMatrix();
    //glFrontFace(GL_CW);

    int i, j;

    /* Adjust z and radius as stacks are drawn. */
    double z0, z1;
    double r0, r1;

    z0 = 1.0;
    z1 = cost2[(stacks > 0) ? 1 : 0];
    r0 = 0.0;
    r1 = sint2[(stacks > 0) ? 1 : 0];

    glBegin(GL_TRIANGLE_FAN);

    glNormal3d(0, 0, 1);
    glVertex3d(0, 0, radius);

    for (j = slices; j >= 0; j--) {
        glNormal3d(cost1[j] * r1, sint1[j] * r1, z1);
        glTexCoord3d(cost1[j] * r1 * radius, sint1[j] * r1 * radius, z1 * radius);
        glVertex3d(cost1[j] * r1 * radius, sint1[j] * r1 * radius, z1 * radius);
    }

    glEnd();

    /* Cover each stack with a quad strip, except the top and bottom stacks */

    for (i = 1; i < stacks - 1; i++) {
        z0 = z1;
        z1 = cost2[i + 1];
        r0 = r1;
        r1 = sint2[i + 1];

        glBegin(GL_QUAD_STRIP);

        for (j = 0; j <= slices; j++) {

            glNormal3d(cost1[j] * r1, sint1[j] * r1, z1);
            glTexCoord3d(cost1[j] * r1 * radius, sint1[j] * r1 * radius, z1 * radius);

            glVertex3d(cost1[j] * r1 * radius, sint1[j] * r1 * radius, z1 * radius);
            glNormal3d(cost1[j] * r0, sint1[j] * r0, z0);

            glTexCoord3d(cost1[j] * r0 * radius, sint1[j] * r0 * radius, z0 * radius);
            glVertex3d(cost1[j] * r0 * radius, sint1[j] * r0 * radius, z0 * radius);
        }

        glEnd();
    }

    /* The bottom stack is covered with a triangle fan */

    z0 = z1;
    r0 = r1;

    glBegin(GL_TRIANGLE_FAN);

    glNormal3d(0, 0, -1);
    glVertex3d(0, 0, -radius);

    for (j = 0; j <= slices; j++) {
        glNormal3d(cost1[j] * r0, sint1[j] * r0, z0);
        glTexCoord3d(cost1[j] * r0 * radius, sint1[j] * r0 * radius, z0 * radius);
        glVertex3d(cost1[j] * r0 * radius, sint1[j] * r0 * radius, z0 * radius);
    }

    glEnd();

    glPopMatrix();
    //glFrontFace(GL_CCW);
}

geSphere::~geSphere() {
    /* Release sin and cos tables */
    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);
}

