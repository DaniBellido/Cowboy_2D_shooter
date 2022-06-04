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
#include "..\GFC\include\SpriteRect.h"

// Constructors with colour and outline colour
CSpriteRect::CSpriteRect(CVector v, float w, float h, CColor color, CColor colorOutline, long time)
	: CSprite(v, w, h, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteRect::CSpriteRect(float x, float y, float w, float h, CColor color, CColor colorOutline, long time)
	: CSprite(x, y, w, h, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteRect::CSpriteRect(CRectangle r, CColor color, CColor colorOutline, long time)
	: CSprite(r, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }

// Constructors with colour and no outline colour
CSpriteRect::CSpriteRect(CVector v, float w, float h, CColor color, long time)
	: CSprite(v, w, h, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteRect::CSpriteRect(float x, float y, float w, float h, CColor color, long time)
	: CSprite(x, y, w, h, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteRect::CSpriteRect(CRectangle r, CColor color, long time)
	: CSprite(r, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }


CSpriteRect::~CSpriteRect()
{
}

void CSpriteRect::OnDraw(CGraphics *g)
{
	if (IsValid()) return;
	CRectangle rect;
	GetClientRect(rect);
	g->FillRect(rect, m_color);
	rect.Grow(0, -1, 0, -1);
	g->DrawRect(rect, m_colorOutline);
}