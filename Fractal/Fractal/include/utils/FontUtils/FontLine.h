#ifndef FONTLINE_H
#define FONTLINE_H
#include "FontWord.h"
namespace fractal {
	class FontLine {
	public :
	private:
		float m_maxWidth;
		float m_spaceSize;
		float m_currentLineWidth;

		std::vector<FontWord*> m_word;
	};
}

#endif // !FONTLINE_H
