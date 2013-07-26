#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

int init_resources(void) {
	return 1;
}

void free_resources() {
}

void onDisplay() {

	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
	glClear(GL_COLOR_BUFFER_BIT);

	// update the buffer here

	glutSwapBuffers();

}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("My First Triangle!");

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	if (init_resources() == 1) {
		glutDisplayFunc(onDisplay);
		glutMainLoop();
	}

	free_resources();
	return EXIT_SUCCESS;

}
