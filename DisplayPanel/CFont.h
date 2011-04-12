//==============================================================================
// FPS Class
//==============================================================================
#ifndef _CFONT_H_
    #define _CFONT_H_

#include <SDL.h>
#include <SDL_TTF.h>

#include "Define.h"

//==============================================================================
class CFont {
	public:
		static CFont Font;

	private:
		TTF_Font *font;
		SDL_Color fontColor;

	public:
		void	OnInit();
		void	OnCleanup();
		void    Draw(char *msg, SDL_Surface *Surf, SDL_Rect Pos);

		int		Linespace;
			
};

//==============================================================================
#endif
