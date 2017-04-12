#include "utils\FontUtils\FontCharacter.h"

namespace fractal {
	FontCharacter::FontCharacter(int id, float xTextureCoord, float yTextureCoord, float xTexSize, float yTexSize, float xOffset, float yOffset, float sizeX, float sizeY, float xAdvance)
	{
		this->id = id;
		this->textureCoord = fmath::Vector2(xTextureCoord, yTextureCoord);
		this->offset = fmath::Vector2(xOffset, yOffset);
		this->size = fmath::Vector2(xTexSize, yTexSize);
		this->xAdvance = xAdvance;
		this->maxTextureCoord = fmath::Vector2(xTexSize + xTextureCoord, yTexSize + yTextureCoord);	
	}
	FontCharacter::FontCharacter(int id, fmath::Vector2 & TextureCoord, fmath::Vector2 & TexSize, fmath::Vector2 & Offset, fmath::Vector2 & size, float xAdvance)
	{
		this->id = id;
		this->textureCoord =TextureCoord;
		this->offset = Offset;
		this->size = TexSize;
		this->xAdvance = xAdvance;
		this->maxTextureCoord = TexSize + TextureCoord;
	}
}