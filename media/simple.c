// simple.c
// 
// Demonstrates simple object drawing with perspective
// Program by Bryson R. Payne, M.Ed.
// Georgia State University
// Submitted in Partial Fulfillment of 
// CSc 6820 - Computer Graphics Algorithms 
// Under the Instruction of Dr. G. Scott Owen

// Header files to include
#include <stdio.h>
#include <gl/glut.h>	// GLUT toolkit

// Define initial camera position and viewing window values
#define INIT_VIEW_X	 0.0 
#define INIT_VIEW_Y  0.0
#define INIT_VIEW_Z -4.5
#define VIEW_LEFT	-2.0
#define VIEW_RIGHT	 2.0
#define VIEW_BOTTOM	-2.0
#define VIEW_TOP	 2.0
#define VIEW_NEAR	 1.0
#define VIEW_FAR	 200.0

// My initialization values for lighting
GLfloat AmbientLight[] =	{ 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat DiffuseLight[] =	{ 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat SpecularLight[] =	{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat SpecRef[] =			{ 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat LightPos[] =		{-50.0f,50.0f,100.0f,1.0f};
GLubyte Shine =	128;	

////////////////////////////////////////////////
//Display the current object using MyImage's data
void DisplayObject(void) 
{
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Change the draw color to slate blue
	glColor3ub(50, 50, 150);
	
	//Save viewing matrix state
	glPushMatrix();
	
	// Rotate 45 degrees on each axis to show a little depth
	glRotatef(45.0,1,1,1);
	
	//Draw WireFrame Sphere
	glutWireSphere(1.0f, 30, 30);
	
	// Restore matrix state
	glPopMatrix();
	
	// Flush drawing commands
	glutSwapBuffers();
	
} // End of DisplayObject

void SetupRend()
{
	// Set background to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	
	// Enable lighting
	glEnable(GL_LIGHTING);
	
	// Set up and enable light zero
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glEnable(GL_LIGHT0);
	
	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	
	// Set material to folow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	// Set specular reflectivity and shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);
	glMateriali(GL_FRONT, GL_SHININESS, Shine);
	
}

// Set a perspective window
void ChangeWindow(GLsizei w, GLsizei h)	
{
	GLfloat Ratio;
	
	// Prevent division by zero
	if (h==0)
		h=1;
	
	// Set viewport to window dimensions
	glViewport(0,0,w,h);
	
	// Set the perspective ratios
	Ratio = (GLfloat)w/(GLfloat)h;
	
	// Reset coordinate system
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	// Set the viewing perspective
	gluPerspective(50.0f, Ratio, VIEW_NEAR, VIEW_FAR);
	
	// Set viewing translation
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( INIT_VIEW_X, INIT_VIEW_Y, INIT_VIEW_Z );
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	
}

//////////////////////////////////////////////////
// Main program module
void main(void)
{
	// Show a Welcome Screen with text instructions
	printf("  * *     Keyboard.c - Demonstration of Keyboard Interaction    * *  \n");
	printf("                      by Bryson R. Payne, M.Ed.\n\n");			//
	printf("Displays a simple wire sphere.\n\n");
	
	// Set the buffers we want for best viewing
	glutInitDisplayMode ( GLUT_DOUBLE	// double-buffered pixel format for flicker-free movement
		| GLUT_RGB		// use RGB pixel format (easy to color)
		| GLUT_DEPTH);	// use depth buffer (better perspective)
	
	// Create the viewing window
	glutCreateWindow ("Simple.c - Demonstration of Simple C++ OpenGL Code");
	
	glutReshapeFunc (ChangeWindow);	// Set function for resizing window
	glutDisplayFunc (DisplayObject);	// Set function for redisplaying
	SetupRend();	// Initialize and get ready to draw
	
	glutMainLoop(); // Keep on going until user gets tired
	
}