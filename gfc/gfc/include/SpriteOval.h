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

class EXT_DECL CSpriteOval : public CSprite
{
	CColor m_color;
	CColor m_colorOutline;

public:
	CSpriteOval(CVector v, float w, float h, CColor color, long time);
	CSpriteOval(float x, float y, float w, float h, CColor color, long time);
	CSpriteOval(CVector v, float radius, CColor color, long time);
	CSpriteOval(float x, float y, float radius, CColor color, long time);
	CSpriteOval(CRectangle r, CColor color, long time);

	CSpriteOval(CVector v, float w, float h, CColor color, CColor colorOutline, long time);
	CSpriteOval(float x, float y, float w, float h, CColor color, CColor colorOutline, long time);
	CSpriteOval(CVector v, float radius, CColor color, CColor colorOutline, long time);
	CSpriteOval(float x, float y, float radius, CColor color, CColor colorOutline, long time);
	CSpriteOval(CRectangle r, CColor color, CColor colorOutline, long time);

	~CSpriteOval();

protected:
	virtual void OnDraw(CGraphics *g);
};
