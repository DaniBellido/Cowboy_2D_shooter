/****************************************************************************
GFC - Games Fundamental Classes version 2.60
Copyright (C) 2009-2018 Jarek Francik, Kingston University London

This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License:
http://creativecommons.org/licenses/by-sa/4.0/

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Created by Jarek Francik
jarek@kingston.ac.uk
****************************************************************************/
#pragma once

#include "Color.h"
#include "Vector.h"

class CGame;
class CGraphics;

class EXT_DECL CGameApp
{
	CGame *m_pGame;				// The Game
	CGraphics* m_pGraphics;		// The main screen graphics
	CColor m_colorClear;		// Background Colour

	Uint16 m_FPS;				// Frames per Second rate

	Uint32 m_nTimeStarted;		// System Time when the clock was started/resumed
	Uint32 m_nTimePaused;		// Game Time when clock was suspended (or zero)
	bool m_bRunning;			// set if clock is running (not suspended)

public:
	//////////////////////////////////////
	// Constructor & Destructor

	CGameApp(CGame *pGame = NULL);
	virtual ~CGameApp(void);

	//////////////////////////////////////
	// Attribute Getters and Setters

	// The Game	
	CGame *GetGame()					{ return m_pGame; }
	void SetGame(CGame *pGame);

	// The Graphics
	CGraphics *GetGraphics()			{ return m_pGraphics; }

	// Size of the Canvas
	CVectorI GetSize();
	int GetWidth();
	int GetHeight();

	// Other
	CColor GetClearColor()				{ return m_colorClear; }
	void SetClearColor(CColor c)		{ m_colorClear = c; }
	void SetBackgroundColor(CColor c)	{ m_colorClear = c; }
	Uint16 GetFPS()						{ return m_FPS; }
	void SetFPS(Uint16 fps)				{ m_FPS = fps; }
	
	//////////////////////////////////////
	// The Clock

	Uint32 GetSystemTime();		// System Time may be not relevant to the game

	Uint32 GetGameTime();		// Game Time, starts from 0 and suspends when paused

	void ResetClock();			// restarts the clock from zero
	void SuspendClock();		// pauses the clock, the time will not progress
	void ResumeClock();			// resumes the clock after a pause
	bool IsClockRunning();		// returns true when the clock is running (not suspended)

	//////////////////////////////////////
	// Application Operations

	// Open Window/Full Screen/Concole
	bool OpenWindow(int nWidth, int nHeight, std::string strTitle, unsigned SDLflags = 0);
	bool OpenFullScreen(int nWidth, int nHeight, int nBpp);
	bool OpenConsole();

	// SDL and Platform-dependent functions (Windows version)
	void DebugMemoryLeaks(long nBreakAlloc = -1);
	unsigned _GetSDLVersion();
	unsigned _GetWindowHandle();

	// Main Loop
	bool Run(CGame *pGame = NULL);

	//////////////////////////////////////
	// Ovverridables (rarely used)
	void OnInitialize()							{ }
	bool OnDispatchEvent(SDL_Event *anEvent)	{ return false; }
	bool OnUpdate()								{ return false; }
	void OnTerminate()							{ }
};
