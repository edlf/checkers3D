/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Entry point and user interface methods.
 */

#include "include/Checkers3D.hpp"

void initializeWindow();

/* Delete current scene (BIG FAT WARNING) */
void deleteCurrentScene(){
    if (currentScene != NULL){
        delete (currentScene);
        currentScene = NULL;
    }
}

/* Save a snapshot function and tell user about it */
static void snapshot() {
    unsigned int numberOfChannels = 3;
    unsigned int rowWidth = (unsigned int) width * numberOfChannels;
    unsigned int numberOfSubpixels = rowWidth * (unsigned int) height;

    time_t ltime;
    struct tm *Tm;

    ltime = time(NULL);
    Tm = localtime(&ltime);

    char fileName[120];

    sprintf(fileName, "Snapshot_%04d-%02d-%02d_%02d-%02d-%02d.png", Tm->tm_year + 1900, Tm->tm_mon + 1, Tm->tm_mday, Tm->tm_hour, Tm->tm_min, Tm->tm_sec);

    /* define where to extract the snapshot from (GL_BACK or GLFRONT) */
    glReadBuffer(GL_FRONT);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    /* Allocate memory for storing the image */
    GLubyte* imageData = new GLubyte[numberOfSubpixels];
    GLubyte* imageDataRotated = new GLubyte[numberOfSubpixels];

    /* Read the image to the buffer (It's rotated 90º) */
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    /* Rotate image */
    for (int i = 0; i < height; i++) {
        memcpy(imageDataRotated + ((unsigned int) height - i - 1) * rowWidth, imageData + i * rowWidth, rowWidth);
    }

    /* Original image data no longer needed */
    delete[] imageData;

    png::image<png::rgb_pixel> img((size_t) width, (size_t) height);
    png::rgb_pixel pixel;

    unsigned int tempCurrentPositionR = 0;
    unsigned int tempCurrentPositionG = 1;
    unsigned int tempCurrentPositionB = 2;

    for (size_t i = 0; i < (size_t) height; i++) {
        for (size_t j = 0; j < (size_t) width; j++) {

            pixel.red = imageDataRotated[tempCurrentPositionR];
            pixel.green = imageDataRotated[tempCurrentPositionG];
            pixel.blue = imageDataRotated[tempCurrentPositionB];

            /* Jump the number of channels to get the next pixel */
            tempCurrentPositionR += numberOfChannels;
            tempCurrentPositionG += numberOfChannels;
            tempCurrentPositionB += numberOfChannels;

            /* Store the pixel */
            img.set_pixel(j, i, pixel);
        }
    }

    /* imageDataRotated no longer needed */
    delete[] imageDataRotated;

    /* Write the PNG snapshot */
    img.write(fileName);

    cout << "Snapshot taken: " << fileName << endl;
}

/* Inline it, since it's only called by performPicking */
static inline void processHits(GLint hits, GLuint buffer[], int action) {
    GLuint *ptr = buffer;
    GLuint mindepth = GLuintMaxValue;
    GLuint *selected = NULL;
    GLuint nselected;

    /* iterate over the list of hits, and choosing the one closer to the viewer (lower depth) */
    for (int i = 0; i < hits; i++) {
        GLuint num = *ptr;
        ptr++;
        GLuint z1 = *ptr;
        ptr++;
        ptr++;

        if (z1 < mindepth && num > 0) {
            mindepth = z1;
            selected = ptr;
            nselected = num;
        }

        for (unsigned int j = 0; j < num; j++) {
            ptr++;
        }
    }

    /* TODO: Have this only select the closest to the viewer object */

    // if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
    if (selected != NULL) {

		if (action == GLFW_PRESS) {
			for (unsigned int i = 0; i < nselected; i++) {
				currentScene->pickByID(selected[i]);
			}
		} else {
			for (unsigned int i = 0; i < nselected; i++) {
				currentScene->hooverByID(selected[i]);
			}
		}

        
    }
}

/* Picking */
static void performPicking(int action) {
    GLuint selectBuf[PICKING_BUFFER_SIZE];

    /* Matrix storage */
    GLint viewPort[4];
    GLfloat projectionMatrix[16], pickMatrix[16];

    /* Save current matrixes */
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
    glGetIntegerv(GL_VIEWPORT, viewPort);

    // Sets the buffer to be used for selection and activate selection mode
    glSelectBuffer(PICKING_BUFFER_SIZE, selectBuf);
    glRenderMode(GL_SELECT);

    /* Initialize the picking name stack */
    glInitNames();
    glPushName(GLuintMaxValue);

    // The process of picking manipulates the projection matrix
    // so we will be activating, saving and manipulating it
    glMatrixMode(GL_PROJECTION);

    //store current projection matrix to restore easily in the end with a pop
    glPushMatrix();

    // reset projection matrix
    glLoadIdentity();

    // get current viewport and use it as reference for
    // setting a small picking window of 5x5 pixels around mouse coordinates for picking

    // this is multiplied in the projection matrix

    gluPickMatrix(xpos, (height - ypos), 5.0, 5.0, viewPort);
	glGetFloatv(GL_PROJECTION_MATRIX, pickMatrix);

    // multiply the projection matrix stored in our array to ensure same conditions as in normal render
    glMultMatrixf(projectionMatrix);

    // only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	currentScene->drawPicking(pickMatrix);

    // restore original projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glFlush();

    // revert to render mode, get the picking results and process them
    GLint hits = glRenderMode(GL_RENDER);

    /* Only process hits if there were any */
    if (hits == 0) {
        return;
    }
    processHits(hits, selectBuf, action);
}

