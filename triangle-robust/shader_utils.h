/*
 * shader_utils.h
 *
 *  Created on: Jul 26, 2013
 *      Author: jason.melanson
 */

#ifndef SHADER_UTILS_H_
#define SHADER_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

GLuint create_shader(const char* file_name, GLenum type);
void print_log(GLuint object);
char* file_read(const char* filename);

#endif /* SHADER_UTILS_H_ */
