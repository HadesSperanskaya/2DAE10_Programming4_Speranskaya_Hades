#include <string>

#ifndef FONT_HEADER
#define FONT_HEADER

struct _TTF_Font;

namespace Engine
{
	
	class Font final
	{
	public:
		//functions
	
		Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;

		_TTF_Font* GetFont() const;

	private:

		//functions
		Font() = delete;

		//elements
		_TTF_Font* m_Font;
	};
}


#endif