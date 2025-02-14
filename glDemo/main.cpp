
#include "core.h"
#include "MyShapes.h"

using namespace std;

// global variables

// Window size
const unsigned int initWidth = 1024;
const unsigned int initHeight = 512;
float red = 1;
float green = 1;
float blue = 1;

float vertical = 0;
float horizontal = 0;
bool horz = false; 
bool vert = false;
float vertices[4][2] = { {0.75f, 0.0f},{2.25f,0.0f},{2.25f, -1.0f},{0.75f,-1.0f} };

float vertFloat = 0;
float horzFloat = 0;
bool horzBool = false;
bool vertBool = false;
float vertices2[4][2] = { {1.25f, 0.0f},{1.5f,0.0f},{1.5f, -0.25f},{1.25f,-0.25f} };

GLfloat colours[4][3] = { {1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f},{0.5f,0.5f,0.5f} };

int tankDirection = 0;
float tankX = -2.0f;
float tankY = -1.0f;
bool tankUp = false;
bool tankDown = false;
bool tankLeft = false;
bool tankRight = false;

bool shoot = true; 
float bulletVertices[2] = { 0,0 };
int bulletDirection = -1;


mt19937 engine;
uniform_real_distribution<float> xRange;
uniform_real_distribution<float> yRange;
vector<glm::vec2> vertexCoords;
vector<glm::vec3> colourValues;
uniform_real_distribution<float> colourRange;



// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();
void rRectTransform();
void cyanSquareTransform();
void tankShoot(float atX, float atY, int direction);
void bullet();



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

	gluOrtho2D(-4.0, 4.0, -2.0, 2.0);

	random_device rd;
	engine = mt19937(rd());
	xRange = uniform_real_distribution<float>(-4.0f, 4.0f);
	yRange = uniform_real_distribution<float>(-2.0f, 2.0f);
	colourRange = uniform_real_distribution<float>(0.0f, 1.0f);

	vertexCoords = vector<glm::vec2>(100, glm::vec2(0.0f, 0.0f));
	colourValues = vector<glm::vec3>(100, glm::vec3(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < 100; i++)
	{
		float x = xRange(engine);
		float y = yRange(engine);
		vertexCoords[i] = glm::vec2(x, y);

		float r = colourRange(engine);
		float g = colourRange(engine);
		float b = colourRange(engine);
		colourValues[i] = glm::vec3(r, g, b);
	}



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
	glColor3f(1, 1, 0);
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

	glColor3f(red, green, blue);        
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.9f, -0.1f);
	glVertex2f(-0.8f, 0.1f);
	glVertex2f(-0.7f, -0.1f);
	glEnd();

	//draws star
	drawStar(2.0f, 1.5f,0.2f,0.5f);
	//draw squares and blend colours
	blendSquares();

	//rainbow rectangle
	glPushMatrix();
	glTranslatef(horizontal, vertical, 0);
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON); 
	for (int i = 0; i < 4; i++)
	{
		glColor3f(colours[i][0], colours[i][1], colours[i][2]);
		glVertex2f(vertices[i][0], vertices[i][1]);
	}
	glEnd();
	glPopMatrix();

	//cyan square
	glPushMatrix(); 
	glTranslatef(horzFloat, vertFloat, 0); 
	glColor3f(0, 1, 1); 
	glBegin(GL_POLYGON); 
	for (int i = 0; i < 4; i++)
	{

		glVertex2f(vertices2[i][0], vertices2[i][1]); 
	}
	glEnd(); 
	glPopMatrix(); 
	
	//tank colour
	float tankColour[3] = { 0.1,1.0,0.1 };
	//drawTank
	drawTank(tankX, tankY, tankDirection, tankColour);

	//tank bullet
	glPointSize(15.0f);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(bulletVertices[0], bulletVertices[1]);
	glEnd();

	drawSemiCircleStudio();

	glPointSize(5.0f);
	

	glBegin(GL_POINTS);
	for (int i = 0;i < 100;i++)
	{
		glColor3f(colourValues[i].x, colourValues[i].y, colourValues[i].z); 
		glVertex2f(vertexCoords[i].x, vertexCoords[i].y); 
	}
	glEnd();
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
				red += 0.01f;
				printf("red =  %f\n", red);
				break;
			case GLFW_KEY_2:
				red -= 0.01f;
				printf("red =  %f\n", red);
				break;
			case GLFW_KEY_3:
				green += 0.01f;
				printf("green =  %f\n", green);
				break;
			case GLFW_KEY_4:
				green -= 0.01f;
				printf("green =  %f\n", green);
				break;
			case GLFW_KEY_5:
				blue += 0.01f;
				printf("blue =  %f\n", blue);
				break;
			case GLFW_KEY_6:
				blue -= 0.01f;
				printf("blue =  %f\n", blue);
				break;

			case GLFW_KEY_SPACE:
				if (shoot)
				{
					if (tankDirection == 0)
					{
						bulletVertices[0] = tankX + 0.5;
						bulletVertices[1] = tankY;
					}
					else if (tankDirection == 1)
					{
						bulletVertices[0] = tankX - 0.5;
						bulletVertices[1] = tankY;
					}
					else if (tankDirection == 2)
					{
						bulletVertices[0] = tankX;
						bulletVertices[1] = tankY +0.5;
					}
					else if (tankDirection == 3)
					{
						bulletVertices[0] = tankX;
						bulletVertices[1] = tankY - 0.5;
					}
					bulletDirection = tankDirection;
					shoot = false;
				}
				break;
			case GLFW_KEY_W:
				tankUp = true;
				tankDirection = 2;
				break;
			case GLFW_KEY_S:
				tankDown = true;
				tankDirection = 3;
				break;
			case GLFW_KEY_A:
				tankLeft = true;
				tankDirection = 1;
				break;
			case GLFW_KEY_D:
				tankRight = true;
				tankDirection = 0;
				break;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
		if (action == GLFW_RELEASE) { 

			// check which key was pressed...
			switch (key)
			{

				case GLFW_KEY_W:
					tankUp = false;
					break;
				case GLFW_KEY_S:
					tankDown = false;
					break;
				case GLFW_KEY_A:
					tankLeft = false;
					break;
				case GLFW_KEY_D:
					tankRight = false;
					break;

				default:
				{
				}
			}
		}
	}
}


