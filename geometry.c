#include "geometry.h"
#include "global.h"
#include <GL/glew.h>
#include <GL/wglew.h>

void DrawQuadF(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	float vertices[] = {
		x1,y1,0.0,
		x2,y2,0.0,
		x4,y4,0.0,
		x2,y2,0.0,
		x3,y3,0.0,
		x4,y4,0.0,
	};
	//const GLubyte indices[] = {0,1,2,3,4,5};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glDrawElements(GL_TRIANGLE_STRIP,6, GL_UNSIGNED_BYTE, indices);
	glDrawArrays(GL_TRIANGLES ,0,6);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawRectF(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float lineWidth) {
	glLineWidth(lineWidth);
	float vertices[] = {
		x1,y1,0.0,
		x2,y2,0.0,
		x3,y3,0.0,
		x4,y4,0.0,
	};
	const GLubyte indices[] = {0,1,2,3,4,5};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawElements(GL_TRIANGLE_STRIP,6, GL_UNSIGNED_BYTE, indices);
	// glDrawArrays(GL_LINE_LOOP ,0,6);
	glDisableClientState(GL_VERTEX_ARRAY);	
}

void DrawQuadI(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	float nx1,ny1,nx2,ny2,nx3,ny3,nx4,ny4;
	TransformCoord(x1, y1, &nx1, &ny1);
	TransformCoord(x2, y2, &nx2, &ny2);
	TransformCoord(x3, y3, &nx3, &ny3);
	TransformCoord(x4, y4, &nx4, &ny4);
	float vertices[] = {
		nx1,ny1,0.0,
		nx2,ny2,0.0,
		nx4,ny4,0.0,
		nx2,ny2,0.0,
		nx3,ny3,0.0,
		nx4,ny4,0.0,
	};
	const GLubyte indices[] = {0,1,2,3,4,5};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glDrawElements(GL_TRIANGLE_STRIP,6, GL_UNSIGNED_BYTE, indices);
	glDrawArrays(GL_TRIANGLES ,0,6);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawQuad(int x, int y, int w, int h) {
	int x1 = x;
	int y1 = y;
	int x2 = x + w;
	int y2 = y;
	int x3 = x + w;
	int y3 = y + h;
	int x4 = x;
	int y4 = y + h;
	DrawQuadI(x1, y1, x2, y2, x3, y3, x4, y4);
}

void TransformCoord(int oldX, int oldY,float *x, float *y) {
	int screenW = GetScreenWidth();
	int screenH = GetScreenHeight();
	float halfW = screenW / 2.0;
	float halfH = screenH / 2.0;
	float xf = oldX - halfW;
	float yf = halfH - oldY;
	*x = xf / halfW;
	*y = yf / halfH; 
}