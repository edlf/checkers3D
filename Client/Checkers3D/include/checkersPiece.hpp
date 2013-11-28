/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Piece class.
 */

#ifndef PIECE_HPP_
#define PIECE_HPP_

#include "hoIncludes.hpp"
#include "geAppearance.hpp"
#include "gePrimitive.hpp"

class checkersPiece{
private:
	/* Piece data */
	unsigned short int kindOf;
	unsigned short int x, y;
	GLdouble xPos, zPos;
	bool isCaptured;

	void updatePosition();
	bool isEven(unsigned int i);

	/* Appearances (static members, shared between all pieces) */
	static geColor pieceAppearanceEmissiveW;
	static geColor pieceAppearanceAmbientW;
	static geColor pieceAppearanceDiffuseW;
	static geColor pieceAppearanceSpecularW;

	static geColor pieceAppearanceEmissiveB;
	static geColor pieceAppearanceAmbientB;
	static geColor pieceAppearanceDiffuseB;
	static geColor pieceAppearanceSpecularB;

	static GLfloat pieceAppearanceShininess;

	static geAppearance* blackPieceAppearance;
	static geAppearance* whitePieceAppearance;
	
	static geTexture* blackPieceTexture;
	static geTexture* whitePieceTexture;

	/* Draw stuff */
	static geCylinder* cylinder;
	static bool initialConfigDone;

public:
	checkersPiece(unsigned short int in);

	void setPosition(unsigned short int x, unsigned short int y);
	unsigned short int getPositionX();
	unsigned short int getPositionY();

	void setCapturedFlag(bool in);

	void draw();
	void drawPicking(GLuint id);
	void loadTextures();
	void reloadTextures();


	~checkersPiece();
	static void deleteSharedData();
};







#endif /* PIECE_HPP_ */
