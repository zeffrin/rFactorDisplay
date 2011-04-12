//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}
/*
//==============================================================================
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_LEFT: {
			Player.MoveLeft = true;
			break;
		}

		case SDLK_RIGHT: {
			Player.MoveRight = true;
			break;
		}

		case SDLK_SPACE: {
		    Player.Jump();
		    break;
		}

		default: {
		}
	}
}

//------------------------------------------------------------------------------
void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_LEFT: {
			break;
		}

		case SDLK_RIGHT: {
			Player.MoveRight = false;
			break;
		}

		default: {
		}
	}
}
*/
//------------------------------------------------------------------------------
void CApp::OnExit() {
	Running = false;
}

//==============================================================================
