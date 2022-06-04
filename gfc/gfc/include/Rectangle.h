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
#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "vector.h"

//CRectangle--abstract an SDL_Rect
class EXT_DECL CRectangle : public SDL_Rect
{
public:
	// Constructors
	CRectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h)	{ Set(x, y, w, h); }
	CRectangle(SDL_Rect rc)						{ Set(rc.x, rc.y, rc.w, rc.h); }
	CRectangle(const CRectangle& rc)			{ Set(rc.x, rc.y, rc.w, rc.h); }
	CRectangle()								{ Set(0, 0, 0, 0); }

	// Destructor
	~CRectangle()	{ }

	// Geometry
	Sint16 Left() const							{ return x; }
	Sint16 Bottom() const						{ return y; }
	Sint16 Right() const						{ return x + w; }
	Sint16 Top() const							{ return y + h; }
	Sint16 GetCenterX() const					{ return x + w / 2; }
	Sint16 GetCenterY() const					{ return y + h / 2; }

	// The following four functions guarantee that w and h (width and height) will always be positive
	// Sets the rectangle from the coordinates of the lower-left corner and size; negative width or height turns the rectangle inside out
	CRectangle& Set(Sint16 _x, Sint16 _y, Sint16 _w, Sint16 _h)
												{ if (_w < 0) { _w = -_w; _x -= _w; } 
												  if (_h < 0) { _h = -_h; _y -= _h; } 
												  x = _x; y = _y; w = _w; h = _h; return(*this); }
	// Sets the rectangle from the coordinates of the lower-left corner and size; negative width or height collapse to zero
	CRectangle& SetColl(Sint16 _x, Sint16 _y, Sint16 _w, Sint16 _h)
												{ x = _x; y = _y; w = max(_w, 0); h = max(_h, 0); return(*this); }
	// Sets the rectangle from the coordinates of a pair of tops; negative width or height turns the rectangle inside out
	CRectangle& SetTops(Sint16 x0, Sint16 y0, Sint16 x1, Sint16 y1)
												{ return Set(x0, y0, x1 - x0, y1 - y0); }
	// Sets the rectangle from the coordinates of a pair of tops; negative width or height collapse to zero
	CRectangle& SetTopsColl(Sint16 x0, Sint16 y0, Sint16 x1, Sint16 y1)
												{ if (x1 < x0) x0 = x1 = (x0 + x1) / 2;
												  if (y1 < y0) y0 = y1 = (y0 + y1) / 2;
												  return Set(x0, y0, x1 - x0, y1 - y0); }

	// Conversion Operators
	operator CVector() const					{ return CVector(x, y); }

	// Y-Invert function
	CRectangle &YInv(Sint16 H)					{ y = H - y - h; return *this; }
//	friend CRectangle YInv(const CRectangle &r, Sint16 H)
//												{ CRectangle rect = r; r.YInv(H); return rect; }

	// Empty - setting & testing
	CRectangle& SetEmpty()						{ return Set(0, 0, 0, 0); }
	bool IsEmpty() const						{ return (w == 0 || h == 0); }

	// Offset and Moving
	CRectangle& Offset(Sint16 dx, Sint16 dy)	{ x += dx; y += dy; return(*this); }
	CRectangle& Offset(const CVector& pt)		{ x += (Sint16)pt.m_x; y += (Sint16)pt.m_y; return(*this); }
	CRectangle& MoveTo(Sint16 _x, Sint16 _y)	{ x = _x; y = _y; return(*this); }
	CRectangle& MoveTo(const CVector& pt)		{ x = (Sint16)pt.m_x; y = (Sint16)pt.m_y; return(*this); }

	// Change in size
	CRectangle& Grow(Sint16 l, Sint16 r, Sint16 t, Sint16 b)	{ Set(x - l, y - b, w + l + r, h + t + b); return(*this); }
	CRectangle& Grow(Sint16 hor, Sint16 ver)	{ return Grow(hor, hor, ver, ver); }
	CRectangle& Grow(Sint16 amount)				{ return Grow(amount, amount, amount, amount); }

	// Union & Intersection
	CRectangle& Union(const CRectangle& rc)			{ return SetTops  (min(Left(), rc.Left()), min(Bottom(), rc.Bottom()), max(Right(), rc.Right()), max(Top(), rc.Top())); }
	CRectangle& Intersection(const CRectangle& rc)	{ return SetTopsColl(max(Left(), rc.Left()), max(Bottom(), rc.Bottom()), min(Right(), rc.Right()), min(Top(), rc.Top())); }
	CRectangle Union(const CRectangle& rc1, const CRectangle& rc2)			{ CRectangle rc(rc1); rc.Union(rc2); return rc; }
	CRectangle Intersection(const CRectangle& rc1, const CRectangle& rc2)	{ CRectangle rc(rc1); rc.Intersection(rc2); return rc; }

	// Conatinment & Intersection Tests
	bool Contains(Sint16 x, Sint16 y) const	{ return x >= Left() && x <= Right() && y >= Bottom() && y <= Top(); }
	bool Contains(const CVector& pt) const	{ return pt.m_x >= Left() && pt.m_x <= Right() && pt.m_y >= Bottom() && pt.m_y <= Top(); }

	bool Intersects(const CRectangle &rc) const	{ return min(Right(), rc.Right()) > max(Left(), rc.Left()) && min(Top(), rc.Top()) > max(Bottom(), rc.Bottom()); }

	// Operators
	
	// assignment
	CRectangle& operator +=(const CVector& pt)	{ return Offset(pt); }
	CRectangle& operator -=(const CVector& pt)	{ return Offset(-pt); }

	CRectangle& operator +=(CRectangle& rc) { return Union(rc); }
	CRectangle& operator *=(CRectangle& rc) { return Intersection(rc); }

	// binary
	CRectangle operator +(const CVector& pt) const		{ CRectangle result =(*this); return result += pt; }
	CRectangle operator -(const CVector& pt) const		{ CRectangle result =(*this); return result -= pt; }
	CRectangle operator +(const CRectangle& rc) const	{ CRectangle result =(*this); return result.Union(rc); }
	CRectangle operator *(const CRectangle& rc) const	{ CRectangle result =(*this); return result.Intersection(rc); }


	// comparisons
	bool operator ==(const CRectangle rc)			{ return x == rc.x && y == rc.y && w == rc.w && h == rc.h; }
	bool operator !=(const CRectangle rc)			{ return x != rc.x || y != rc.y || w != rc.w || h != rc.h; }
};

#endif
