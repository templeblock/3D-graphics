#include "shader_utils.h"

GLuint create_shader(const char* file_name, GLenum type) {

	const GLchar* shader_source = file_read(file_name);
	GLint compile_ok = GL_FALSE;

	const char *source[2] = {
		#ifdef GL_ES_VERSION_2_0
		"#version 100\n"
		"#define GLES2\n",
		#else
		"#version 120\n",
		#endif
		shader_source
	};

	GLuint s = glCreateShader(type);
	glShaderSource(s, 2, source, NULL);
	free((void*)shader_source);
	glCompileShader(s);
	glGetShaderiv(s, GL_COMPILE_STATUS, &compile_ok);

	if (compile_ok == GL_FALSE) {
		fprintf(stderr, "Error compiling: %s\n", file_name);
		print_log(s);
		glDeleteShader(s);
		return 0;
	}

	return s;

}

void print_log(GLuint object) {

	GLint log_length = 0;
	if (glIsShader(object)) {
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	}
	else if (glIsProgram(object)) {
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	}
	else {
		fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}

	char* log = (char*) malloc(log_length);

	if (glIsShader(object)) {
		glGetShaderInfoLog(object, log_length, NULL, log);
	}
	else if (glIsProgram(object)) {
		glGetProgramInfoLog(object, log_length, NULL, log);
	}

	fprintf(stderr, "%s", log);
	free(log);

}

char* file_read(const char* filename) {
	FILE* input = fopen(filename, "rb");
	if (input == NULL )
		return NULL ;

	if (fseek(input, 0, SEEK_END) == -1) {
		return NULL;
	}

	long size = ftell(input);

	if (size == -1) {
		return NULL;
	}

	if (fseek(input, 0, SEEK_SET) == -1) {
		return NULL;
	}

	/*if using c-compiler: don't cast malloc's return value*/
	char *content = (char*) malloc((size_t) size + 1);
	if (content == NULL) {
		return NULL ;
	}

	fread(content, 1, (size_t) size, input);
	if (ferror(input)) {
		free(content);
		return NULL ;
	}

	fclose(input);
	content[size] = '\0';
	return content;
}
