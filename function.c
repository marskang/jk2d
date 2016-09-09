#include <function.h>

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
	int halfW = screenW / 2;
	int halfH = screenH / 2;
	dx1 = dx1 - halfW;
	dy1 = halfH - dy1;
	dx2 = dx2 - halfW;
	dy2 = halfH - dy2;
	texture->dCoordf[0].x = dx1 / (float)halfW;
	texture->dCoordf[0].y = dy1 / (float)halfH;
	texture->dCoordf[1].x = dx2 / (float)halfW;
	texture->dCoordf[1].y = dy1 / (float)halfH;
	texture->dCoordf[2].x = dx2 / (float)halfW;
	texture->dCoordf[2].y = dy2 / (float)halfH; 
	texture->dCoordf[3].x = dx1 / (float)halfW;
	texture->dCoordf[3].y = dy2 / (float)halfH;

