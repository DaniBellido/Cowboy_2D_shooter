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
#include  "crtdbg.h"

CMyGame *pGame;
CGameApp *pApp;

int main(int argc, char* argv[])
{
	#ifndef NDEBUG
		int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		flag |= _CRTDBG_LEAK_CHECK_DF;
		_CrtSetDbgFlag(flag); 
	#endif

//		_crtBreakAlloc = 569;

	// These objects are instantiated dynamically to easily track memory leaks.
	// In regular use, these object may be static.
	pApp = new CGameApp;
	pGame = new CMyGame;

	pApp->OpenWindow(800, 600, "My Game!");
//	pApp.OpenConsole();
	//pApp.OpenFullScreen(800, 600, 24);
	pApp->SetClearColor(CColor::LightGray());
	pApp->Run(pGame);
	delete pGame;
	delete pApp;
	return(0);
}
