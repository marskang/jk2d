#ifndef ex_texture_h
#define ex_texture_h
#include <png.h>
#include <GL/glew.h>
#include <GL/wglew.h>
typedef struct PointD {
	int x;
	int y;
}PointD;
typedef struct PointF {
	float x;
	float y;
}PointF;

typedef struct Texture {
	png_uint_32 width;
	png_uint_32 height;
	PointF sCoordf[4];
	PointF dCoordf[4];
	PointD sCoord[4];
	PointD dCoord[4];
	unsigned int textureId;
	int x;
	int y;
	GLubyte * data;
}Texture;

Texture * LoadPng(char *file_name);
Texture * BindTexture(char *file_name,int sx1, int sy1, int sx2, int sy2,int dx1, int dy1, int dx2, int dy2);
void CalTexCoord(Texture * texture,int sx1, int sy1, int sx2, int sy2,int dx1, int dy1, int dx2, int dy2);
#endif