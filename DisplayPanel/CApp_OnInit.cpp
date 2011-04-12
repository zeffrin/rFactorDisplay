//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
																			//  | SDL_NOFRAME
    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	CFont::Font.OnInit();

	background = CSurface::OnLoad("Background.bmp");
		
	if( !(rFactorInfo::rFactor.Initialise()) )
	{
		return false;
	}

	return true;
}

//==============================================================================
