#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "shader_utils.h"

GLuint program;
GLint attribute_coord2d;
GLuint vbo;

int init_resources(void) {

	GLfloat triangle_vertices[] = {
			0.0,  0.8,
			-0.8, -0.8,
			0.8, -0.8,
	};
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	GLuint vs = create_shader("shaders/vertex.glsl", GL_VERTEX_SHADER);
	if (vs == 0) {
		return 0;
	}

	GLuint fs = create_shader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	if (fs == 0) {
		return 0;
	}

	GLint link_ok = GL_FALSE;

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		print_log(program);
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
	glDeleteBuffers(1, &vbo);
}

void onDisplay() {

	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(attribute_coord2d);
	glVertexAttribPointer(
	    attribute_coord2d,
	    2,
	    GL_FLOAT,
	    GL_FALSE,
	    0,
	    0
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
