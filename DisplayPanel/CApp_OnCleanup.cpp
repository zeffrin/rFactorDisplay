//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnCleanup() {

	CFont::Font.OnCleanup();

	SDL_FreeSurface(background);

	SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}

//==============================================================================
