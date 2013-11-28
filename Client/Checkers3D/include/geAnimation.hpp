/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Animation class.
 */

#ifndef GEANIMATION_HPP_
#define GEANIMATION_HPP_

#include "hoIncludes.hpp"

class geAnimation {
protected:
    double span;
    unsigned int type;

    std::vector<gePoint> controlPoints;
    unsigned int numberOfControlPoints;

    double deltaTimeMillis;
    double updateCounter;

    double deltaTimeSingleMove;

    double spanMilliseconds;
    double totalTimePassed;

    double x, y, z;

    double angleX;
    double angleZ;

    void updateAngles();

    bool hasEnded;

    gePoint currentSourcePoint;
    gePoint currentDestionationPoint;
    unsigned int numberOfProcessedControlPoints;

    double dX, dY, dZ;

    void updateDeltas();

    double deg2rad;

public:
    geAnimation(double iSpan, unsigned int iType);

    void insertPoint(gePoint in);
    void insertPoint(GLdouble ix, GLdouble iy, GLdouble iz);

    double getDeltaTime();

    /* Receives the (approximated) time passed since last update */
    void updateAnimation(double timePassed);
    void applyAnimation();

    ~geAnimation();
};

#endif /* GEANIMATION_HPP_ */
