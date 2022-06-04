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
#include "StdAfx.h"
#include "..\GFC\include\GFC.h"
#include "..\GFC\include\SpriteOval.h"

// Constructors with colour and outline colour
CSpriteOval::CSpriteOval(CVector v, float w, float h, CColor color, CColor colorOutline, long time)
	: CSprite(v, w, h, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteOval::CSpriteOval(float x, float y, float w, float h, CColor color, CColor colorOutline, long time)
	: CSprite(x, y, w, h, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteOval::CSpriteOval(CVector v, float radius, CColor color, CColor colorOutline, long time)
	: CSprite(v, radius+radius, radius+radius, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteOval::CSpriteOval(float x, float y, float radius, CColor color, CColor colorOutline, long time)
	: CSprite(x, y, radius+radius, radius+radius, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }
CSpriteOval::CSpriteOval(CRectangle r, CColor color, CColor colorOutline, long time)
	: CSprite(r, time), m_color(color), m_colorOutline(colorOutline)
	{ SetColorKey(CColor::AnyBut(color, colorOutline)); }

// Constructors with colour and no outline colour
CSpriteOval::CSpriteOval(CVector v, float w, float h, CColor color, long time)
	: CSprite(v, w, h, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteOval::CSpriteOval(float x, float y, float w, float h, CColor color, long time)
	: CSprite(x, y, w, h, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteOval::CSpriteOval(CVector v, float radius, CColor color, long time)
	: CSprite(v, radius+radius, radius+radius, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteOval::CSpriteOval(float x, float y, float radius, CColor color, long time)
	: CSprite(x, y, radius+radius, radius+radius, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }
CSpriteOval::CSpriteOval(CRectangle r, CColor color, long time)
	: CSprite(r, time), m_color(color), m_colorOutline(color)
	{ SetColorKey(CColor::AnyBut(color)); }

CSpriteOval::~CSpriteOval()
{
}

void CSpriteOval::OnDraw(CGraphics *g)
{
	if (IsValid()) return;
	CRectangle rect;
	GetClientRect(rect);
	g->FillRect(rect, GetColorKey());
	rect.Grow(0, -1, 0, -1);
	g->FillOval(rect, m_color);
	g->DrawOval(rect, m_colorOutline);
}
