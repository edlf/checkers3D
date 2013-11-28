/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Struct definitions.
 */

#ifndef HOSTRUCTS_HPP_
#define HOSTRUCTS_HPP_

struct gePoint {
    GLdouble x, y, z;
};

struct ge2dPoint {
    GLdouble x, y;
};

struct geColor {
    GLdouble r, g, b, a;
};

struct boardStatus {
    /* Current player */
    unsigned short int currentPlayer;

    /* Board for IO */
    unsigned short int boardContentsIO[8][8];
    unsigned short int boardContentsIoHighlights[8][8];
};

#endif
