#include "winfont.h"

#include <GL/glew.h>
#include <stdio.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <windows.h>
#define MAX_CHAR 127

GLuint lists;
void FontCreate(int size, int charset, const char * face, HDC dc) {
	// HFONT hFont = CreateFontA(size, 0, 0, 0, 
	// 	FW_MEDIUM, 0, 0, 0,
	// 	charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	// 	DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	// HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	// DeleteObject(hOldFont);
	
	// HFONT hFont = CreateFont(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,  
 //        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,  
 //        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);  
	HFONT hFont = CreateFont(
			48,
			0,
			0,
			0, 
			FW_REGULAR, 
			FALSE, 
			FALSE,  
			FALSE, 
			ANSI_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_MODERN,
			"Comic Sans MS"
			);
    HFONT hOldFont = (HFONT)SelectObject(dc, hFont);  
    DeleteObject(hOldFont); 
    lists = glGenLists(MAX_CHAR);
	wglUseFontBitmaps(CreateCompatibleDC(NULL), 0, MAX_CHAR, lists);
}

void InitFont() {
	GLuint textureId = 0;
	FT_Library pFTLib = NULL;
	FT_Face pFTFace = NULL;
	FT_Error error = 0;
	error = FT_Init_FreeType(&pFTLib);
	if(error) {
		pFTLib = 0;
		return -1;
	}
	error = FT_New_Face(pFTLib, "D:\\字体下载\\柏青简体.ttf", 0, &pFTFace);
	if(!error) {
		FT_Set_Char_Size(pFTFace, 48<<6, 48<<6, 300,300);
		FT_Glyph glyph;
		FT_Select_Charmap(pFTFace, FT_ENCODING_UNICODE);
		wchar_t * pOut;
		char * gbBuffer = "你";
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,gbBuffer,2,pOut,1);
		FT_UInt glyph_index = FT_Get_Char_Index(pFTFace,pOut[0]);
		FT_Load_Glyph(pFTFace, glyph_index, FT_LOAD_DEFAULT);
		error = FT_Get_Glyph(pFTFace->glyph, &glyph);
		FT_Render_Glyph(pFTFace->glyph, FT_RENDER_MODE_MONO);
		if(!error) {
			printf("hello world\n");
			FT_Glyph_To_Bitmap( & glyph, ft_render_mode_normal,  0 ,  1 );  
	        FT_BitmapGlyph    bitmap_glyph  =  (FT_BitmapGlyph)glyph;  
	        FT_Bitmap bitmap  =  bitmap_glyph -> bitmap;  
			int height = bitmap.rows;
			int width = bitmap.width;
			unsigned char* data = (unsigned char*)malloc(4*width*height);
			int i,j;
			/*for (j = 0 ; j < bitmap.rows;  ++ j) {  
	             for (i = 0 ; i < bitmap.width;  ++ i)  {  
					char ch = (i>=bitmap.width || j>=bitmap.rows) ? 
                                                0 : bitmap.buffer[i + bitmap.width*j];
					 data[3*(i+(height-j-1)*width)]=  
                     data[3*(i+(height-j-1)*width)+1] =  
                     data[3*(i+(height-j-1)*width)+2] = ch;
					 if(ch == 0) {
						 data[3*(i+(height-j-1)*width)+3] = 255;
						 printf("0");
					 } else {
						 data[3*(i+(height-j-1)*width)+3] = 0;
						 printf("1");
					 }
				 }
				 printf("\n");
	        } */ 
			for(j=0; j  < height ; j++)  {  
				for(i=0; i < width; i++) {  
					unsigned char _vl =  (i>=bitmap.width || j>=bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];  
					data[(4*i + (height - j - 1) * width * 4)] = 0xFF;  
					data[(4*i + (height - j - 1) * width * 4)+1] = 0xFF;  
					data[(4*i + (height - j - 1) * width * 4)+2] = 0xFF;  
					data[(4*i + (height - j - 1) * width * 4)+3] = _vl;  
				}  
			 }
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.width, bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			FT_Done_Glyph(glyph);
			glyph = NULL;
			free(data);
		}
		FT_Done_Face(pFTFace);
		pFTFace = NULL;
	}
	FT_Done_FreeType(pFTLib);
	pFTLib = NULL;
	return 0;
}

void DrawString(const char * str) {

	// static int isFirstCall = 1;
	// static GLuint lists;
	// if(isFirstCall) {
	// 	isFirstCall = 0;
	// 	lists = glGenLists(MAX_CHAR);
	// 	wglUseFontBitmaps(CreateCompatibleDC(NULL), 0, MAX_CHAR, lists);
	// }
	for(; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}