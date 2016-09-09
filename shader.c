#include "shader.h"
void DrawTexture(Texture * texture, float alpha) {
	glColor4f(1.0f, 1.0f, 1.0f, alpha);
	float vertices[] = {
 		texture->dCoordf[3].x, texture->dCoordf[3].y,0.0,
		texture->dCoordf[2].x, texture->dCoordf[2].y,0.0,
		texture->dCoordf[1].x, texture->dCoordf[1].y,0.0,
		texture->dCoordf[3].x, texture->dCoordf[3].y,0.0,
		texture->dCoordf[1].x, texture->dCoordf[1].y,0.0,
		texture->dCoordf[0].x, texture->dCoordf[0].y,0.0,
	};
	float texCoords[] = {
		texture->sCoordf[0].x, texture->sCoordf[0].y,
		texture->sCoordf[1].x, texture->sCoordf[1].y,
		texture->sCoordf[2].x, texture->sCoordf[2].y,
		texture->sCoordf[0].x, texture->sCoordf[0].y,
		texture->sCoordf[2].x, texture->sCoordf[2].y,
		texture->sCoordf[3].x, texture->sCoordf[3].y,
	};
	const GLubyte indices[] = {0,1,2,3,4,5};
	glBindTexture(GL_TEXTURE_2D, texture->textureId);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_BYTE, indices);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}