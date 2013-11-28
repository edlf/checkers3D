/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#include "include/checkersBackground.hpp"

checkersBackground::checkersBackground() {
    this->currentBackground = 0;
    this->defaultTexture = new geTexture("defaultBackground.png");
    this->defaultFloor = new geTexture("defaultFloor.png");

    this->backgroundPlane = new checkersPlane(50);
}

void checkersBackground::loadTextures() {
    this->defaultTexture->loadTexture();
    this->defaultFloor->loadTexture();
}

void checkersBackground::reloadTextures() {
    this->defaultTexture->reloadTexture();
    this->defaultFloor->reloadTexture();
}

void checkersBackground::changeBackground(unsigned int i) {
    this->currentBackground = i;
}

void checkersBackground::draw() {
    /* Wall */
    glPushMatrix();
    glTranslatef(0, 8, -30);
    glRotatef(-90, 1, 0, 0);
    glScalef(32, 0, 20);
    this->defaultTexture->apply();
    this->backgroundPlane->draw();
    glPopMatrix();

    /* Floor */
    glPushMatrix();
    glTranslatef(0, -5, -15);
    glRotatef(30, 1, 0, 0);
    glScalef(32, 0, 20);
    this->defaultFloor->apply();
    this->backgroundPlane->draw();
    glPopMatrix();
}
