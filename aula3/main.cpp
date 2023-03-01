#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>


// Global variables
std::vector<int> modes = {GL_FILL, GL_LINE, GL_POINT};
int mode = 0;
float angle_y = 0.0f; // angle of rotation for the camera direction (x/y-plain)
float angle_z = 0.0f; // angle of rotation for the camera direction (x/z-plain)
float radius_camera = 5.0f; // radius of the camera position



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


void drawCylinder(float radius, float height, int slices) {

    float x, y, z, px, py, pz;
    
    for (int i = 0; i < slices; ++i) {
		float delta = (2 * M_PI / slices); // angulo de uma fatia para a outra 
        float alpha = delta * i;
		float beta = delta * (i + 1);
		glBegin(GL_QUADS);
			glVertex3f(radius * sin(alpha), -(height/2), radius * cos(alpha));
			glVertex3f(radius * sin(beta), -(height/2), radius * cos(beta));
			glVertex3f(radius * sin(beta), (height/2), radius * cos(beta));
			glVertex3f(radius * sin(alpha), (height/2), radius * cos(alpha));
        glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(radius * sin(alpha), -(height/2), radius * cos(alpha));
			glVertex3f(0, -(height/2), 0);
			glVertex3f(radius * sin(beta), -(height/2), radius * cos(beta));
			glVertex3f(radius * sin(beta), (height/2), radius * cos(beta));
			glVertex3f(0, (height/2), 0);
			glVertex3f(radius * sin(alpha), (height/2), radius * cos(alpha));
			

		glEnd();

    }
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(radius_camera*cos(angle_y)*sin(angle_z),radius_camera*sin(angle_y),radius_camera*cos(angle_y)*cos(angle_z),
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawCylinder(1,2,1000);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
	// put code to process regular keys in here
	switch (c) {
	    case 'm':
	    case 'M':
	        mode = (mode + 1) % modes.size();
	        glPolygonMode(GL_FRONT_AND_BACK, modes[mode]);
			glutPostRedisplay();
	        break;
	    case '-':
			radius_camera += 0.1;
			glutPostRedisplay();
			break;
	    case '+':
			radius_camera -= 0.1;
			glutPostRedisplay();
			break;
	// Exit because bspwm has no min, max or close buttons
	    case 'q':
	    case 'Q':
	    	exit(0);
	default:
		break;
	}


}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

	switch (key) {
		case GLUT_KEY_LEFT : 
			angle_z -= 0.1f;
			break;
		case GLUT_KEY_RIGHT : 
			angle_z += 0.1f;
			break;
		case GLUT_KEY_UP : 
			angle_y += 0.1f;
			break;
		case GLUT_KEY_DOWN : 
			angle_y -= 0.1f;
			break;
	}
	glutPostRedisplay();

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
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