/* Toggle Full Screen Mode */
void toggleFullScreen() {
    if (!fullScreen) {
        /* Get current window size, if the user decides to go back to window mode */
        glfwGetFramebufferSize(currentWindowPointer, &windowWidth, &windowHeight);

        /* Backup current time */
        timeBackup = glfwGetTime();
        fullScreen = true;

        initializeWindow();
        currentWindowPointer = glfwFullScreen;
        glfwDestroyWindow(glfwWindow);
        glfwWindow = NULL;

    } else {
        /* Backup current time */
        timeBackup = glfwGetTime();
        fullScreen = false;

        initializeWindow();
        currentWindowPointer = glfwWindow;
        glfwDestroyWindow(glfwFullScreen);
        glfwFullScreen = NULL;
    }

    if (currentScene != NULL){
		currentScene->setAspectRatio(aspectRatio);
        currentScene->reInit();
    }
}

/* Calls the current scene display function. */
static void display(void) {
    /* Display current scene */
    if (currentScene != NULL){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);

        currentScene->display();
    }
}

static void mouseButtonFun(GLFWwindow* window, int button, int action, int mods) {
    (void) window;

    keyModifiers = mods;

    /* Remove zoom functions later */
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        pressingMouseLeft = true;
    } else {
        pressingMouseLeft = false;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        pressingMouseRight = true;
    } else {
        pressingMouseRight = false;
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        pressingMouseMiddle = true;
    } else {
        pressingMouseMiddle = false;
    }

    /* Don't perform picking when using modifier keys */
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == 0) {
        performPicking(action);
    }

}

static void cursorPosFun(GLFWwindow* window, double x, double y) {
	(void)window;

	/* Calculate displacement */
	displacementX = x - xpos;
	displacementY = y - ypos;

	/* Remember cursor position */
	xpos = x;
	ypos = y;

	if (pressingMouseLeft && keyModifiers == GLFW_MOD_CONTROL) {
		currentScene->externalGuiCamera->rotate(0, (GLfloat)displacementY * (GLfloat)MOUSE_ROTATE_FACTOR);
		currentScene->externalGuiCamera->rotate(1, (GLfloat)displacementX * (GLfloat)MOUSE_ROTATE_FACTOR);

	}
	else if (pressingMouseRight && keyModifiers == GLFW_MOD_CONTROL) {
		currentScene->externalGuiCamera->translate(0, (GLfloat)displacementX * (GLfloat)MOUSE_PAN_FACTOR);
		currentScene->externalGuiCamera->translate(1, -(GLfloat)displacementY * (GLfloat)MOUSE_PAN_FACTOR);

	}
	else if (pressingMouseMiddle || (pressingMouseLeft && (keyModifiers == GLFW_MOD_SHIFT))) {
		currentScene->externalGuiCamera->translate(2, (GLfloat)displacementY * (GLfloat)MOUSE_ZOOM_FACTOR);
	}

	/* Ask scene to change camera to the special GUI cam */
	if (currentScene != NULL && keyModifiers == GLFW_MOD_CONTROL) {
		currentScene->changeCameraToExernal();
	}

	performPicking(0);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void) scancode;

    /* Escape closes the app */
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    /* P for snapshot */
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        snapshot();
        return;
    }

    /* Q for point */
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        currentScene->reSetPolygonMode(2);
        return;
    }

    /* W for wireframe */
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        currentScene->reSetPolygonMode(1);
        return;
    }

    /* E for fill */
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        currentScene->reSetPolygonMode(0);
        return;
    }

	/* R for info */
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		currentScene->getCurrentCameraInfo();
		return;
	}

    if (action == GLFW_PRESS && mods == 0) {
        currentScene->processKey(key);
    }

    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS && mods == GLFW_MOD_ALT) {
        toggleFullScreen();
    }
}

static void framebufferSizeFun(GLFWwindow* window, int w, int h) {
    (void) window;

    width = w;
    height = h > 0 ? h : 1;
	aspectRatio = width / height;
	if (currentScene != NULL) {
		currentScene->setAspectRatio(aspectRatio);
	}
}

static void geInitialize() {
    /* Initialize glew */
    glewInit();

    /* Initialize global variables */
    displacementX = 0;
    displacementY = 0;

    pressingMouseLeft = false;
    pressingMouseRight = false;
    pressingMouseMiddle = false;

    prev_X = 0;
    prev_Y = 0;

    /* Check if scene has a valid pointer */
    if (currentScene == NULL) {
        cerr << "Null scene pointer. You got bugs to fix!" << endl;
        exit(-1);
    }

    /* Ask scenes to initialize */
	currentScene->setAspectRatio(aspectRatio);
    currentScene->init();

}

