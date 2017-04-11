#ifndef FONTCHARACTER_H
#define FONTCHARACTER_H
#include <FractalMath\Vector.h>
namespace fractal {
	struct FontCharacter {
		FontCharacter(int id, float xTextureCoord, float yTextureCoord, float xTexSize, float yTexSize,
			float xOffset, float yOffset, float sizeX, float sizeY, float xAdvance);
		FontCharacter(int id, fmath::Vector2& yTextureCoord,fmath::Vector2& yTexSize,
			 fmath::Vector2& yOffset, fmath::Vector2& sizeY, float xAdvance);
		int id;
		fmath::Vector2 textureCoord;
		fmath::Vector2 maxTextureCoord;
		fmath::Vector2 offset;
		fmath::Vector2 size;
		float xAdvance;
	};


}

#endif // !FONTCHARACTER_H
