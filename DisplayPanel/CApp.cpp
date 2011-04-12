//==============================================================================
#include "CApp.h"

//==============================================================================
CApp::CApp() {
    Surf_Display = NULL;

    Running = true;
}

//------------------------------------------------------------------------------
int CApp::OnExecute() {
    if(OnInit() == false) {
		return -1;
    }
	
	SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();

		SDL_Delay(100);
    }

    OnCleanup();

    return 0;
}

//==============================================================================
int main(int argc, char* argv[]) {
	//putenv("SDL_VIDEO_WINDOW_POS=0,0");
	putenv("SDL_VIDEO_CENTERED=1");
	
	CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
