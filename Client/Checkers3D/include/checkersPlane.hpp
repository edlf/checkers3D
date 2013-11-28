/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#ifndef CHECKERSPLANE_HPP_
#define CHECKERSPLANE_HPP_

#include "hoIncludes.hpp"

class checkersPlane {
private:
	unsigned int numberOfDivisions;

	GLdouble _s;
	GLdouble _t;

public:
	checkersPlane(void);
	checkersPlane(unsigned int);
	checkersPlane(unsigned int, GLdouble, GLdouble);

	void draw();

	~checkersPlane(void);
};

#endif
