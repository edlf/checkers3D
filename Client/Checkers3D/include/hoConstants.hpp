/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Game board constants, must be equal to the server ones!
 */

#ifndef HOCONSTANTS_HPP_
#define HOCONSTANTS_HPP_

/* OpenGL light max */
#define MAX_LIGHTS                        8

/* buffer size for the picking */
#define PICKING_BUFFER_SIZE             256

#define WINDOW_SIZE_X                   800
#define WINDOW_SIZE_Y                   600
#define WINDOW_INITIALPOS_X              50
#define WINDOW_INITIALPOS_Y              50

/* GUI camera stuff, once again stolen from CGFlib (divided values by 2 for more accuracy) */
#define MOUSE_ROTATE_FACTOR            0.25
#define MOUSE_PAN_FACTOR              0.025
#define MOUSE_ZOOM_FACTOR              0.25

/* Files */
#define SETTINGS_FILE_NAME "Checkers3D.sav"

/* Folders */
#define TEXTURE_FOLDER          "textures/"
#define SHADER_FOLDER            "shaders/"

/* Sockets defaults */
#define SOCKET_PORT                    1200
#define SOCKET_HOST             "localhost"

/* Board */
#define BOARD_EMPTY                       0
#define BOARD_WHITE                       1
#define BOARD_WHITE_KING                  2
#define BOARD_BLACK                       3
#define BOARD_BLACK_KING                  4

#define BOARD_PIECES_BY_PLAYER           12
#define BOARD_START                       1
#define BOARD_END                         8

#define BOARD_LAYOUT_SIZE                12
#define BOARD_LAYOUT_CENTER               6
#define BOARD_LAYOUT_SQUARE_SIDE        1.5
#define BOARD_LAYOUT_SQUARE_CENTER     0.75
#define PIECE_RADIUS                    0.4

#define BOARD_PICKING_ID_BLACK_PIECE    200
#define BOARD_PICKING_ID_WHITE_PIECE    100

#endif
