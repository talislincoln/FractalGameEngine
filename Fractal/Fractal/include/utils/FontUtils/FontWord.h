#ifndef FONTWORD_H
#define FONTWORD_H
#include <vector>
#include "FontCharacter.h"
namespace fractal {
	class FontWord {
	public:

	private:
		std::vector<FontCharacter*> m_word;
		float width;
		float fontSize;
	};
}

#endif // !FONTWORD_H
