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

#include "Vector.h"
class CGameApp;
class CGraphics;

class EXT_DECL CGame
{
public:
	CGame();
	virtual ~CGame();

	// Game Modes
	enum GAMEMODE { MODE_MENU, MODE_GAME, MODE_GAMEOVER, MODE_NONE };

private:
	// Attributes:
	///////////////////////////////////////////////

	CVectorI m_dim;						// playfield size

	CGameApp *m_pApp;					// the Game Application object

	///////////////////////////////////////////////
	// Game State Flags
	volatile bool m_flagRunning;		// used to stop the animation thread
	volatile bool m_flagPaused;			// used to pause the animation thread
	volatile GAMEMODE m_flagMode;		// current game mode - either MODE_MENU, MODE_GAME or MODE_GAMEOVER
	volatile GAMEMODE m_flagModeReq;	// requested game mode

	///////////////////////////////////////////////
	// Game Level
	volatile Sint16 m_level;			// current game level
	volatile Sint16 m_levelReq;			// requested game level

	///////////////////////////////////////////////
	// Key States
	Uint8 *m_kbarray;					// pointer to keyboard states array
	bool m_bMouseFocus;

	///////////////////////////////////////////////
	// Game Timing
	volatile Uint32 m_time;				// set automatically by the framework (CGameApp)
	volatile Uint32 m_timePrev;			// time of the previous update (used to calculate DeltaTime)
	volatile Uint32 m_timeGameOver;		// set automatically by the framework (CGameApp)

public:
	// Accessor Functions
	
	///////////////////////////////////////////////
	// The application object

	CGameApp *GetApp()					{ return m_pApp; }

	///////////////////////////////////////////////
	// Game Geometry: simple but usable implementation

	CVectorI GetSize()					{ return m_dim; }
	Sint16 GetWidth()					{ return m_dim.X(); }
	Sint16 GetHeight()					{ return m_dim.Y(); }

	///////////////////////////////////////////////
	// Time Utilities
	
	Uint32 GetTime()					{ return m_time; }
	Uint32 GetDeltaTime()				{ return m_time - m_timePrev; }
	Uint32 GetTimeGameOver()			{ return m_timeGameOver; }

	///////////////////////////////////////////////
	// Keyboard and Mouse State Functions
	
	// Checks if a particular key is pressed
	bool IsKeyDown(SDLKey sym);

	CVectorI GetMouseCoords();
	void GetMouseCoords(Uint16 &x, Uint16 &y);
	bool IsMouseFocus();
	bool IsLButtonDown();
	bool IsRButtonDown();
	bool IsMButtonDown();

	void HideMouse();
	void ShowMouse();


	///////////////////////////////////////////////
	// Game State

	bool IsRunning()					{ return m_flagRunning; }
	bool IsPaused()						{ return m_flagPaused; }
	bool IsMenuMode()					{ return m_flagMode == MODE_MENU; }
	bool IsGameMode()					{ return m_flagMode == MODE_GAME; }
	bool IsGameOverMode()				{ return m_flagMode == MODE_GAMEOVER; }
	bool IsGameOver()					{ return IsGameOverMode(); }
	
	GAMEMODE GetMode()					{ return m_flagMode; }
	GAMEMODE GetGameMode()				{ return m_flagMode; }
	void ChangeMode(GAMEMODE mode)		{ m_flagModeReq = mode; }	// will only act from the next animation loop iteration!
	bool IsModeChanging()				{ return m_flagModeReq != MODE_NONE; }

	void StartGame()					{ ChangeMode(MODE_GAME); }
	void GameOver() 					{ ChangeMode(MODE_GAMEOVER); }
	void NewGame()						{ ChangeMode(MODE_MENU); }
	void StopGame()						{ m_flagRunning = false; }
	void StopApp()						{ m_flagRunning = false; }
	void PauseGame()					{ m_flagPaused = !m_flagPaused; }
	void PauseGame(bool b)				{ m_flagPaused = b; }

	///////////////////////////////////////////////
	// Game Level

	Sint16 GetLevel()					{ return m_level; }
	void SetLevel(Sint16 level)			{ m_levelReq = level; }
	void NewLevel()						{ SetLevel(GetLevel() + 1); }

	///////////////////////////////////////////////
	// Force Game Draw

	void ForceDraw();

	///////////////////////////////////////////////
	// Life Cycle

	virtual void OnInitialize()			{ }
	virtual void OnDisplayMenu()		{ }
	virtual void OnStartGame()			{ }
	virtual void OnStartLevel(Sint16 nLevel)	{ }
	virtual void OnGameOver()			{ }
	virtual void OnUpdate()				{ }
	virtual void OnDraw(CGraphics* g)	{ }
	virtual void OnTerminate()			{ }


	///////////////////////////////////////////////
	// Game State Handlers
	void HandleGameState();

	///////////////////////////////////////////////
	// Event Dispatcher
	void DispatchEvents(SDL_Event* pEvent);

	///////////////////////////////////////////////
	// Event Handlers

	// Generic Event
	virtual bool OnEvent(SDL_Event* pEvent);

	// Keyboard events
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse events
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);

	// Joystick events
	virtual void OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value);
	virtual void OnJoyButtonDown(Uint8 which,Uint8 button);
	virtual void OnJoyButtonUp(Uint8 which,Uint8 button);
	virtual void OnJoyHat(Uint8 which,Uint8 hat,Uint8 value);
	virtual void OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel);

	// Active Events (keyboard)
	virtual void OnInputFocus();
	virtual void OnInputBlur();

	// Active Events (mouse)
	virtual void OnMouseFocus();
	virtual void OnMouseBlur();

	// Active Events (application)
	virtual void OnMinimize();
	virtual void OnRestore();

	// Video Event
	virtual void OnResize(int w,int h);
	virtual void OnExpose();

	// User Event
	virtual void OnUserEvent(Uint8 type,int code,void* data1,void* data2);

//////////////////////////////////////////////////////////////////
// These functions are provided strictly for CGameApp internal use
private:
	void SetSize(Sint16 x, Sint16 y)	{ m_dim = CVectorI(x, y); }
	void SetApp(CGameApp *p)			{ m_pApp = p; }
	void ResetTime(long t = 0)			{ m_time = m_timePrev = t; }
	void SetTime(long t)				{ m_time = t; }
	void CatchDeltaTime()				{ m_timePrev = m_time; }
	void SetTimeGameOver(long t)		{ m_timeGameOver = t; }
	friend class CGameApp;
};
