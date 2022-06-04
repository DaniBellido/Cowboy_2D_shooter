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

// CFont - a simple tool for alternative text output
// Compatible with GTEC2D library:
// Construct providing a pointer to a CGraphics object
// We strongly recommend using the CGraphics object and its << operator rather than this interface class

#ifndef __FONT_H__
#define __FONT_H__

#include <string>

#include "Graphics.h"

class EXT_DECL CFont
{
public:
	CFont(CGraphics *pG) : m_pG(pG)						{ LoadDefault(); }

private:
	CGraphics *m_pG;
	
	std::string m_fontFace;
	int m_nPtSize;
	CColor m_color;



	////////
	//// GTEC like interface
public:
	bool LoadDefault()										{ return Load("arial.ttf"); }
	bool Load(std::string filename)							{ m_fontFace = filename; m_nPtSize = 18; m_color = CColor::Black(); return m_pG->DrawText(0, 0, m_fontFace, m_nPtSize, m_color, "") >= 0;  }

	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 100)	{ m_color = CColor(r, g, b, a); }
	void SetColor(const CColor& color)						{ m_color = (CColor)color; }

	void SetSize(int size)									{ m_nPtSize = size; }

	int DrawText(int x, int y, std::string Text)			{ return m_pG->DrawText(x, y, m_fontFace, m_nPtSize, m_color, Text); }
	int DrawNumber(int x, int y, int number)				{ char Text[128]; _itoa_s(number, Text, 10); return m_pG->DrawText(x, y, m_fontFace, m_nPtSize, m_color, Text); }

	int DrawText(int x, int y, std::string Text, const CColor& color, int size)		{ return m_pG->DrawText(x, y, m_fontFace, size, color, Text); }
	int DrawNumber(int x, int y, int number, const CColor& color, int size)			{ char Text[128]; _itoa_s(number, Text, 10); return m_pG->DrawText(x, y, m_fontFace, size, color, Text); }

	int DrawChar(int x, int y, char c)						{ return m_pG->DrawText(x, y, m_fontFace, m_nPtSize, m_color, std::string(1, c)); }
};

#endif
