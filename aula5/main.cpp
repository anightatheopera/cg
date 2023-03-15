#include <string>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

// funções desenho
void make_tree(float x, float y, float z) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(-90, 1, 0, 0);
		glColor3f(92.0/255, 53.0/255, 35.0/255);
		glutSolidCone(0.35f, 1.0f, 10, 10);
		glColor3f(63.0/255, 135.0/255, 55.0/255);
		glTranslatef(0, 0, 1);
		glutSolidCone(1.0f, 3.0f, 10, 10);
	glPopMatrix();
}

void tree_placement() {
	for (int i = 0; i < 100; i++) {
		float x = (rand() % 100);
		float z = (rand() % 100);
		if(pow(x,2) + pow(z,2) > pow(50,2))
			make_tree(x, 0, z);
		x = (rand() % 100) * -1;
		z = (rand() % 100) * -1;
		if(pow(x,2) + pow(z,2) > pow(50,2))
			make_tree(x, 0, z);
		x = (rand() % 100) * -1;
		z = (rand() % 100);
		if(pow(x,2) + pow(z,2) > pow(50,2))
			make_tree(x, 0, z);
		x = (rand() % 100);
		z = (rand() % 100) * -1;
		if(pow(x,2) + pow(z,2) > pow(50,2))
			make_tree(x, 0, z);
	}
}

void make_teapot(std::string color){
	if(color == "blue"){
		glPushMatrix();
			glTranslatef(15, 0.8, 0);
			glRotatef(0, 1, 0, 0);
			glColor3f(73.0/255, 97.0/255, 145.0/255);
			glutSolidTeapot(1.0f);
		glPopMatrix();
	}
	if(color == "red"){
		glPushMatrix();
			glTranslatef(35, 0.8, 0);
			glRotatef(90, 0, 1, 0);
			glColor3f(239.0/255, 21.0/255, 21.0/255);
			glutSolidTeapot(1.0f);
		glPopMatrix();
	}
}

void bteapot_circle(){
	for(int i = 0; i <= 360; i+= 45){
		make_teapot("blue");
		glRotatef(i, 0, 1, 0);
	}
}

void rteapot_circle(){
	for(double i = 0; i <= 360; i+= 22.5){
		make_teapot("red");
		glRotatef(i, 0, 1, 0);
	}
}


void make_torus(float inner, float outter, int sides, int rings){
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glColor3f(146.0/255, 32.0/255, 195.0/255);
		glutSolidTorus(inner, outter, sides, rings);
	glPopMatrix();
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();
	
	// put code to draw scene in here
	srand(0); // start the random number sequence
	rand(); // returns a number between 0 and RAND_MAX
	bteapot_circle();
	rteapot_circle();
	make_torus(0.5f, 1.0f, 10, 10);
	tree_placement();
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
