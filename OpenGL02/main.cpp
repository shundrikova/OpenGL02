#include <windows.h>
#include <gl\freeglut.h>

static int w = 0, h = 0;

double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;

static int spin = 0;

void Init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glPushMatrix();
	GLfloat position1[] = { 0.0, 0.0, 1.5, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position1);
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4);

	/*GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuseLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat specularLight[] = { 10, 10, 10, 10 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);*/

	glPopMatrix();

	//glPushMatrix();
	//GLfloat position2[] = { 0.0, 0.0, 0.0, 1.0 };
	////glRotated(170.0, 1.0, 1.0, 1.0);
	//glLightfv(GL_LIGHT1, GL_POSITION, position2);
	////glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
	////glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);
	////glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.4);*/
	//glPopMatrix();

	// bronze cube
	glPushMatrix();
	GLfloat ambient_bronze[] = { 0.21, 0.13, 0.05, 1.00 };
	GLfloat diffuse_bronze[] = { 0.71, 0.43, 0.18, 1.00 };
	GLfloat specular_bronze[] = { 0.39, 0.27, 0.17, 1.00 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_bronze);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_bronze);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_bronze);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.6);

	glTranslatef(2.0, -1.0, 0.0);
	glScalef(2.0, 1.0, 2.0);
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

	glScalef(2.0, 3.0, 2.0);

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

	glTranslatef(-2.0, -0.5, 0.0);
	glScalef(2.0, 2.0, 2.0);

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
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	//gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("OpenGL");
	Init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}