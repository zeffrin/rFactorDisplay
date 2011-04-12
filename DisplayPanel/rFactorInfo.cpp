#include "rFactorInfo.h"

rFactorInfo rFactorInfo::rFactor;

const char * const rFactorInfo::GamePhases[] = { "Practice", "Recon", "Walk Through", "Formation", 
								"Countdown", "Green Flag", "Yellow Flag", "Session Stopped", 
								"Session Over" };

rFactorInfo::rFactorInfo()
{
	// Initialise structs, commented out for now, hoping updates will bring in all valid data

	//memset(this, 0, sizeof(TeleInfo))
	//memset(this, 0, sizeof(ScoreInfo))

	GotData = false;
	Connected = false;
	//Initialise();




}

bool rFactorInfo::Initialise() 
{
	szMemName = TEXT("Local\\rFactorDisplay");
	szEventName = TEXT("Local\\rFactorDisplayPlugin");
	szMutexName = TEXT("Local\\rFactorDisplayMutex");

	// Set up the shared memory space for the plugin to write into
	
	hMapHandle = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security 
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD) 
        sizeof(TelemInfoV2) + sizeof(ScoringInfoV2),// maximum object size (low-order DWORD)  
        szMemName);                 // name of mapping object
 
	if (hMapHandle == NULL) 
	{ 
		WriteToLogFile("w", "Couldn't create file mapping object");
		//_tprintf(TEXT("Could not create file mapping object (%d).\n"), 
      //       GetLastError());
		return false;
	}
	
	TelemBuf = (TelemInfoV2 *) MapViewOfFile(hMapHandle,   // handle to map object
                        FILE_MAP_ALL_ACCESS, // read/write permission
                        0,                   
                        0,                   
                        sizeof(TelemInfoV2) + sizeof(ScoringInfoV2));           
 
	if (TelemBuf == NULL) 
	{ 
      //_tprintf(TEXT("Could not map view of file (%d).\n"), 
      //       GetLastError()); 
		WriteToLogFile("w", "Could not map view of file");
	    CloseHandle(hMapHandle);
	    hMapHandle = NULL;
		return false;
	}

	hEventHandle = CreateEvent(NULL, FALSE, FALSE, szEventName);
	if (hEventHandle == NULL)
	{
		//WriteToLogFile("w", "-Unable to open Event-");
		WriteToLogFile("w", "Unable to Create Event");
	    CloseHandle(hMapHandle);
		UnmapViewOfFile(TelemBuf);
		TelemBuf = NULL;
	    hMapHandle = NULL;
		return false;
	}


	hMutex = CreateMutex(NULL, FALSE, szMutexName);
	if (hMutex == NULL)
	{
		WriteToLogFile("w", "Unable to create Mutex");
	    CloseHandle(hMapHandle);
		CloseHandle(hEventHandle);
		UnmapViewOfFile(TelemBuf);
		hEventHandle = NULL;
		TelemBuf = NULL;
	    hMapHandle = NULL;
		return false;
	}

	hArr[0] = hEventHandle;
	hArr[1] = hMutex;

	ScoringBuf = (ScoringInfoV2 *) (TelemBuf + 1);

	Connected = true;
	fuelcounter.endlapfuel = 0;
	fuelcounter.fuelavg = 0;
	fuelcounter.fuelavgtotal = 0;
	fuelcounter.lapnumber = 0;
	fuelcounter.laps = 0;
	fuelcounter.lastfuel = 0;

	WriteToLogFile("w", "Init all ok");

	// Debug stuff
#ifdef DEBUG
	
	strcpy(rFactor.ScoreInfo.mPlayerName, "Zeffrin");
	strcpy(rFactor.ScoreInfo.mTrackName, "Test Track");
	rFactor.ScoreInfo.mAmbientTemp = 30.1f;
	rFactor.ScoreInfo.mDarkCloud = .9f;
	rFactor.ScoreInfo.mGamePhase = 2;
	rFactor.ScoreInfo.mMaxLaps = 100;
	rFactor.ScoreInfo.mRaining = 0.2f;
	rFactor.ScoreInfo.mOffPathWetness = 0.8f;
	rFactor.ScoreInfo.mOnPathWetness = 0.5f;

