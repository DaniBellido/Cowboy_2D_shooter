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
#include "stdafx.h"
#include "..\GFC\include\Game.h"
#include "..\GFC\include\GameApp.h"
#include "..\GFC\include\Graphics.h"


CGame::CGame() : m_dim(0, 0)
{
	m_bMouseFocus = false;
	m_time = m_timePrev = m_timeGameOver = 0;
	m_flagRunning = true;
	m_flagPaused = false;
	m_flagModeReq = MODE_MENU;
	m_flagMode = MODE_MENU;
	m_level = 0;
	m_levelReq = 0;
}

CGame::~CGame(void)
{
}

///////////////////////////////////////////////
// Keyboard and Mouse State Functions

bool CGame::IsKeyDown(SDLKey sym)
{
	return (m_kbarray[sym] == 1); 
}

CVectorI CGame::GetMouseCoords()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	y = GetHeight() - y;
	return CVectorI(x, y);
}

void CGame::GetMouseCoords(Uint16 &x, Uint16 &y)
{
	int _x, _y;
	SDL_GetMouseState(&_x, &_y);
	x = _x;
	y = GetHeight() - _y;
}

bool CGame::IsMouseFocus()
{ 
	return m_bMouseFocus; 
}

bool CGame::IsLButtonDown()
{
	return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK) != 0;
}

bool CGame::IsRButtonDown()
{
	return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_RMASK) != 0;
}

bool CGame::IsMButtonDown()
{
	return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_MMASK) != 0;
}

void CGame::HideMouse()
{
	SDL_ShowCursor(0);
}
void CGame::ShowMouse()
{
	SDL_ShowCursor(1);
}

///////////////////////////////////////////////
// Force Game Draw

void CGame::ForceDraw()
{
	auto pApp = GetApp();
	auto pGraphics = pApp->GetGraphics();
	pGraphics->Clear(pApp->GetClearColor());
	OnDraw(pGraphics);
	pGraphics->Flush();
	pGraphics->Flip();
}


///////////////////////////////////////////////
// Game State & Events

void CGame::HandleGameState()
{
	if (m_flagModeReq != MODE_NONE)
	{
		m_flagMode = m_flagModeReq; 
		m_flagModeReq = MODE_NONE;
		switch (GetMode())
		{
		case CGame::MODE_MENU:
			m_pApp->ResetClock();
			this->ResetTime();
			m_level = m_levelReq = 0;
			OnDisplayMenu();
			OnStartLevel(m_level);
			break;
		case CGame::MODE_GAME:
			m_pApp->ResetClock();
			this->ResetTime();
			m_level = m_levelReq = 1;
			OnStartGame();
			OnStartLevel(m_level);
			break;
		case CGame::MODE_GAMEOVER:
			SetTimeGameOver(GetTime());
			m_pApp->ResetClock();
			this->ResetTime();
			m_levelReq = m_level;
			OnGameOver();
			break;
		}
	}
	if (m_level != m_levelReq)
	{
		m_level = m_levelReq; 
		OnStartLevel(m_level);
	}
}

