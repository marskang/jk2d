#ifndef ex_geometry_h
#define ex_geometry_h

/**
*坐标是顺时针填写
**/
void DrawQuadF(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void DrawRectF(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float lineWidth);
void TransformCoord(int oldX, int oldY,float *x, float *y);
void DrawQuadI(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void DrawQuad(int x, int y, int w, int h);
#endif