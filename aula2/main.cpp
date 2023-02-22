#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float angle = 0.0f;
float lx=1.0f,ly=1.0f,lz=1.0f;
float a=1.0f,b=1.0f,c=1.0f;

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


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	glBegin(GL_LINES);
	// draw axis 
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f( 1.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();
	glTranslatef(0.0+lx,0.0+ly,0.0+lz);
	glRotatef(angle,0.0,1.0,0.0);
	glScalef(1.0*a,1.0*b,1.0*c);
	// draw pyramid
			glBegin(GL_TRIANGLES);
		// Front
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		// Right
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		// Back
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		// Left
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glEnd();
		// draw square
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glColor3f(1.0f,1.0f, 1.0f);
		
		glEnd();
	

	glutSwapBuffers();
}



// put the geometric transformations here
void scale(unsigned char key, int _x, int _y){
	switch (key)
	{
	case 'w':
		b -= 1;
		break;
	case 's':
		b += 1;
		break;
	case 'a':
		a -= 1;
		break;
	case 'd':
		a += 1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void move(unsigned char key) {
    switch (key) {
        case 't':
            ly += 0.1;
            break;
        case 'g':
            ly -= 0.1;
            break;
        case 'f':
            lx -= 0.1;
            break;
        case 'h':
            lx += 0.1;
            break;
        case 'u':
            lz += 0.1;
            break;
        case 'j':
            lz -= 0.1;
            break;
    }
    glutPostRedisplay();
}

void rotate(int key){
	switch (key)
	{
	case 'p':
		angle -= 1.0f;
		break;
	case 'l':
		angle += 1.0f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void func(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            scale(key, x, y);
            break;
        case 's':
            scale(key, x, y);
            break;
        case 'a':
            scale(key, x, y);
            break;
        case 'd':
            scale(key, x, y);
            break;
        case 'p':
            rotate(key);
            break;
        case 'l':
            rotate(key);
            break;
        case 't':
            move(key);
            break;
        case 'g':
            move(key);
            break;
        case 'f':
            move(key);
            break;
        case 'h':    
            move(key);
            break;
        case 'u':
            move(key);
            break;
        case 'j':
            move(key);
            break;
    }
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

	
// put here the registration of the keyboard callbacks
	glutKeyboardFunc(func);



//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
