#ifndef JK2D_PLATFORM_GL_H
#define JK2D_PLATFORM_GL_H

/* macOS supplies the legacy fixed-function OpenGL API system-wide. */
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/wglew.h>
#endif

#endif
