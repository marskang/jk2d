#ifndef ex_winfont_h
#define ex_winfont_h
#include <windows.h>
void FontCreate(int size, int charset, const char * face, HDC dc);

void DrawString(const char * str);

void InitFont();
#endif