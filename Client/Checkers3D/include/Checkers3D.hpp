/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Global UI variables.
 */

#ifndef GEAPP_HPP_
#define GEAPP_HPP_

#include "hoIncludes.hpp"
#include "checkersIntroScene.hpp"
#include "checkersMenuScene.hpp"
#include "checkersGameScene.hpp"

using namespace std;

/* GLuint max */
GLuint GLuintMaxValue = std::numeric_limits<GLuint>::max();

/* Frame buffer size */
static int width, height;
static int windowWidth, windowHeight;
double aspectRatio;

/* Window pointer */
GLFWwindow* glfwWindow = NULL;
GLFWwindow* glfwFullScreen = NULL;
GLFWwindow* currentWindowPointer = NULL;

/* Mouse Position */
static double xpos = 0, ypos = 0;

/* Time control */
bool timeFirstInit = true;
double timeBackup;
double  t = 0.0;
double  t_old = 0.0;
double  dt = 0.0;

/* Settings */
checkersSettings* settingsObj = NULL;

/* Fullscreen control bool */
bool fullScreen = false;

/* Current keyModifiers */
int keyModifiers;

/* Current scene pointer */
checkersScene* currentScene = NULL;

/* Intro scene pointer */
checkersScene* introScene;

/* Menu scene pointer */
checkersScene* menuScene;

/* Main game scene pointer */
checkersScene* mainGameScene;

/* State and control variables to handle mouse interaction */
double displacementX, displacementY;
double prev_X, prev_Y;
bool pressingMouseLeft;
bool pressingMouseMiddle;
bool pressingMouseRight;

/* Sockets */
int socketServerPort = 1200;

#endif /* GEAPP_HPP_ */
