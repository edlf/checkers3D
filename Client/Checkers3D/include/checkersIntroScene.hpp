/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#ifndef CHECKERSINTROSCENE_HPP_
#define CHECKERSINTROSCENE_HPP_

#include "checkersScene.hpp"

class checkersIntroScene: public checkersScene{
private:
    double timeSinceLastDelta, deltaTime;
    unsigned short int stage, ct;
    GLdouble fadeIn[60];
    unsigned short int currentPos;
    void createFade();

    geSphere* ball;
    geColor emissive;
    geAppearance* appearance;
    checkersSettings* settingsObj;

public:
    checkersIntroScene(checkersSettings* settingsObjI);

    void init();
    void reInit();
    void draw();
	void drawPicking(GLfloat* pickMatrix);
    void pickByID(GLuint ID);

    void update(double dt);

    ~checkersIntroScene();
};

#endif
