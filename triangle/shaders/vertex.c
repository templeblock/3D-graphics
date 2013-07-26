#include <GL/glut.h>

int loadVertexShader(GLuint vs) {

	GLint compile_ok = GL_FALSE;

	const char *vs_source =
		#ifdef GL_ES_VERSION_2_0
	    "#version 100                             \n"  // OpenGL ES 2.0
		#else
	    "#version 120                             \n"  // OpenGL 2.1
		#endif
	    "attribute vec2 coord2d;                  \n"
	    "void main(void) {                        \n"
	    "	gl_Position = vec4(coord2d, 0.0, 1.0);\n"
	    "}                                          ";
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);

	if (compile_ok == 0) {
		fprintf(stderr, "Error in vertex shader\n");
		return 0;
	}

	return 1;

}
