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

class EXT_DECL CSpriteText : public CSprite
{
	Sint16 m_align, m_valign;
	std::string m_strFont;
	Sint16 m_nPtSize;
	std::string m_text;
	CColor m_color;

public:
	CSpriteText(CVector pt, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time);
	CSpriteText(CVector pt, Sint16 align, Sint16 valign, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time);
	CSpriteText(float x, float y, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time);
	CSpriteText(float x, float y, Sint16 align, Sint16 valign, std::string strFont, Sint16 nPtSize, std::string text, CColor color, long time);
	~CSpriteText();

protected:
	virtual void OnPrepareGraphics(CGraphics *pG = NULL);
	virtual void OnDraw(CGraphics *g);
};
