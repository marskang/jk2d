#include "global.h"

static int width = 800;
static int height = 600;

int GetScreenWidth() {
	return width;
}

int GetScreenHeight() {
	return height;
}

void SetScreenWidth(int w) {
	width = w;
}

void SetScreenHeight(int h) {
	height = h;
}

void SetWH(int w, int h) {
	width = w;
	height = h;
}