#include "core.h"
#include "MyShapes.h"


/*
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
	if (vertices2[0][1] + vertFloat > vertices[0][1] + vertical)
	{
		vertBool = false;
	}
	if (vertices2[2][1] + vertFloat < vertices[2][1] + vertical)
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

*/


void drawStar(float atX, float atY, float innerRadius, float outerRadius)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(atX, atY + (outerRadius / 2));
	glVertex2f(atX + (innerRadius / 2), atY + (innerRadius / 2));
	glVertex2f(atX + (outerRadius / 2), atY + ((innerRadius / 2) - innerRadius / 10));
	glVertex2f(atX + ((outerRadius / 2) - (innerRadius / 2)), atY - (innerRadius / 4));
	glVertex2f(atX + (outerRadius / 2), atY - (outerRadius / 2));

	glVertex2f(atX, atY - (outerRadius / 4));

	glVertex2f(atX - (outerRadius / 2), atY - (outerRadius / 2));
	glVertex2f(atX + (-(outerRadius / 2) + (innerRadius / 2)), atY - (innerRadius / 4));
	glVertex2f(atX - (outerRadius / 2), atY + ((innerRadius / 2) - innerRadius / 10));
	glVertex2f(atX - (innerRadius / 2), atY + (innerRadius / 2));
	glEnd();
}

void drawTank(float atX, float atY, int direction, float colour[3])
{

	//set colour
	glColor3f(colour[0], colour[1], colour[2]);

	//pointing left or right
	if (direction < 2)
	{
		//render body
		glBegin(GL_LINE_LOOP);
		glVertex2f(atX - 0.75, atY + 0.4);
		glVertex2f(atX + 0.75, atY + 0.4);
		glVertex2f(atX + 0.75, atY - 0.4);
		glVertex2f(atX - 0.75, atY - 0.4);
		glEnd();

		//render gun
		if (direction == 0)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(atX - 0.5, atY + 0.3);
			glVertex2f(atX - 0.5, atY - 0.3);
			glVertex2f(atX + 0.5, atY);
			glEnd();
		}
		else
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(atX + 0.5, atY + 0.3);
			glVertex2f(atX + 0.5, atY - 0.3);
			glVertex2f(atX - 0.5, atY);
			glEnd();
		}
	}


	//pointing up or down
	else
	{
		//render body
		glBegin(GL_LINE_LOOP);
		glVertex2f(atX - 0.4, atY - 0.75);
		glVertex2f(atX - 0.4, atY + 0.75);
		glVertex2f(atX + 0.4, atY + 0.75);
		glVertex2f(atX + 0.4, atY - 0.75);
		glEnd();

		//render gun
		if (direction == 2)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(atX - 0.3, atY - 0.5);
			glVertex2f(atX + 0.3, atY - 0.5);
			glVertex2f(atX, atY + 0.5);
			glEnd();
		}
		else
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(atX - 0.3, atY + 0.5);
			glVertex2f(atX + 0.3, atY + 0.5);
			glVertex2f(atX, atY - 0.5);
			glEnd();
		}
	}
}

void blendSquares()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	//red square
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-2.5, 1.5);
	glVertex2f(-2.0, 1.5);
	glVertex2f(-2.0, 1.0);
	glVertex2f(-2.5, 1.0);
	glEnd();

	//green square
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-2.75, 1.25);
	glVertex2f(-2.25, 1.25);
	glVertex2f(-2.25, 0.75);
	glVertex2f(-2.75, 0.75);
	glEnd();

	//blue square
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-2.35, 1.25);
	glVertex2f(-1.85, 1.25);
	glVertex2f(-1.85, 0.75);
	glVertex2f(-2.35, 0.75);
	glEnd();

	//end blend
	glDisable(GL_BLEND);

}

// Draw a semi-circle with smooth shading, with red vertices on the inner edge and yellow vertices on the outer edge.
void drawSemiCircleStudio() {

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	//change shade model so Semi circle is flat and not blended colours
	glShadeModel(GL_FLAT);

	glBegin(GL_TRIANGLE_STRIP);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.25f, 1.0f);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.75f, 1.0f);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.216506351f, 1.125f);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.649519053f, 1.375f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.125, 1.216506351f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.375f, 1.649519053f);

	glColor3ub(0, 255, 0);
	glVertex2f(0.0f, 1.25f);

	glColor3ub(0, 255, 0);
	glVertex2f(0.0f, 1.75f);

	glColor3ub(0, 255, 255);
	glVertex2f(0.125f, 1.216506351f);

	glColor3ub(0, 255, 255);
	glVertex2f(0.375f, 1.649519053f);

	glColor3ub(0, 0, 255);
	glVertex2f(0.216506351f, 1.125f);

	glColor3ub(0, 0, 255);
	glVertex2f(0.649519053f, 1.375f);

	glColor3ub(255, 0, 255);
	glVertex2f(0.25f, 1.0f);

	glColor3ub(255, 0, 255);
	glVertex2f(0.75f, 1.0f);

	glEnd();

	//change shade model so other renders are smooth
	glShadeModel(GL_SMOOTH);
}