/* Terminate method */
static void geTerminate() {
    cout << "Exiting.." << endl;
    /* Save settings to file */
    settingsObj->saveSettings();

    glfwTerminate();

    if (currentScene != NULL) {
        delete (currentScene);
    }

}

static void geLoop() {
    /* Main loop */
    while (1) {
        if (currentScene->isOver()) {
			/* Call scene close function */
			currentScene->processEndScene();

            switch (currentScene->getNextSceneID()) {
            case 1:
                deleteCurrentScene();
                introScene = new checkersIntroScene(settingsObj);
                currentScene = introScene;
                break;

            case 2:
                deleteCurrentScene();
                menuScene = new checkersMenuScene(settingsObj);
                currentScene = menuScene;
                break;

            case 3:
                deleteCurrentScene();
                mainGameScene = new checkersGameScene(settingsObj);
                currentScene = mainGameScene;
                break;

            default:
                break;
            }

			currentScene->setAspectRatio(aspectRatio);
            currentScene->init();
        }

        /* Timing */
        t = glfwGetTime();
        dt = t - t_old;
        t_old = t;

        currentScene->update(dt);

        /* Draw one frame */
        display();

        /* Swap buffers */
        glfwSwapBuffers(currentWindowPointer);
        glfwPollEvents();

        /* Check if we are still running (aka the window has not been closed) */
        if (glfwWindowShouldClose(currentWindowPointer)) {
            break;
        }
    }
}

void initializeWindow() {
    GLFWmonitor* currentMonitor = NULL;

    /* Get primary monitor video mode */
    currentMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* currentVideoMode = glfwGetVideoMode(currentMonitor);

    if (fullScreen) {
        glfwFullScreen = glfwCreateWindow(currentVideoMode->width, currentVideoMode->height, APP_NAME, currentMonitor, NULL);
        if (!glfwFullScreen) {
            glfwTerminate();
            cerr << "Error while opening in full screen mode!" << endl;
            pressEnterToExit();
        }
        currentWindowPointer = glfwFullScreen;

    } else {
        glfwWindow = glfwCreateWindow(windowWidth, windowHeight, APP_NAME, NULL, NULL);
        if (!glfwWindow) {
            glfwTerminate();
            cerr << "Error while creating window!" << endl;
            pressEnterToExit();
        }
        currentWindowPointer = glfwWindow;
    }

    /* Callbacks */
    glfwSetFramebufferSizeCallback(currentWindowPointer, framebufferSizeFun);

    /* Mouse */
    glfwSetCursorPosCallback(currentWindowPointer, cursorPosFun);
    glfwSetMouseButtonCallback(currentWindowPointer, mouseButtonFun);

    /* Keyboard */
    glfwSetKeyCallback(currentWindowPointer, key_callback);

    /* Enable vsync */
    glfwMakeContextCurrent(currentWindowPointer);
    glfwSwapInterval(1);

    glfwGetFramebufferSize(currentWindowPointer, &width, &height);
    framebufferSizeFun(currentWindowPointer, width, height);

    /* Only initialize time once */
    if (timeFirstInit) {
        glfwSetTime(0.0);
        timeFirstInit = false;
    } else {
        glfwSetTime(timeBackup);
    }
}

void createIntroScene(){
    /* Create intro scene */
    try {
        introScene = new checkersIntroScene(settingsObj);
    } catch (geException& exception) {
        exception.printerErrorMessage();
        pressEnterToExit();
    }
}

void createMenuScene(){
    /* Unlock sockets config before starting the menu scene */
    settingsObj->unlockSocketsConfig();

    /* Create main menu scene */
    try {
        menuScene = new checkersMenuScene(settingsObj);
    } catch (geException& exception) {
        exception.printerErrorMessage();
        pressEnterToExit();
    }
}

void createGameScene(){
    /* Save settings to file */
    settingsObj->saveSettings();

    /* Lock sockets config before starting the game scene */
    settingsObj->lockSocketsConfig();

    /* Create game scene */
    try {
        mainGameScene = new checkersGameScene(settingsObj);
    } catch (geException& exception) {
        exception.printerErrorMessage();
        pressEnterToExit();
    }
}


/* Main */
int main(int argc, char** argv) {
	/* Initialize glut */
	glutInit(&argc, argv);

    /* Avoid warnings */
    //(void) argc;
    //(void) argv;

    /* Obligatory Duke Nukem 3D reference */
    cout << "Duke says: \"What are you waiting for? Christmas?\"" << endl;

    /* Create settings object w/ default settings */
    settingsObj = new checkersSettings();

    /* Load settings from file */
    settingsObj->loadSettings();
    /* We only need the fullscreen flag here */
    fullScreen = settingsObj->getFullScreenBool();

    /* Create main intro scene */
    createIntroScene();
    currentScene = introScene;

    /* Initialize GLFW */
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    /* Set default window size */
    windowWidth = WINDOW_SIZE_X;
    windowHeight = WINDOW_SIZE_Y;
	aspectRatio = windowWidth / windowHeight;

    initializeWindow();

    geInitialize();
    geLoop();
    geTerminate();
    return (0);
}