void CGame::DispatchEvents(SDL_Event* pEvent)
{
	//filter event
	if (OnEvent(pEvent)) return;

	m_kbarray = SDL_GetKeyState(NULL);   // get keyboard states 


	//dispatch event
	switch(pEvent->type)
	{
		case SDL_ACTIVEEVENT:		//activation event
			//what was gained or lost?
			switch(pEvent->active.state)
			{
				case SDL_APPMOUSEFOCUS:		//mouse focus
					//gain or loss?
					m_bMouseFocus = pEvent->active.gain != 0;
					if (m_bMouseFocus)
						OnMouseFocus();
					else
						OnMouseBlur();
					break;
				case SDL_APPINPUTFOCUS:		//input focus
					if(pEvent->active.gain)
						OnInputFocus();
					else
						OnInputBlur();
					break;
				case SDL_APPACTIVE:			//application activation
					if(pEvent->active.gain)
						OnRestore();
					else
						OnMinimize();
					break;
			}
			break;
		case SDL_KEYDOWN:			//key press
			OnKeyDown(pEvent->key.keysym.sym,pEvent->key.keysym.mod,pEvent->key.keysym.unicode);
			break;
		case SDL_KEYUP:				//key release
			OnKeyUp(pEvent->key.keysym.sym,pEvent->key.keysym.mod,pEvent->key.keysym.unicode);
			break;
		case SDL_MOUSEMOTION:		//mouse motion
			OnMouseMove(pEvent->motion.x,GetHeight() - pEvent->motion.y,pEvent->motion.xrel,pEvent->motion.yrel,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
			break;
		case SDL_MOUSEBUTTONDOWN:	//mouse button press
			//which button?
			switch(pEvent->button.button)
			{
				case SDL_BUTTON_LEFT:	OnLButtonDown(pEvent->button.x,GetHeight() - pEvent->button.y); break;
				case SDL_BUTTON_RIGHT:	OnRButtonDown(pEvent->button.x,GetHeight() - pEvent->button.y); break;
				case SDL_BUTTON_MIDDLE:	OnMButtonDown(pEvent->button.x,GetHeight() - pEvent->button.y); break;
			}
			break;
		case SDL_MOUSEBUTTONUP:		//mouse button release
			//which button?
			switch(pEvent->button.button)
			{
				case SDL_BUTTON_LEFT:	OnLButtonUp(pEvent->button.x,GetHeight() - pEvent->button.y); break;
				case SDL_BUTTON_RIGHT:	OnRButtonUp(pEvent->button.x,GetHeight() - pEvent->button.y); break;
				case SDL_BUTTON_MIDDLE:	OnMButtonUp(pEvent->button.x,GetHeight() - pEvent->button.y); break;
			}
			break;
		case SDL_JOYAXISMOTION:		//joystick axis motion
			OnJoyAxis(pEvent->jaxis.which,pEvent->jaxis.axis,pEvent->jaxis.value);
			break;
		case SDL_JOYBALLMOTION:		//joystick ball motion
			OnJoyBall(pEvent->jball.which,pEvent->jball.ball,pEvent->jball.xrel,pEvent->jball.yrel);
			break;
		case SDL_JOYHATMOTION:		//joystick hat motion
			OnJoyHat(pEvent->jhat.which,pEvent->jhat.hat,pEvent->jhat.value);
			break;
		case SDL_JOYBUTTONDOWN:		//joystick button press
			OnJoyButtonDown(pEvent->jbutton.which,pEvent->jbutton.button);
			break;
		case SDL_JOYBUTTONUP:		//joystick button release
			OnJoyButtonUp(pEvent->jbutton.which,pEvent->jbutton.button);
			break;
		case SDL_QUIT:				//quit event
			//ignore it!
			break;
		case SDL_SYSWMEVENT:		//window manager event
			//ignore as well...
			break;
		case SDL_VIDEORESIZE:		//resize video
			OnResize(pEvent->resize.w,pEvent->resize.h);
			break;
		case SDL_VIDEOEXPOSE:		//video expose
			OnExpose();
			break;
		default:					//user defined
			OnUserEvent(pEvent->user.type,pEvent->user.code,pEvent->user.data1,pEvent->user.data2);
			break;
	}
}

///////////////////////////////////////////////////////
// Generic Implementation of Events Handlers

// Generic Event
bool CGame::OnEvent(SDL_Event* pEvent)									{ return false; }
// Keyboard events
void CGame::OnKeyDown(SDLKey sym,SDLMod mod,Uint16 unicode)				{ }
void CGame::OnKeyUp(SDLKey sym,SDLMod mod,Uint16 unicode)				{ }
// Mouse events
void CGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)	{ }
void CGame::OnLButtonDown(Uint16 x,Uint16 y)							{ }
void CGame::OnLButtonUp(Uint16 x,Uint16 y)								{ }
void CGame::OnRButtonDown(Uint16 x,Uint16 y)							{ }
void CGame::OnRButtonUp(Uint16 x,Uint16 y)								{ }
void CGame::OnMButtonDown(Uint16 x,Uint16 y)							{ }
void CGame::OnMButtonUp(Uint16 x,Uint16 y)								{ }
// Joystick events
void CGame::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value)				{ }
void CGame::OnJoyButtonDown(Uint8 which,Uint8 button)					{ }
void CGame::OnJoyButtonUp(Uint8 which,Uint8 button)						{ }
void CGame::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value)					{ }
void CGame::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel)	{ }
// Active Events (keyboard)
void CGame::OnInputFocus()												{ }
void CGame::OnInputBlur()												{ }
// Active Events (mouse)
void CGame::OnMouseFocus()												{ }
void CGame::OnMouseBlur()												{ }
// Active Events (application)
void CGame::OnMinimize()												{ PauseGame(true); }
void CGame::OnRestore()													{ PauseGame(false); }
// Video Event
void CGame::OnResize(int w,int h)										{ }
void CGame::OnExpose()													{ }
//User Event
void CGame::OnUserEvent(Uint8 type,int code,void* data1,void* data2)	{ }

