
#include "core.h"


// global variables

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;
double red = 1;
double green = 1;
double blue = 1;

float vertical = 0;
float horizontal = 0;


// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();


int main() {

	//
	// 1. Initialisation
	//
	

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Real-Time Computer Graphics", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback


	// Initialise glew
	glewInit();

	
	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black

	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);

	//
	// 2. Main loop
	// 
	

	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		//ensure rgb is between 0 and 255
		//red
		if (red > 1)
		{
			red = 0;
		}
		else if (red < 0)
		{
			red = 1;
		}
		//green
		if (green > 1)
		{
			green = 0;
		}
		else if (green < 0)
		{
			green = 1;
		}
		//blue
		if (blue > 1)
		{
			blue = 0;
		}
		else if (blue < 0)
		{
			blue = 1;
		}

		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
		// glfwWaitEvents();				// Use this if no animation.
		// glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();					// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}



// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 1, 0);
	// Render objects here...
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();

	glBegin(GL_TRIANGLES); 
	glVertex2f(-0.5f, 0.2f);
	glVertex2f(0.0f, -0.8f);
	glVertex2f(0.5f, 0.2f);
	glEnd(); 

	glColor3d(red, green, blue);        
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.9f, -0.1f);
	glVertex2f(-0.8f, 0.1f);
	glVertex2f(-0.7f, -0.1f);
	glEnd();

	
	glColor3d(1, 0, 0);
	glBegin(GL_POLYGON); 
	glVertex2f(1.0f +horizontal, 0.0f +vertical);
	glVertex2f(1.5f + horizontal, 0.0f + vertical);
	glVertex2f(1.5f + horizontal, -0.5f + vertical);
	glVertex2f(1.0f + horizontal, -0.5f + vertical);
	glEnd();


	//glPushMatrix();
	//glTranslatef(0.1f, 0.1f, 0.0f);
	//glPopMatrix();
	

}


// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}


// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;
			case GLFW_KEY_1:  
				red += 0.01;
				printf("red =  %f\n", red);
				break;
			case GLFW_KEY_2:
				red -= 0.01;
				printf("red =  %f\n", red);
				break;
			case GLFW_KEY_3:
				green += 0.01;
				printf("green =  %f\n", green);
				break;
			case GLFW_KEY_4:
				green -= 0.01;
				printf("green =  %f\n", green);
				break;
			case GLFW_KEY_5:
				blue += 0.01;
				printf("blue =  %f\n", blue);
				break;
			case GLFW_KEY_6:
				blue -= 0.01;
				printf("blue =  %f\n", blue);
				break;
			case GLFW_KEY_W:
				vertical += 0.01f;
				break;
			case GLFW_KEY_S:
				vertical -= 0.01f;
				break;
			case GLFW_KEY_A:
				horizontal -= 0.01;
				break;
			case GLFW_KEY_D:
				horizontal += 0.01;
				break;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
	}
}


// Function called to animate elements in the scene
void updateScene() 
{
	//glTranslated(0.1f,0.1f,0);
	//glPopMatrix();
}

