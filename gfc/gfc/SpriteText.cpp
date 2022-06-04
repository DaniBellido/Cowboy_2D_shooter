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
#include "..\GFC\include\GFC.h"
#include "..\GFC\include\SpriteText.h"

CSpriteText::CSpriteText(CVector pt, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time)
	: CSprite(pt, 0, 0, time), m_align(0), m_valign(0), m_strFont(strFont), m_nPtSize(nPtSize), m_text(text), m_color(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteText::CSpriteText(CVector pt, Sint16 align, Sint16 valign, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time)
	: CSprite(pt, 0, 0, time), m_align(align), m_valign(valign), m_strFont(strFont), m_nPtSize(nPtSize), m_text(text), m_color(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteText::CSpriteText(float x, float y, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time)
	: CSprite(x, y, 0, 0, time), m_align(0), m_valign(0), m_strFont(strFont), m_nPtSize(nPtSize), m_text(text), m_color(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteText::CSpriteText(float x, float y, Sint16 align, Sint16 valign, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time)
	: CSprite(x, y, 0, 0, time), m_align(align), m_valign(valign), m_strFont(strFont), m_nPtSize(nPtSize), m_text(text), m_color(color)
	{ SetColorKey(CColor::AnyBut(color)); }

CSpriteText::~CSpriteText()
{
}

void CSpriteText::OnPrepareGraphics(CGraphics *pG)
{
	if (m_pGraphics) return;
	if (!pG) return;
		
	std::string fface = pG->GetFontName();
	int fsize = pG->GetFontSize();
	CColor tclr = pG->GetTextColor();

	*pG << font(m_strFont, m_nPtSize);
	*pG << color(m_color);
	m_pGraphics = pG->GetTextGraphics(m_text);
	SetSize((float)m_pGraphics->GetWidth(), (float)m_pGraphics->GetHeight());
	*pG << font(fface, fsize);
	*pG << color(tclr);
}

void CSpriteText::OnDraw(CGraphics*)
{
	// do nothing - the bitmap is already loaded in OnPrepareGraphics
}