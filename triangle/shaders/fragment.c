#include <GL/glut.h>

int loadFragmentShader(GLuint fs) {

	GLint compile_ok = GL_FALSE;

	const char *fs_source =
		"#version 120                                 \n"
		"void main(void) {                            \n"
		"	gl_FragColor[0] = gl_FragCoord.x/640.0;   \n"
		"   gl_FragColor[1] = gl_FragCoord.y/480.0;   \n"
		"   gl_FragColor[2] = 0.5;                    \n"
		"}                          ";
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);

	if (compile_ok == 0) {
		fprintf(stderr, "Error in fragment shader\n");
		return 0;
	}

	return 1;

}
