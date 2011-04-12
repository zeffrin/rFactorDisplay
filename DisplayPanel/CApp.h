//==============================================================================
// SDL Tutorial 8
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>

#include "Define.h"

#include "CFPS.h"

#include "CEvent.h"
#include "CSurface.h"

#include "CFont.h"

#include "rFactorInfo.h"


//==============================================================================
class CApp : public CEvent {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;
		SDL_Surface *background;

    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

        	//void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

        	//void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

            void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

//==============================================================================

#endif
