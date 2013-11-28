/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#ifndef CHECKERSSCENE_HPP_
#define CHECKERSSCENE_HPP_

#include "hoIncludes.hpp"
#include "geCamera.hpp"
#include "geLight.hpp"
#include "geAppearance.hpp"
#include "gePrimitive.hpp"
#include "geAnimation.hpp"

#include "checkersBoard.hpp"
#include "checkersBackground.hpp"

class checkersScene {

protected:
    unsigned short int sceneID;
    unsigned short int nextSceneID;
    bool sceneHasEnded;

    /* Aspect */
    GLdouble aspectRatio;

    /* Globals */
    GLfloat backgroundColor[4];
    unsigned int drawModeInt;

    void setBackgroundColor(geColor in);
    void applyGlobals();

    /* Cameras */
    geCamera* currentCameraPointer;
    std::vector<geCamera*> cameraVector;

    unsigned int numberOfCameras;

    void setInitialCamera();
    // void setViewRotate(GLdouble* input);
    // GLdouble* getViewProjection();

    void applyCameraView();

    /* Lights */
    GLfloat ambientLightColor[4];
    std::vector<geLight*> lightVector;

    void setAmbientLightColor(geColor in);
    void initLights();

    /* Shaders */
    //vector<geWaterLine*> waterLineVector;

    /* Internal display functions */
    void displayLights();

    /* Current render mode */
    GLint mode;

    /* Update stuff */
    virtual void checkUpdate();
    unsigned long updatePeriod;
    unsigned long lastUpdate;

public:
    geCameraPerspective* externalGuiCamera;

    checkersScene();

    /* Init / Draw related stuff */
    virtual void init();
    virtual void reInit();
    virtual void display();
    virtual void draw();
	virtual void drawPicking(GLfloat* pickMatrix);
    virtual void update(double dt);
    virtual void processKey(int key);
	virtual void processEndScene();

    unsigned short int getSceneID();
    unsigned short int getNextSceneID();

    bool isOver();

    void changeCameraToExernal();

    void reSetPolygonMode(int in);

	void getCurrentCameraInfo();

    /* For reshape */
	void setAspectRatio(double in);
    double getAspectRatio();

	virtual void pickByID(GLuint id);
	virtual void hooverByID(GLuint id);

    virtual ~checkersScene();
};

#endif /* CHECKERSSCENE_HPP_ */
