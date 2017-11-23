#include <windows.h>
#include <gl\freeglut.h>
#include <cmath>

static int w = 0, h = 0;

double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;

double pedestal_rotate_x = 0;
double pedestal_rotate_y = 0;
double pedestal_rotate_z = 0;

bool camera_rotation = false;

int oldX, oldY;
bool rotate = false;
float theta = 0, phi = 0;
int radius = 5;
double eyeX = 2.0, eyeY = 3.0, eyeZ = 4.0, pickObjX = 0, pickObjY = 0, pickObjZ = 0;

float zoom = 1.0;

void Init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

void Enable_Light0(void) {
	glEnable(GL_LIGHT0);

	GLfloat position[] = { -2.0, 0.0, 2.0, 1.0 };
	GLfloat ambientLight[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
}

void Enable_Light1(void) {
	glEnable(GL_LIGHT1);

	GLfloat position[] = { 2.5, 0.0, -2.5, 1.0 };
	GLfloat ambientLight[] = { 0.5, 0.0, 0.0, 1.0 };
	GLfloat diffuseLight[] = { 1.0, 0.0, 1.0, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
}

void Enable_Light2(void) {
	glEnable(GL_LIGHT2);

	GLfloat position[] = { 2.0, 2.0, 3.0, 1.0 };
	//{ 0.8, 0.8, 0.2, 1.0 };
	GLfloat spot_direction[] = { 0.0, 0.0, 1.0 };

	GLfloat ambientLight[] = { 0.5, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT2, GL_POSITION, position);

	//glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 15.0);

}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	if (camera_rotation) {
		eyeX = pickObjX + radius*cos(phi)*sin(theta);
		eyeY = pickObjY + radius*sin(phi)*sin(theta);
		eyeZ = pickObjZ + radius*cos(theta);
	}
	
	gluLookAt(eyeX, eyeY, eyeZ, pickObjX, pickObjY, pickObjZ, 0, 1, 0);

	// light 0
	Enable_Light0();

	// light 1
	Enable_Light1();

	// light 2
	Enable_Light2();

	glScalef(zoom, zoom, zoom);

	glPushMatrix();

	glBegin(GL_LINES);
	for (int i = -15; i <= 15; i++) {
		glVertex3f(i, -0.5, -15);
		glVertex3f(i, -0.5, 15);

		glVertex3f(-15, -0.5, i);
		glVertex3f(15, -0.5, i);
	};
	glEnd();
	glPopMatrix();

	glPushMatrix();

	glRotatef(pedestal_rotate_x, 1.0, 0.0, 0.0);
	glRotatef(pedestal_rotate_y, 0.0, 1.0, 0.0);
	glRotatef(pedestal_rotate_z, 0.0, 0.0, 1.0);

	// bronze cube
	glPushMatrix();
	GLfloat ambient_bronze[] = { 0.21, 0.13, 0.05, 1.00 };
	GLfloat diffuse_bronze[] = { 0.71, 0.43, 0.18, 1.00 };
	GLfloat specular_bronze[] = { 0.39, 0.27, 0.17, 1.00 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_bronze);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_bronze);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_bronze);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.6);

	glTranslatef(1.0, -0.15, 0.0);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	glScalef(1.0, 0.7, 1.0);

	glutSolidCube(1);
	glPopMatrix();

	// golden cube
	glPushMatrix();
	GLfloat ambient_golden[] = { 0.25, 0.22, 0.06, 1.00 };
	GLfloat diffuse_golden[] = { 0.35, 0.31, 0.09, 1.00 };
	GLfloat specular_golden[] = { 0.80, 0.72, 0.21, 1.00 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_golden);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_golden);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_golden);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 51.2);

	glTranslatef(0.0, 0.25, 0.0);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.5, 1.0);

	glutSolidCube(1);
	glPopMatrix();

	// silver cube
	glPushMatrix();
	GLfloat ambient_silver[] = { 0.23, 0.23, 0.23, 1.00 };
	GLfloat diffuse_silver[] = { 0.28, 0.28, 0.28, 1.00 };
	GLfloat specular_silver[] = { 0.77, 0.77, 0.77, 1.00 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_silver);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_silver);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_silver);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 51.2);

	glTranslatef(-1.0, 0.0, 0.0);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);

	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void Reshape(int width, int height) {
	w = width;   h = height;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
	gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(2.0, 3.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
		// вокруг центра сцены		
		// все вокруг центра пьедестала почета
		case 'w': pedestal_rotate_x -= 5; break;
		case 's': pedestal_rotate_x += 5; break;
		case 'a': pedestal_rotate_y += 5; break;
		case 'd': pedestal_rotate_y -= 5; break;
		case 'q': pedestal_rotate_z += 5; break;
		case 'e': pedestal_rotate_z -= 5; break;

		// zoom
		/*case 'i': zoom += 0.1; break;
		case 'o': zoom -= 0.1; break;*/
	}
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {

	switch (key) {
		// вокруг своей оси
		case GLUT_KEY_UP: rotate_x += 5; break;
		case GLUT_KEY_DOWN: rotate_x -= 5; break;
		case GLUT_KEY_RIGHT: rotate_y += 5; break;
		case GLUT_KEY_LEFT: rotate_y -= 5; break;
		case GLUT_KEY_PAGE_UP: rotate_z += 5; break;
		case GLUT_KEY_PAGE_DOWN: rotate_z -= 5; break;

		case GLUT_KEY_CTRL_L: camera_rotation = !camera_rotation; break;
	}

	glutPostRedisplay();
}

void mouseMove(int x, int y) {
	if (rotate) {
		theta += (x - oldX)*0.003f;
		phi += (y - oldY)*0.003f;
	}
	oldX = x;
	oldY = y;
	glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y) {
	rotate = false;
	if (button == GLUT_LEFT_BUTTON) {	
		oldX = x;
		oldY = y;
		rotate = true;
	}
	
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	(direction > 0) ? zoom += 0.1 : zoom -= 0.1;
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("OpenGL");
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(Keyboard);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutMouseWheelFunc(mouseWheel);

	glutMainLoop();
	return 0;
}