// Function called to animate elements in the scene
void updateScene() 
{
	//glTranslated(0.1f,0.1f,0);
	//glPopMatrix();

	//tankMove
	if (tankUp)tankY += 0.01f;
	else if (tankDown) tankY -= 0.01f;
	else if (tankLeft) tankX -= 0.01f;
	else if (tankRight) tankX += 0.01f;

	rRectTransform();
	cyanSquareTransform();
	bullet();
}

void rRectTransform()
{
	//horizontal check
	if (vertices[1][0] + horizontal > 4)
	{
		horz = false;
	}
	if (vertices[3][0] + horizontal < -4)
	{
		horz = true;
	}

	//vertical check
	if (vertices[0][1] + vertical > 2)
	{
		vert = false;
	}
	if (vertices[2][1] + vertical < -2)
	{
		vert = true;
	}


	if (horz)
	{
		horizontal += 0.01f;
	}
	else
	{
		horizontal -= 0.01f;
	}

	if (vert)
	{
		vertical += 0.01f;
	}
	else
	{
		vertical -= 0.01f;
	}
}

void cyanSquareTransform()
{
	//horizontal check
	if (vertices2[1][0] + horzFloat > vertices[1][0] + horizontal)
	{
		horzBool = false;
	}
	if (vertices2[3][0] + horzFloat < vertices[3][0] + horizontal)
	{
		horzBool = true;
	}

	//vertical check
	if (vertices2[0][1] + vertFloat > vertices[0][1]+vertical)
	{
		vertBool = false;
	}
	if (vertices2[2][1] + vertFloat < vertices[2][1]+vertical)
	{
		vertBool = true;
	}


	if (horzBool)
	{
		horzFloat += 0.03f;
	}
	else
	{
		horzFloat -= 0.03f;
	}

	if (vertBool)
	{
		vertFloat += 0.03f;
	}
	else
	{
		vertFloat -= 0.03f;
	}
}


void tankShoot(float atX, float atY, int direction)
{

}

void bullet()
{
	if (!shoot)
	{
		if (bulletDirection == 0)
		{
			bulletVertices[0] += 0.01;
			
		}
		else if (bulletDirection == 1)
		{
			bulletVertices[0] -= 0.01;;
			
		}
		else if (bulletDirection == 2)
		{
			
			bulletVertices[1] += 0.01;
		}
		else if (bulletDirection == 3)
		{
			
			bulletVertices[1] -= 0.01;
		}
		
	}
	
	if (bulletVertices[0] > 4 || bulletVertices[0] < -4 || bulletVertices[1] > 2 || bulletVertices[1] < -2)
	{
		shoot = true;
	}
	
}


