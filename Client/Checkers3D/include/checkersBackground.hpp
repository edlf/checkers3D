/*
 * checkersBackground.hpp
 *
 *  Self contained background class.
 */

#ifndef CHECKERSBACKGROUND_HPP_
#define CHECKERSBACKGROUND_HPP_

#include "hoIncludes.hpp"
#include "geAppearance.hpp"
#include "geTexture.hpp"
#include "checkersPlane.hpp"

class checkersBackground {
private:
    unsigned int currentBackground;
    checkersPlane* backgroundPlane;
    geTexture* defaultTexture;
    geTexture* defaultFloor;

public:
    checkersBackground();

    void loadTextures();
    void reloadTextures();

    void changeBackground(unsigned int i);

    void draw();
};

#endif /* CHECKERSBACKGROUND_HPP_ */
