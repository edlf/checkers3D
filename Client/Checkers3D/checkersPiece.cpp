/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 */

#include "include/checkersPiece.hpp"

/* Shared stuff */
geCylinder* checkersPiece::cylinder = NULL;
bool checkersPiece::initialConfigDone = false;

/* White */
geColor checkersPiece::pieceAppearanceEmissiveW = { 1, 1, 1, 1 };
geColor checkersPiece::pieceAppearanceAmbientW = { 1, 1, 1, 1 };
geColor checkersPiece::pieceAppearanceDiffuseW = { 1, 1, 1, 1 };
geColor checkersPiece::pieceAppearanceSpecularW = { 1, 1, 1, 1 };

/* Black */
geColor checkersPiece::pieceAppearanceEmissiveB = { 0, 0, 0, 1 };
geColor checkersPiece::pieceAppearanceAmbientB = { 0, 0, 0, 1};
geColor checkersPiece::pieceAppearanceDiffuseB = { 0, 0, 0, 1 };
geColor checkersPiece::pieceAppearanceSpecularB = { 1, 1, 1, 1 };

GLfloat checkersPiece::pieceAppearanceShininess = 1;

geAppearance* checkersPiece::blackPieceAppearance = NULL;
geAppearance* checkersPiece::whitePieceAppearance = NULL;

geTexture* checkersPiece::blackPieceTexture = NULL;
geTexture* checkersPiece::whitePieceTexture = NULL;

/* End shared stuff */

checkersPiece::checkersPiece(unsigned short int in) {
    this->kindOf = in;
    this->isCaptured = true;

    this->x = 1;
    this->y = 1;

    updatePosition();

    if (!initialConfigDone) {
        this->cylinder = new geCylinder((GLfloat) PIECE_RADIUS, (GLfloat) PIECE_RADIUS, (GLfloat) 0.15, 32, 6);

		this->blackPieceAppearance = new geAppearance(pieceAppearanceEmissiveB, pieceAppearanceAmbientB, pieceAppearanceDiffuseB, pieceAppearanceDiffuseB, pieceAppearanceShininess);
		this->whitePieceAppearance = new geAppearance(pieceAppearanceEmissiveW, pieceAppearanceAmbientW, pieceAppearanceDiffuseW, pieceAppearanceDiffuseW, pieceAppearanceShininess);

		this->blackPieceTexture = new geTexture("pieceMarbleBlack.png");
		this->whitePieceTexture = new geTexture("pieceMarbleWhite.png");

        initialConfigDone = true;
    }
}

void checkersPiece::updatePosition() {
    /* Pieces start from 1 to 8, the openGl x 'y' are swapped (not really y, it's z) */
    this->zPos = - (GLfloat) BOARD_LAYOUT_CENTER + (GLfloat) BOARD_LAYOUT_SQUARE_CENTER + (GLfloat) BOARD_LAYOUT_SQUARE_SIDE * (x - 1);
    this->xPos = - (GLfloat) BOARD_LAYOUT_CENTER + (GLfloat) BOARD_LAYOUT_SQUARE_CENTER + (GLfloat) BOARD_LAYOUT_SQUARE_SIDE * (y - 1);
}

bool checkersPiece::isEven(unsigned int i) {
    if (i % 2 == 0) {
        return (true);
    } else {
        return (false);
    }
}

void checkersPiece::setPosition(unsigned short int x, unsigned short int y) {
    if (x > 8 || y > 8) {
        throw geException("checkersPiece: Out of bonds position value.", true);
    }

    /* Check if the value is valid */
    if (isEven(x) && isEven(y)) {
        this->x = x;
        this->y = y;
    } else if (!isEven(x) && !isEven(y)) {
        this->x = x;
        this->y = y;
    } else {
        throw geException("checkersPiece: Invalid place.", true);
    }

    updatePosition();
}

unsigned short int checkersPiece::getPositionX(){
    return (this->x);
}

unsigned short int checkersPiece::getPositionY(){
    return (this->y);
}

void checkersPiece::setCapturedFlag(bool in) {
    this->isCaptured = in;
}

void checkersPiece::draw() {
    glPushMatrix();
    glDisable(GL_TEXTURE_2D);

    if (isCaptured) {
        /* Piece is captured draw outside of the board */
        if (this->kindOf == BOARD_WHITE) {

            whitePieceAppearance->apply();
			whitePieceTexture->apply();
        } else {

            blackPieceAppearance->apply();
			blackPieceTexture->apply();
        }

        /* Draw in piece holder */

    } else {
        /* Piece is in the board, draw it in it's position */
        if (this->kindOf == BOARD_WHITE) {

            whitePieceAppearance->apply();
			whitePieceTexture->apply();
        } else {

            blackPieceAppearance->apply();
			blackPieceTexture->apply();
        }

        /* y = 0.15 + 0.001 in order to avoid artifacts */
        glTranslated(xPos, (GLfloat) 0.151, zPos);
        glRotatef(90, 1, 0, 0);
        cylinder->draw(1, 1);

    }

    glPopMatrix();
}

void checkersPiece::drawPicking(GLuint id){
    /* Only 'draw' it if it is not captured */
    if (!this->isCaptured) {
        glPushMatrix();

        glTranslated(xPos, (GLfloat) 0.151, zPos);
        glRotatef(90, 1, 0, 0);

        glLoadName(id);
        /* Draw a more crappy cylinder here? */
        cylinder->draw(1, 1);

        glPopMatrix();
    }
}

void checkersPiece::loadTextures(){
	blackPieceTexture->loadTexture();
	whitePieceTexture->loadTexture();
}

void checkersPiece::reloadTextures(){
	blackPieceTexture->reloadTexture();
	whitePieceTexture->reloadTexture();
}

checkersPiece::~checkersPiece() {
}

void checkersPiece::deleteSharedData() {
    /* Reset the initial config flag */
    initialConfigDone = false;

    if (cylinder != NULL) {
        delete (cylinder);
        cylinder = NULL;
    }

	if (blackPieceAppearance != NULL) {
		delete (blackPieceAppearance);
		blackPieceAppearance = NULL;
	}

	if (whitePieceAppearance != NULL) {
		delete (whitePieceAppearance);
		whitePieceAppearance = NULL;
	}

	if (blackPieceTexture != NULL) {
		delete (blackPieceTexture);
		blackPieceTexture = NULL;
	}

	if (whitePieceTexture != NULL) {
		delete (whitePieceTexture);
		whitePieceTexture = NULL;
	}
}
