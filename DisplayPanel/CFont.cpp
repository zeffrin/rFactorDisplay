#include "CFont.h"

CFont CFont::Font;

void CFont::OnInit()
{

	TTF_Init();
	font = TTF_OpenFont(FONTNAME, FONTSIZE );
	fontColor.b = 0;
	fontColor.g = 255;
	fontColor.r = 0;
	fontColor.unused = 0;
	Linespace = 19;

}

void CFont::OnCleanup()
{
	TTF_CloseFont(font);
	TTF_Quit();
}

void CFont::Draw(char *msg, SDL_Surface *Surf, SDL_Rect Pos)
{
	SDL_Surface *text;

	text = TTF_RenderText_Solid(
			font, // This is the TTF_Font to use.
			msg, // This is the text to render.
			fontColor // This is the color to use.
	);
	Pos.x -= text->w;
	SDL_BlitSurface(text, NULL, Surf, &Pos);
	SDL_FreeSurface(text);
}