#endif

	return true;
}

rFactorInfo::~rFactorInfo()
{
	if(Connected)
	{
	    CloseHandle(hMapHandle);
		CloseHandle(hEventHandle);
		CloseHandle(hMutex);
		UnmapViewOfFile(TelemBuf);
		hEventHandle = NULL;
		TelemBuf = NULL;
		ScoringBuf = NULL;
	    hMapHandle = NULL;
		hMutex = NULL;
		GotData = false;
		Connected = false;
	}

}

void rFactorInfo::OnLoop()
{
	int i;

	if(Connected)
	{
		i = WaitForMultipleObjectsEx(2, hArr, TRUE, 0, FALSE);
		if (i >= WAIT_OBJECT_0 && i <= WAIT_OBJECT_0 + 1)
		{
			
			//memcpy(&TeleInfo, TelemBuf, sizeof(TelemInfoV2));
			//memcpy(&ScoreInfo, test, sizeof(ScoringInfoV2));
			TeleInfo = *TelemBuf;
			ScoreInfo = *ScoringBuf;
			ReleaseMutex(hMutex);
			ResetEvent(hEventHandle);
			GotData = true;
			
			//invert tyre wear and turn to percentage
			TeleInfo.mWheel[0].mWear = (float) (abs(TeleInfo.mWheel[0].mWear -1.0f)) * 100.0f;
			TeleInfo.mWheel[1].mWear = (float) (abs(TeleInfo.mWheel[1].mWear -1.0f)) * 100.0f;
			TeleInfo.mWheel[2].mWear = (float) (abs(TeleInfo.mWheel[2].mWear -1.0f)) * 100.0f;
			TeleInfo.mWheel[3].mWear = (float) (abs(TeleInfo.mWheel[3].mWear -1.0f)) * 100.0f;

			//Invert Wetness and turn to percentage
			//ScoreInfo.mOnPathWetness = (float) (abs(ScoreInfo.mOnPathWetness -1.0f)) * 100.0f;
			//ScoreInfo.mOffPathWetness = (float) (abs(ScoreInfo.mOffPathWetness -1.0f)) * 100.0f;

			////Invert Cloud Cover and turn to percentage
			//ScoreInfo.mDarkCloud = (float) (abs(ScoreInfo.mDarkCloud -1.0f)) * 100.0f;
			//ScoreInfo.mRaining = (float) (abs(ScoreInfo.mRaining -1.0f)) * 100.0f;

			ScoreInfo.mOnPathWetness *= 100.0f;
			ScoreInfo.mOffPathWetness *= 100.f;
			ScoreInfo.mDarkCloud *= 100.0f;
			ScoreInfo.mRaining *= 100.0f;


			// Neaten end time
			if (ScoreInfo.mEndET == 0xFFFFFFFF)
			{
				ScoreInfo.mEndET = 0;
			}

			//do fuel calcs
			if(TeleInfo.mLapNumber < fuelcounter.lapnumber)
			{
				fuelcounter.fuelavgtotal = 0;
				fuelcounter.lapnumber = TeleInfo.mLapNumber;
				fuelcounter.lastfuel = 0;
				fuelcounter.endlapfuel = 0;
				fuelcounter.laps = 0;
				fuelcounter.fuelavg = 0;
			}
			else if(TeleInfo.mLapNumber > fuelcounter.lapnumber)
			{
				if(fuelcounter.endlapfuel)
				{
					fuelcounter.lastfuel = fuelcounter.endlapfuel - TeleInfo.mFuel;
					fuelcounter.fuelavgtotal += fuelcounter.lastfuel;
					fuelcounter.fuelavg = (float)fuelcounter.fuelavgtotal / fuelcounter.laps;
				}

				fuelcounter.laps++;
				fuelcounter.lapnumber = TeleInfo.mLapNumber;
				fuelcounter.endlapfuel = TeleInfo.mFuel;


			}
		}
	}
}


void rFactorInfo::WriteToLogFile( const char * const openStr, const char * const msg )
{
  FILE *fo;

  fo = fopen( "DisplayPanelLog.txt", openStr );
  if( fo != NULL )
  {
    fprintf( fo, "%s\n", msg );
    fclose( fo );
  }
}