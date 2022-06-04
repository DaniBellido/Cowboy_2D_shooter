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


#ifndef __COLOR_H__
#define __COLOR_H__

class EXT_DECL CColor  
{
private:
	//actual color representation
	SDL_Color m_Color;
public:
	// Constructors
	CColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255)	{ Set(r, g, b, a); }
	CColor(const CColor &Color)			{ m_Color.r = Color.GetR(); m_Color.g = Color.GetG(); m_Color.b = Color.GetB(); m_Color.unused = Color.GetA(); }
	CColor()							{ Set(0, 0, 0, 255); }

	// Destructor
	virtual ~CColor()					{ }

	// Access R, G, B
	Uint8 GetR() const					{ return m_Color.r; }
	Uint8 GetG() const					{ return m_Color.g; }
	Uint8 GetB() const					{ return m_Color.b; }
	Uint8 GetA() const					{ return m_Color.unused; }

	void SetR(Uint8 r)					{ m_Color.r = r; }
	void SetG(Uint8 g)					{ m_Color.g = g; }
	void SetB(Uint8 b)					{ m_Color.b = b; }
	void SetA(Uint8 a)					{ m_Color.unused = a; }
	
	void Set(Uint8 r, Uint8 g, Uint8 b, Uint8 a=0)	{ m_Color.r = r; m_Color.g = g; m_Color.b = b; m_Color.unused = a; }
	void Set(CColor &color)				{ m_Color.r = color.R(); m_Color.g = color.G(); m_Color.b = color.B(); m_Color.unused = color.A(); }

	Uint8 &R()							{ return m_Color.r; }
	Uint8 &G()							{ return m_Color.g; }
	Uint8 &B()							{ return m_Color.b; }
	Uint8 &A()							{ return m_Color.unused; }

	// Conversion Operators
	operator SDL_Color()				{ return m_Color; }
	operator SDL_Color*()				{ return &m_Color; }

	// Assignment operators
	CColor &operator=(CColor &Color)	{ Set(Color); return *this; }
	CColor &operator+=(CColor &Color)	{ Set(min(R()+Color.R(), 255), min(G()+Color.G(), 255), min(B()+Color.B(), 255), min(A()+Color.A(), 255)); return *this; }
	CColor &operator-=(CColor &Color)	{ Set(max(R()-Color.R(),   0), max(G()-Color.G(),   0), max(B()-Color.B(),   0), max(A()-Color.A(),   0)); return *this; }
	CColor &operator*=(CColor &Color)	{ Set((GetR()*Color.GetR())/255, (GetG()*Color.GetG())/255, (GetB()*Color.GetB())/255, (GetA()*Color.GetA())/255); return *this; }
	CColor &operator*=(int Multiplier)	{ operator *=(CColor(Multiplier, Multiplier, Multiplier, 255)); return *this; }
	CColor &operator|=(CColor &Color)	{ Set(GetR()|Color.GetR(), GetG()|Color.GetG(), GetB()|Color.GetB(), GetA()|Color.GetA()); return(*this); return *this; }
	CColor &operator&=(CColor &Color)	{ Set(GetR()&Color.GetR(), GetG()&Color.GetG(), GetB()&Color.GetB(), GetA()&Color.GetA()); return(*this); return *this; }
	CColor &operator^=(CColor &Color)	{ Set(GetR()^Color.GetR(), GetG()^Color.GetG(), GetB()^Color.GetB(), GetA()^Color.GetA()); return(*this); return *this; }

	// Binary Operators
	CColor operator+(CColor &Color)		{ CColor c1 = *this; return c1 += Color; }
	CColor operator-(CColor &Color)		{ CColor c1 = *this; return c1 -= Color; }
	CColor operator*(CColor &Color)		{ CColor c1 = *this; return c1 *= Color; }
	CColor operator*(int Multiplier)	{ CColor c1 = *this; return c1 *= Multiplier; }
	CColor operator|(CColor &Color)		{ CColor c1 = *this; return c1 |= Color; }
	CColor operator&(CColor &Color)		{ CColor c1 = *this; return c1 &= Color; }
	CColor operator^(CColor &Color)		{ CColor c1 = *this; return c1 ^= Color; }

	// Unary Operator
	CColor operator~()					{ CColor c1 = *this; return c1^=CColor(255,255,255); }

	// Comparison Operators
	bool operator==(CColor Color)		{ return GetR()==Color.GetR() && GetG()==Color.GetG() && GetB()==Color.GetB() && GetA()==Color.GetA(); }
	bool operator!=(CColor Color)		{ return GetR()!=Color.GetR() || GetG()!=Color.GetG() || GetB()!=Color.GetB() || GetA()!=Color.GetA(); }

	//primary colors
	static CColor Red(Uint8 shade=255)							{ return(CColor(shade,0,0)); }
	static CColor Green(Uint8 shade=255)						{ return(CColor(0,shade,0)); }
	static CColor Blue(Uint8 shade=255)							{ return(CColor(0,0,shade)); }

	//secondary colors
	static CColor Yellow(Uint8 shade=255)						{ return(Red(shade)|Green(shade)); }
	static CColor Cyan(Uint8 shade=255)							{ return(Green(shade)|Blue(shade)); }
	static CColor Magenta(Uint8 shade=255)						{ return(Red(shade)|Blue(shade)); }

	// dark colours
	static CColor DarkRed(Uint8 shade=128)						{ return(Red(shade)); }
	static CColor DarkGreen(Uint8 shade=128)					{ return(Green(shade)); }
	static CColor DarkBlue(Uint8 shade=128)						{ return(Blue(shade)); }
	static CColor DarkYellow(Uint8 shade=128)					{ return(Yellow(shade)); }
	static CColor DarkCyan(Uint8 shade=128)						{ return(Cyan(shade)); }
	static CColor DarkMagenta(Uint8 shade=128)					{ return(Magenta(shade)); }

	// light colours	
	static CColor LightRed(Uint8 gray=128,Uint8 shade=255)		{ return(Red(shade)|White(gray)); }
	static CColor LightGreen(Uint8 gray=128,Uint8 shade=255)	{ return(Green(shade)|White(gray)); }
	static CColor LightBlue(Uint8 gray=128,Uint8 shade=255)		{ return(Blue(shade)|White(gray)); }
	static CColor LightYellow(Uint8 gray=128,Uint8 shade=255)	{ return(Yellow(shade)|White(gray)); }
	static CColor LightCyan(Uint8 gray=128,Uint8 shade=255)		{ return(Cyan(shade)|White(gray)); }
	static CColor LightMagenta(Uint8 gray=128,Uint8 shade=255)	{ return(Magenta(shade)|White(gray)); }

	// grayscale
	static CColor White(Uint8 shade=255)						{ return(Red(shade)|Green(shade)|Blue(shade)); }
	static CColor LightGray(Uint8 shade=192)					{ return(White(shade)); }
	static CColor DarkGray(Uint8 shade=128)						{ return(White(shade)); }
	static CColor Black(Uint8 shade=0)							{ return(White(shade)); }

	static CColor AnyBut(CColor c)								{ CColor C = Black(); if (C == c) C = White(); return C; }
	static CColor AnyBut(CColor c1, CColor c2)					{ CColor C = Black(); 
																  if (C == c1 || C == c2) C = White(); 
																  if (C == c1 || C == c2) C = DarkGray(); 
																  return C; }

	static CColor HSB(float hue, float saturation, float brightness)
	{
		int H = (int)(hue / 60.0f) % 6;
		float f = (hue / 60.0f) - (int)(hue / 60.0);
		int p = (int)(255 * brightness * (1 - saturation));
		int q = (int)(255 * brightness * (1 - f * saturation));
		int t = (int)(255 * brightness * (1 - (1 - f) * saturation));
		int v = (int)(brightness * 255);
		switch (H)
		{
		case 0: return CColor(v, t, p);
		case 1: return CColor(q, v, p);
		case 2: return CColor(p, v, t);
		case 3: return CColor(p, q, v);
		case 4: return CColor(t, p, v);
		case 5: return CColor(v, p, q);
		default: return CColor::Black();
		}
	}
};

#endif //#ifndef __COLOR_H__
