/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#ifndef CHECKERSBOARDOVERLAY_HPP_
#define CHECKERSBOARDOVERLAY_HPP_

#include "hoIncludes.hpp"
#include "geAppearance.hpp"
#include "checkersPlane.hpp"

class checkersBoardOverlay{
private:
	unsigned short int x, y;
	GLdouble xPos, zPos;
	
	unsigned short int kind;

	geAppearance* currentAppearance;

	/* Shared stuff */
	static bool initialConfigDone;
	static checkersPlane* highlightPlane;
	static geAppearance* highlightAppearance;
	static geAppearance* highlightedAppearance;
	static geAppearance* highlightedDestinationAppearance;

	/* Methods */
    void updatePosition();
    void updateHighlightColor();

public:
	checkersBoardOverlay(unsigned short int xi, unsigned short int yi);

	void disable();
	void setNormal();
	void setDestination();
	void setSelected();


	unsigned short int getPositionX();
	unsigned short int getPositionY();

	void draw();
	void drawPicking();
	void update();

	~checkersBoardOverlay();
	static void deleteSharedData();
};

#endif /* CHECKERSBOARDOVERLAY_HPP_ */
