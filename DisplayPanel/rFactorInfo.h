
#ifndef _RFACTOR_INFO_H
#define _RFACTOR_INFO_H

#define DEBUG 1

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Define.h"

#include "CApp.h"

class rFactorInfo
{
	public:

		static rFactorInfo rFactor;

		rFactorInfo();
		~rFactorInfo();
		void OnLoop();
		TelemInfoV2 TeleInfo;
		ScoringInfoV2 ScoreInfo;

		bool GotData;
		
		bool Initialise();

		struct fuelstruct {
			long lapnumber;
			float lastfuel;
			float endlapfuel;
			double fuelavgtotal;
			float fuelavg;
			long laps;
		} fuelcounter;

		static const char * const GamePhases[];

	private:
		
		bool Connected;
		const TCHAR *szMemName;
		const TCHAR *szEventName;
		const TCHAR *szMutexName;
		HANDLE hMapHandle;
		HANDLE hEventHandle;
		HANDLE hMutex;
		HANDLE hArr[2];
		ScoringInfoV2 *ScoringBuf;
		TelemInfoV2 *TelemBuf;

		void WriteToLogFile( const char * const openStr, const char * const msg );		

		

};



  // Game phases:
  // 0 Before session has begun
  // 1 Reconnaissance laps (race only)
  // 2 Grid walk-through (race only)
  // 3 Formation lap (race only)
  // 4 Starting-light countdown has begun (race only)
  // 5 Green flag
  // 6 Full course yellow / safety car
  // 7 Session stopped
  // 8 Session over

#endif //_RFACTOR_INFO_H