#include <GL/glew.h>
#include <GL/wglew.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <png.h>
#include <zlib.h>
#include <assert.h>
#include "texture.h"
#include "global.h"
#define MAX_TEXTURE 127

unsigned int textureIds[MAX_TEXTURE];
unsigned int nTextureId = 0;
Texture * LoadPng(char *file_name) {
	png_structp png_ptr;
	png_infop info_ptr;
	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type;
	FILE *fp = NULL;
	if((fp = fopen(file_name, "rb")) == NULL) {
		return NULL;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
		0,0,0);
	if(png_ptr == NULL) {
		fclose(fp);
		return NULL;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return NULL;
	}
	if(setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		return NULL;
	}
	png_init_io(png_ptr, fp);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
	&color_type, &interlace_type, NULL, NULL);
	if(color_type == PNG_COLOR_TYPE_RGB_ALPHA) {
		bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	}
	if(color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
	}
 	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	}
	if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS) != 0) {
		png_set_tRNS_to_alpha(png_ptr);
	}
	png_read_update_info(png_ptr, info_ptr);
	png_bytep row_pointers[height];
	int row, col;
	for(row = 0; row < height; row++) {
		row_pointers[row] = NULL;
	}
	for(row = 0; row < height; row++) {
		row_pointers[row] = png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));
	}
	png_read_image(png_ptr, row_pointers);
	GLubyte * rgba = (GLubyte *)malloc(width * height * 4 * sizeof(GLubyte) + 10);
	int pos = (width * height * 4) - (4 * width);
	for(row = 0; row < height; row++) {
		for(col = 0; col < (4 * width); col += 4) {
			rgba[pos++] = row_pointers[row][col];
			rgba[pos++] = row_pointers[row][col + 1];
			rgba[pos++] = row_pointers[row][col + 2];
			rgba[pos++] = row_pointers[row][col + 3];
		}
		pos = (pos - (width * 4) * 2);
	}

	Texture * texture = (Texture*)malloc(sizeof(Texture));
	texture->data = rgba;
	texture->width = width;
	texture->height = height;
	fclose(fp);
	fp = NULL;
	return texture;
}

Texture * BindTexture(char *file_name,int sx1, int sy1, int sx2, int sy2,int dx1, int dy1, int dx2, int dy2) {
	Texture * texture = LoadPng(file_name);
	glGenTextures(1, &nTextureId);
	texture->textureId = nTextureId;
	glBindTexture(GL_TEXTURE_2D, nTextureId);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width,texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//计算坐标
	CalTexCoord(texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
	free(texture->data);
	texture->data = NULL;
	return texture;
}

void CalTexCoord(Texture *texture, int sx1, int sy1, int sx2, int sy2,int dx1, int dy1, int dx2, int dy2) {
	
	png_uint_32 w = texture->width;
	png_uint_32 h = texture->height;
	texture->sCoordf[0].x = sx1 / (float)w;
	texture->sCoordf[0].y = sy1 / (float)h;
	texture->sCoordf[1].x = sx2 / (float)w;
	texture->sCoordf[1].y = sy1 / (float)h;
	texture->sCoordf[2].x = sx2 / (float)w;
	texture->sCoordf[2].y = sy2 / (float)h;
	texture->sCoordf[3].x = sx1 / (float)w;
	texture->sCoordf[3].y = sy2 / (float)h;
	int screenW = GetScreenWidth();
	int screenH = GetScreenHeight();
	float halfW = screenW / 2.0;
	float halfH = screenH / 2.0;
	float dxf1 = dx1 - halfW;
	float dyf1 = halfH - dy1;
	float dxf2 = dx2 - halfW;
	float dyf2 = halfH - dy2;
	texture->dCoordf[0].x = dxf1 / halfW;
	texture->dCoordf[0].y = dyf1 / halfH;
	texture->dCoordf[1].x = dxf2 / halfW;
	texture->dCoordf[1].y = dyf1 / halfH;
	texture->dCoordf[2].x = dxf2 / halfW;
	texture->dCoordf[2].y = dyf2 / halfH; 
	texture->dCoordf[3].x = dxf1 / halfW;
	texture->dCoordf[3].y = dyf2 / halfH;

	printf("%.2f %.2f %.2f %.2f \n %.2f %.2f %.2f %.2f    iiiiiii \n",
	texture->dCoordf[0].x ,
	texture->dCoordf[0].y,
	texture->dCoordf[1].x ,
	texture->dCoordf[1].y,
	texture->dCoordf[2].x,
	texture->dCoordf[2].y,
	texture->dCoordf[3].x,
	texture->dCoordf[3].y);
	printf("=========================================================zzzzzzzzzzzz\n");
	printf("%.2f %.2f %.2f %.2f \n %.2f %.2f %.2f %.2f \n",
	texture->sCoordf[0].x ,
	texture->sCoordf[0].y,
	texture->sCoordf[1].x ,
	texture->sCoordf[1].y,
	texture->sCoordf[2].x,
	texture->sCoordf[2].y,
	texture->sCoordf[3].x,
	texture->sCoordf[3].y);
}
