/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#include "include/checkersBoardOverlay.hpp"

bool checkersBoardOverlay::initialConfigDone = false;
checkersPlane* checkersBoardOverlay::highlightPlane = NULL;
geAppearance* checkersBoardOverlay::highlightAppearance = NULL;
geAppearance* checkersBoardOverlay::highlightedAppearance = NULL;
geAppearance* checkersBoardOverlay::highlightedDestinationAppearance = NULL;

void checkersBoardOverlay::updatePosition() {
    this->zPos = - (GLfloat) BOARD_LAYOUT_CENTER + (GLfloat) BOARD_LAYOUT_SQUARE_CENTER + (GLfloat) BOARD_LAYOUT_SQUARE_SIDE * (x - 1);
    this->xPos = - (GLfloat) BOARD_LAYOUT_CENTER + (GLfloat) BOARD_LAYOUT_SQUARE_CENTER + (GLfloat) BOARD_LAYOUT_SQUARE_SIDE * (y - 1);
}

void checkersBoardOverlay::updateHighlightColor() {
    switch (this->kind) {
    case 1:
        currentAppearance = highlightAppearance;
        break;

    case 2:
        currentAppearance = highlightedDestinationAppearance;
        break;

    case 3:
        currentAppearance = highlightedAppearance;
        break;

    default:
        break;
    }
}

checkersBoardOverlay::checkersBoardOverlay(unsigned short int xi, unsigned short int yi) {
    this->x = xi;
    this->y = yi;
    this->kind = 0;

    updatePosition();

    /* If this is the first overlay created initialize the objects */
    if (!initialConfigDone) {
        highlightPlane = new checkersPlane(2);

        highlightAppearance = new geAppearance();
        highlightedAppearance = new geAppearance();
        highlightedDestinationAppearance = new geAppearance();

        highlightAppearance->setShininess(16);
        highlightedAppearance->setShininess(16);
        highlightedDestinationAppearance->setShininess(16);

        highlightAppearance->setAmbient(0, 0.7, 1, 1);
        highlightAppearance->setEmissive(0, 0.7, 1, 1);
        highlightAppearance->setSpecular(0, 0.7, 1, 1);

        highlightedAppearance->setAmbient(1, 0.6, 0.25, 1);
        highlightedAppearance->setEmissive(1, 0.6, 0.25, 1);
        highlightedAppearance->setSpecular(1, 0.6, 0.25, 1);

        highlightedDestinationAppearance->setAmbient(0, 1, 0.25, 1);
        highlightedDestinationAppearance->setEmissive(0, 1, 0.25, 1);
        highlightedDestinationAppearance->setSpecular(0, 1, 0.25, 1);

        updateHighlightColor();

        initialConfigDone = true;
    }

    this->currentAppearance = highlightAppearance;
}

void checkersBoardOverlay::disable() {
    this->kind = 0;
}

void checkersBoardOverlay::setNormal() {
    this->kind = 1;
    updateHighlightColor();
}

void checkersBoardOverlay::setDestination() {
    this->kind = 2;
    updateHighlightColor();
}

void checkersBoardOverlay::setSelected() {
    this->kind = 3;
    updateHighlightColor();
}

unsigned short int checkersBoardOverlay::getPositionX() {
    return (this->x);
}

unsigned short int checkersBoardOverlay::getPositionY() {
    return (this->y);
}

void checkersBoardOverlay::draw() {
    if (this->kind > 0) {
		glDisable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslated(xPos, 0.002, zPos);
        glScalef(BOARD_LAYOUT_SQUARE_SIDE, 0, BOARD_LAYOUT_SQUARE_SIDE);
        currentAppearance->apply();
        highlightPlane->draw();
        glPopMatrix();
    }
}

void checkersBoardOverlay::drawPicking() {
    GLuint temp = 300 + (x * 10) + y;

    if (this->kind > 0) {
        glPushMatrix();
        glLoadName(temp);
        glTranslated(xPos, 0.002, zPos);
        glScalef(BOARD_LAYOUT_SQUARE_SIDE, 0, BOARD_LAYOUT_SQUARE_SIDE);
        highlightPlane->draw();
        glPopMatrix();
    }
}

void checkersBoardOverlay::update() {
    /* TODO: Create animated pulsating color */

}

/* Don't delete anything since the only objects here are shared */
checkersBoardOverlay::~checkersBoardOverlay() {
}

/* This should be called when the overlays are no longer needed */
void checkersBoardOverlay::deleteSharedData() {
    /* Reset the config flag */
    initialConfigDone = false;

    if (highlightPlane != NULL) {
        delete (highlightPlane);
        highlightPlane = NULL;
    }

    if (highlightAppearance != NULL) {
        delete (highlightAppearance);
        highlightAppearance = NULL;
    }

    if (highlightedAppearance != NULL) {
        delete (highlightedAppearance);
        highlightedAppearance = NULL;
    }

    if (highlightedDestinationAppearance != NULL) {
        delete (highlightedDestinationAppearance);
        highlightedDestinationAppearance = NULL;
    }
}
