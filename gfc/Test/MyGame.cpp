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
#include "MyGame.h"

CMyGame::CMyGame(void) : m_sprite(50, 50, "rocket.bmp", CColor::Blue(), 0)
{ 
}

CMyGame::~CMyGame(void)
{
	for (CSpriteList::iterator i = m_sprites.begin(); i != m_sprites.end(); i++)
		delete *i;
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	for each (CSprite *p in m_sprites)
	{
		p->Update(GetTime());
	}

	m_sprite.SetVelocity(m_sprite.GetVelocity() + CVector(0, -1));
	m_sprite.SetRotation(m_sprite.GetDirection());
	m_sprite.Update(GetTime());

	//static int i = 0;
	//if (i++ % 60 == 0)
	//	m_sprites.push_back(m_sprite.Clone());
}

void CMyGame::OnDraw(CGraphics* g)
{
	for (int i = 0; i < 800; i += 10) g->DrawVLine(CVector((float)i, (float)0), 600, CColor::DarkGray());
	for (int i = 0; i < 600; i += 10) g->DrawHLine(CVector((float)0, (float)i), 800, CColor::DarkGray());
	
	//g->SetScrollPos(GetMouseCoords() - CVectorI(400, 300));

	g->DrawRect(CRectangle(10, 10, 40, 20), CColor::Red());
	g->FillRect(CRectangle(60, 10, 40, 20), CColor::Red());
	g->DrawRect(CRectangle(110, 10, 100, 60), CColor::Red(), 20);
	g->FillRect(CRectangle(220, 10, 100, 60), CColor::Red(), 20);
	g->DrawOval(CRectangle(10, 40, 40, 20), CColor::Red());
	g->FillOval(CRectangle(60, 40, 40, 20), CColor::Red());
	g->DrawCircle(CVectorI(30, 80), 10, CColor::Red());
	g->FillCircle(CVectorI(80, 80), 10, CColor::Red());

	g->DrawPie(CVectorI(80, 160), 60, 315, 45, CColor::Red());
	g->FillPie(CVectorI(260, 160), 60, -45, 225, CColor::Yellow());

	g->DrawTriangle(CVectorI(10, 240), CVectorI(70, 260), CVectorI(50, 300), CColor::DarkBlue());
	g->FillTriangle(CVectorI(80, 240), CVectorI(140, 260), CVectorI(120, 300), CColor::DarkBlue());

	CVectorI ii1[] = { CVectorI(200, 240), CVectorI(180, 280), CVectorI(220, 320), CVectorI(260, 280), CVectorI(240, 240) };
	CVectorI ii2[] = { CVectorI(300, 240), CVectorI(280, 280), CVectorI(320, 320), CVectorI(360, 280), CVectorI(340, 240) };
	CVectorI ii3[] = { CVectorI(400, 240), CVectorI(380, 280), CVectorI(420, 320), CVectorI(460, 280), CVectorI(440, 240) };
	CVectorI ii4[] = { CVectorI(500, 240), CVectorI(480, 280), CVectorI(520, 320), CVectorI(560, 280), CVectorI(540, 340) };
	g->DrawPolyLine(ii1, 5, CColor::DarkGreen());
	g->DrawPolygon(ii2, 5, CColor::DarkGreen());
	g->FillPolygon(ii3, 5, CColor::DarkGreen());
	g->DrawBezierLine(ii4, 5, 10, CColor::DarkGreen());

	
	if (IsMouseFocus())
		*g << top << center << "mouse coords: " << GetMouseCoords().m_x << ", " << GetMouseCoords().m_y << endl;
	if (IsLButtonDown()) *g << "LEFT BUTTON PRESSED" << endl;

	for (CSpriteList::iterator i = m_sprites.begin(); i != m_sprites.end(); i++)
		(*i)->Draw(g);

	if (IsKeyDown(SDLK_UP))		{ *g << bottom << endl << centre << "Arrow UP is pressed"; }
	if (IsKeyDown(SDLK_DOWN))	{ *g << bottom << centre << "Arrow DOWN is pressed"; }
	if (IsKeyDown(SDLK_LEFT))	{ *g << bottom << left << "Arrow LEFT is pressed"; }
	if (IsKeyDown(SDLK_RIGHT))	{ *g << bottom << right << "Arrow RIGHT is pressed"; }
	if (!IsKeyDown(SDLK_UP) && !IsKeyDown(SDLK_DOWN) && !IsKeyDown(SDLK_LEFT) && !IsKeyDown(SDLK_RIGHT)) { *g << bottom << centre << "Use Arrows to change this text"; }

	if (IsMouseFocus())
		*g << top << center << "mouse coords: " << GetMouseCoords().m_x << ", " << GetMouseCoords().m_y << endl;
	if (IsLButtonDown()) *g << "LEFT BUTTON PRESSED" << endl;
	if (IsRButtonDown()) *g << "RIGHT BUTTON PRESSED" << endl;
	if (IsMButtonDown()) *g << "MIDDLE BUTTON PRESSED" << endl;

	m_sprite.Draw(g);

	*g << font(48) << color(CColor::Red()) << center << vcenter << "TEST!" << endl;

	*g << xy(12, 400) << font("andyb.ttf", 44) << color(CColor::DarkCyan()) << "CFont: andyb.ttf";
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}


// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	CSprite *pSprite;
	m_sprites.push_back(pSprite = new CSpriteRect(60, 540, 101, 101, CColor::Red(), CColor::Black(), GetTime()));
	m_sprites.push_back(pSprite = new CSpriteRect(60, 340, 101, 101, CColor::Red(), CColor::Black(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSpriteOval(260, 540, 101, 101, CColor::Yellow(), CColor::Black(), GetTime()));
	m_sprites.push_back(pSprite = new CSpriteOval(260, 340, 101, 101, CColor::Yellow(), CColor::Black(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSpriteText(510, 540, "arial.ttf", 24, "THIS IS A TEXT", CColor::Black(), GetTime()));
	m_sprites.push_back(pSprite = new CSpriteText(510, 340, "arial.ttf", 24, "THIS IS A TEXT", CColor::Black(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSprite(710, 540, "rocket.bmp", CColor::Blue(), GetTime()));
	m_sprites.push_back(pSprite = new CSprite(710, 340, "rocket.bmp", CColor::Blue(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSprite(235, 130, 250, 120, "rocket.bmp", CColor::Blue(), GetTime()));
	m_sprites.push_back(pSprite = new CSprite(735, 130, 250, 120, "rocket.bmp", CColor::Blue(), GetTime()));
	pSprite->SetOmega(30);
	m_sprites.push_back(pSprite = new CSpriteRect(461, 130, 2, 120, CColor::Blue(), GetTime()));
	//pSprite->SetPivotFromCenter(0, -50);
	pSprite->SetOmega(30);

	m_sprite.SetPosition(400, 300);
	m_sprite.SetDirection(-30);
	m_sprite.SetSpeed(100);
	m_sprite.SetRotation(m_sprite.GetDirection());

	StartGame();
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();

	if (sym == SDLK_RETURN)
		m_player.Play("shot.wav");

	if (sym == SDLK_ESCAPE)
	{
		for each (CSprite *p in m_sprites)
			delete p;
		m_sprites.clear();
	}
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
