//==============================================================================

#include "rFactorInfo.h"

//==============================================================================
void CApp::OnRender() {
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = WWIDTH;
	Rect.h = WHEIGHT;
	
	char msg[256];

	//SDL_FillRect(Surf_Display, &Rect, 0);

	CSurface::OnDraw(Surf_Display, background, 0, 0);

	//if(rFactorInfo::rFactor.GotData)
	//{

		// Session Stuff, Left Column

		Rect.x = 400;
		Rect.y = 13;
		sprintf(msg, "FPS: %d", CFPS::FPSControl.GetFPS());
		CFont::Font.Draw(msg, Surf_Display, Rect);
		
		Rect.x = 240;
		Rect.y = 36;
		sprintf(msg, "%s", rFactorInfo::rFactor.ScoreInfo.mPlayerName);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace - 1;
		sprintf(msg, "%s", rFactorInfo::rFactor.ScoreInfo.mTrackName);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace;
		sprintf(msg, "%s", rFactorInfo::rFactor.GamePhases[rFactorInfo::rFactor.ScoreInfo.mGamePhase]);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace - 1;
		sprintf(msg, "%3ld / %3ld", rFactorInfo::rFactor.TeleInfo.mLapNumber,
			rFactorInfo::rFactor.ScoreInfo.mMaxLaps);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace;
		sprintf(msg, "%5.2f / %5.2f", rFactorInfo::rFactor.ScoreInfo.mCurrentET,
									  rFactorInfo::rFactor.ScoreInfo.mEndET);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace - 2;
		sprintf(msg, "%3.0f", rFactorInfo::rFactor.ScoreInfo.mOnPathWetness);
		CFont::Font.Draw(msg, Surf_Display, Rect);


		// Session Stuff, Right Column

		Rect.x = 466;
		Rect.y = 35;
		sprintf(msg, "%3.0f", rFactorInfo::rFactor.ScoreInfo.mDarkCloud);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace - 1;
		sprintf(msg, "%3.0f", rFactorInfo::rFactor.ScoreInfo.mRaining);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace;
		sprintf(msg, "%.1f", rFactorInfo::rFactor.ScoreInfo.mAmbientTemp);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace - 1;
		sprintf(msg, "%.1f", rFactorInfo::rFactor.ScoreInfo.mTrackTemp);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace;
		// TODO: Wind speed

		Rect.y += CFont::Font.Linespace - 1;
		sprintf(msg, "%3.0f", rFactorInfo::rFactor.ScoreInfo.mOffPathWetness);
		CFont::Font.Draw(msg, Surf_Display, Rect);


		// Timing Info Left Column

		Rect.x = 240;
		Rect.y = 181;
		sprintf(msg, "%5.2f", rFactorInfo::rFactor.ScoreInfo.mCurrentET - 
							  rFactorInfo::rFactor.TeleInfo.mLapStartET);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		//Rect.y += CFont::Font.Linespace;
		//sprintf(msg, "%5.2f", rFactorInfo::rFactor.TeleInfo.

		// Engine Info Left Column
		Rect.x = 240;
		Rect.y = 290;
		sprintf(msg, "%.2f", rFactorInfo::rFactor.TeleInfo.mFuel);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		Rect.y += CFont::Font.Linespace;
		sprintf(msg, "%3.2f / %3.2f", rFactorInfo::rFactor.fuelcounter.lastfuel,
									  rFactorInfo::rFactor.fuelcounter.fuelavg);
		CFont::Font.Draw(msg, Surf_Display, Rect);

		// Engine Info Right Column

	//}
	SDL_Flip(Surf_Display);
}

//==============================================================================
