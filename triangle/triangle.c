#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "shaders/vertex.c"
#include "shaders/fragment.c"

GLuint program;
GLint attribute_coord2d;

int init_resources(void) {

	GLint link_ok = GL_FALSE;

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	if (loadVertexShader(vs) != 1) {
		return 0;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	if (loadFragmentShader(fs) != 1) {
		return 0;
	}

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		return 0;
	}

	const char* attribute_name = "coord2d";
	attribute_coord2d = glGetAttribLocation(program, attribute_name);
	if (attribute_coord2d == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	    return 0;
	}

	return 1;

}

void free_resources() {
	glDeleteProgram(program);
}

void onDisplay() {

	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glEnableVertexAttribArray(attribute_coord2d);
	GLfloat triangle_vertices[] = {
	    -0.8,  0.8,
	     0.8, -0.8,
	    -0.8, -0.8,

	    -0.8,  0.8,
	     0.8,  0.8,
	     0.8, -0.8,
	};
	glVertexAttribPointer(
	    attribute_coord2d,
	    2,
	    GL_FLOAT,
	    GL_FALSE,
	    0,
	    triangle_vertices
	);

	/* Push each element in buffer_vertices to the vertex shader */
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(attribute_coord2d);

	glutSwapBuffers();

}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("My First Triangle -- Different Build -- more!");

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
