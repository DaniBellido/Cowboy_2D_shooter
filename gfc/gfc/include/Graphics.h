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
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <list>
#include <map>
#include <string>
#include <functional>
#include <iomanip>

#include "Color.h"
#include "Vector.h"
#include "Rectangle.h"
#include "FileMgr.h"
//#include "Sprite.h"

#pragma warning (disable:4251)

// CGraphics class
class EXT_DECL CGraphics
{
private:
	SDL_Surface* m_pSurface;				// pointer to an SDL_Surface

	CVectorI m_vecScroll;					// scroll vector

	// File Loader (path resolving and cached loading)
	static CFileMgr<SDL_Surface> c_filemgr;

	// Fonts...
	struct FONT
	{
		TTF_Font *pFont;
		int size, height, width, ascent, descent, leading, baseline;
	};
	FONT m_curFont;							// font set (if any)
	std::string m_curFontFile;				// current font file
	std::map<std::string, FONT> m_fonts;	// font cache

	// Text Printing
	CColor m_textColor;						// text color
	int m_x, m_y;							// current pos for printing
	int m_ml, m_mr, m_mu, m_mb;				// margins: left, right, upper, bottom
	std::stringstream m_ss;					// string stream used for the << operator (from ver. 1.7)

public:
	// Constructors:

	// from a SDL Surface
	CGraphics(SDL_Surface* pSurface = NULL);
	// memory canvas
	CGraphics(int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
	CGraphics(int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask, CColor colorKey);
	// memory canvas compatible with the current display
	CGraphics(int width, int height);
	CGraphics(int width, int height, CColor colorKey);
	// from a loaded bitmap
	CGraphics(std::string sFileName);
	CGraphics(std::string sFileName, CColor colorKey);

	// copy constructor
	CGraphics(CGraphics &g);

	// copy from a pointer
	CGraphics(CGraphics *p);
	CGraphics(CGraphics *p, CColor colorKey);

	// Rectangular Fragment
	// Creates a CGraphics constructed of a rectangular fragment of another image.
	CGraphics(CGraphics *p, CRectangle rect);
	CGraphics(std::string sFileName, CRectangle rect);
	CGraphics(CGraphics *p, CRectangle rect, CColor colorKey);
	CGraphics(std::string sFileName, CRectangle rect, CColor colorKey);
	
	// Tiled Fragment
	// Creates a CGraphics constructed of a rectangular fragment of another image.
	// The image is considered to be divided into numCols x numRows regular rectangular tiles,
	// of which the one is taken iCol's column and iRow's row
	CGraphics(CGraphics *p, short numCols, short numRows, short iCol, short iRow);
	CGraphics(std::string sFileName, short numCols, short numRows, short iCol, short iRow);
	CGraphics(CGraphics *p, short numCols, short numRows, short iCol, short iRow, CColor colorKey);
	CGraphics(std::string sFileName, short numCols, short numRows, short iCol, short iRow, CColor colorKey);
	
	// destructor
	virtual ~CGraphics();

	// SDL_Surface Getters & Setters
	void SetSurface(SDL_Surface* pSurface)			{ m_pSurface = pSurface; }
	SDL_Surface* GetSurface()						{ return m_pSurface; }

	// Width & Height
	int GetWidth()									{ return m_pSurface->w; }
	int GetHeight()									{ return m_pSurface->h; }

	// Automatic Scroll Vector
	CVectorI GetScrollPos()							{ return m_vecScroll; }
	void SetScrollPos(CVectorI vecScroll)			{ m_vecScroll = vecScroll; }
	void SetScrollPos(CVector vecScroll)			{ m_vecScroll = CVectorI(vecScroll); }
	void SetScrollPos(int x, int y)					{ m_vecScroll = CVectorI(x, y); }
	void SetScrollPos()								{ m_vecScroll = CVectorI(0, 0); }
	void ResetScrollPos()							{ m_vecScroll = CVectorI(0, 0); }

	// Color functions
	CColor MatchColor(CColor color);				// Match color with the closest

	// Color Key (Trasnparent Color)
	bool SetColorKey(CColor& color);
	bool IsColorKeySet();
	CColor GetColorKey();
	bool ClearColorKey();

	// Flip Function
	bool Flip();

	// lock and unlock (for direct pixel access)
	bool Lock();
	void Unlock();


	// Drawing Functions
	CColor GetPixel(int x, int y);
	void SetPixel(int x, int y, CColor& color);

	bool Clear(CColor& clr);
	bool Blit(CRectangle& rectDest, CGraphics& Src, CRectangle& rectSrc);
	bool Blit(CRectangle& rectDest, CGraphics& Src);
	bool Blit(CVectorI ptDest, CGraphics& Src, CRectangle& rectSrc);
	bool Blit(CVectorI ptDest, CGraphics& Src);

	void DrawHLine(CVectorI pt1, Sint16 x2, CColor& color);
	void DrawVLine(CVectorI pt1, Sint16 y2, CColor& color);
	void DrawLine(CVectorI pt1, CVectorI pt2, CColor& color);
	void DrawLine(CVectorI pt1, CVectorI pt2, Uint8 width, CColor& color);	// thick line
	void DrawRect(CRectangle& rect, CColor& color);
	bool FillRect(CRectangle& rect, CColor& color);
	void DrawRect(CRectangle& rect, CColor& color, Sint16 rad);				// rounded rectangle
	void FillRect(CRectangle& rect, CColor& color, Sint16 rad);				// rounded rectangle
	void DrawOval(CRectangle& rect, CColor& color);
	void FillOval(CRectangle& rect, CColor& color);
	void DrawCircle(CVectorI pt, Uint16 radius, CColor& color);
	void FillCircle(CVectorI pt, Uint16 radius, CColor& color);
	void DrawPie(CVectorI pt, Uint16 radius, Uint16 angleStart, Uint16 angleEnd, CColor& color);
	void FillPie(CVectorI pt, Uint16 radius, Uint16 angleStart, Uint16 angleEnd, CColor& color);
	void DrawTriangle(CVectorI pt1, CVectorI pt2, CVectorI pt3, CColor& color);
	void FillTriangle(CVectorI pt1, CVectorI pt2, CVectorI pt3, CColor& color);
	void DrawPolyLine(CVectorI pts[], Uint16 num, CColor& color);
	void DrawPolygon(CVectorI pts[], Uint16 num, CColor& color);
	void FillPolygon(CVectorI pts[], Uint16 num, CColor& color);
	void DrawBezierLine(CVectorI pts[], Uint16 num, Uint16 nSteps, CColor& color);

	// Text Functions (low level)
	int DrawText(CVectorI pos, std::string fontFace, int nPtSize, CColor color, std::string pText);
	int DrawText(int x, int y, std::string fontFace, int nPtSize, CColor color, std::string pText)	{ return DrawText(CVectorI(x, y), fontFace, nPtSize, color, pText); }
	
	CGraphics *GetTextGraphics(TTF_Font *pFont, CColor color, std::string pText);
	CGraphics *GetTextGraphics(std::string fontFace, int nPtSize, CColor color, std::string pText);
	CGraphics *GetTextGraphics(std::string pText);

	// Text drawing functions
	// Since version 1.7 operator << in conjunction with a set of manipulators is the only recommended method of drawing on-screen text
	// Example:		*g << top << left << "Score: " << score << right << "Time: " << timetext(GetTime()) << flush;
	template <class T> 
	CGraphics &operator << (T val)								{ m_ss << val; return _DrawText(); }
	CGraphics &operator << (std::ostream&(*f)(std::ostream&))	{ return _DrawText(f); }
	CGraphics &operator << (std::ios_base& (__cdecl *f)(std::ios_base&))	{ return _DrawText(f); }
	CGraphics &operator << (CGraphics& (__cdecl *f)(CGraphics&)){ return (*f)(*this); }
	typedef std::function<CGraphics& (CGraphics& g)> manip;
	CGraphics &operator << (manip f)							{ return f(*this); }
	// Flush any not rendered text
	void Flush();
	// Get/set text flags - these are standard C++ flags as returned by ios_base::flags
	// ios_base::internal is re-used as "center" flag, and ios_base::skipws as "up"
	std::ios_base::fmtflags GetTextFlags()						{ return m_ss.flags(); }
	void SetTextFlags(std::ios_base::fmtflags fl)				{ m_ss.flags(fl); }

	std::string GetFontName()									{ return m_curFontFile; }
	int GetFontSize()											{ return m_curFont.size; }
	CColor GetTextColor()										{ return m_textColor; }

	// Text Output Manipulators
	// Mix them with other standard C++ stream manipulators and your text input to achieve the effect you like
	// endl					- to move to the new line. It may be above the current one rather than below, if you previously applied bottom or up manipulators
	// left, right, center	- to align text within the line
	// top, bottom			- to move to the top or the bottom row of the window. These manipulators set down and up modes respectively (see below)
	// down, up				- to make the text flowing down (default) or up when you change to a new line - unlike top/bottom, the insertion point will not be moved
	// vcenter				- to center your IP in vertical direction (in the middle of the screen)
	// rowcol, row, col		- to move to the specified row and/or column (note that left/right/center/up/down modes apply!)
	// xy					- to move to the specified screen coordinates
	// font, leading, color	- to change the font (name, size or both), font leading (distance between lines) and colour of the text
	// margins				- to setup the margins within the text window
	// timetext				- to display time in the standard format MM:SS.cc (technically not a manipulator function)
	// dec, hex, oct		- to change the basis used to display your numbers
	// fixed, scientific	- to switch between fixed and scientific notation of floating point values
	// setprecision			- to set the precision for floating point values
	// setw					- to set field width
	// setfill				- to set fill character
	// boolalpha/noboolalpha- to show alphanumerical bool values
	// showbase/noshowbase	- to show numerical base prefixes (0xff, 077)
	// showpoint/noshowpoint- to always show decimal point in floating point values
	// showpos/noshowpos	- to show positive sign (+) for non-negative numbers
	// uppercase/nouppercase- to generate upper-case letters in hexadecimal and scientific notation numbers
	// setiosflags/resetiosflags - to directly set or reset flags
	// setbase				- to set basefield flag
	// flush				- to immediately flush any buffered text
	// Following C++ manipulators must not be used with CGraphics objects: skipws, ws, internal. The left and right manipulators have a different meaning

	friend std::ios_base& center(std::ios_base& _Iosbase);
	friend std::ios_base& centre(std::ios_base& _Iosbase);
	friend std::ios_base& down(std::ios_base& _Iosbase);
	friend std::ios_base& up(std::ios_base& _Iosbase);
	friend CGraphics& top(CGraphics& g);
	friend CGraphics& bottom(CGraphics& g);
	friend CGraphics& vcenter(CGraphics& g);
	friend CGraphics& vcentre(CGraphics& g);
	friend manip row(float n);
	friend manip col(float n);
	friend manip rowcol(float r, float c);
	friend manip xy(int x, int y);
	friend manip font(std::string s);
	friend manip font(int n);
	friend manip font(std::string s, int n);
	friend manip leading(int n);
	friend manip color(CColor clr);
	friend manip color(Uint8 r, Uint8 g, Uint8 b, Uint8 a=255);
	friend manip margins(int l=5, int r=5, int u=2, int b=2);
	friend std::string timetext(long t);

	// change the default graphics file path (standard is "%;%images\\;.\\;images\\")
	static void SetDefaultFilePath(std::string new_path)	{ c_filemgr.SetPathString(new_path); }

private:
	// for internal use only

	// Low level text drawing - public use is not recommended from version 1.7 - for internal use only
	Sint16 DrawText(CVectorI pt, std::string pText);		// draws text adjusted to pt left side, right side or centrally, depending on the left/right/centre text flags; returns the right end of the text
	Sint16 DrawTextLt(CVectorI pt, std::string pText);		// draws text adjusted to pt left side; returns the width of the text
	Sint16 DrawTextCt(CVectorI pt, std::string pText);		// draws text adjusted centrally to pt; returns the half of the width of the text
	Sint16 DrawTextRt(CVectorI pt, std::string pText);		// draws text adjusted to pt right side; returns 0
	
	CGraphics &_DrawText();
	CGraphics &_DrawText(std::ostream&(*f)(std::ostream&));
	CGraphics &_DrawText(std::ios_base& (__cdecl *f)(std::ios_base&));

	// Text Attributes Functions - public use is not recommended from version 1.7 - for internal use only
	// Recommended replacement is provided in the comments below
	FONT FindFont(std::string fontFace, int nPtSize = 0);		// helper for SetFont and GetTextGraphics(font, color, text)
	void SetFont(std::string fontFace, int nPtSize = 0);		// *g << font(file, nPtSize); 
	void SetFont(int nPtSize);									// *g << font(nPtSize);
	void SetTextColor(CColor clr)				{ m_textColor = clr; }		// *g << color(clr);
	void SetMargins(int l, int r, int u, int b)	{ m_ml = l; m_mr = r; m_mu = u; m_mb = b; GotoRowCol(0, 0); }	// *g << margins(l, r, u, b);
	int  GetFontLeading()						{ return m_curFont.leading; }									// n/a
	void SetFontLeading(int l)					{ m_curFont.leading = l; m_curFont.baseline = m_curFont.leading - m_curFont.height - m_curFont.descent; }	// *g << leading(l);

	// Text Insertion Point functions - public use is not recommended from version 1.7 - for internal use only
	// Recommended replacement is provided in the comments below
	// GotoXY places the insertion point (IP) at the (x, y) screen coordinates
	// GotoRowCol, GotoRow/GotoRowXX and GotoCol/GotoColXX use zero-based indices of the text rows and columns to calculate position of the IP.
	// Rows are counted from the top (Tp), bottom (Bt) or centre (Ct) of the screen, and columns from the left (Lt), right (Rt) or centre (Ct)
	// In GotoRowCol, GotoRow and GotoCol the direction from which rows and cols are counted is determined automatically, 
	// depending on the current manipulator settings (left/right/center/top/bottom/vcenter/up/down)
	// GotoLn moves the IP one line down in top/down modes, or one line up in bottom/up modes. GotoLnUp/Dn moves the IP one line up and down, respectively
	void GotoXY(int x, int y)			{ m_x = x; m_y = y; }														// *g << xy(x, y);
	void GotoRowCol(float r, float c)	{ GotoRow(r); GotoCol(c); }													// *g << rowcol(r, c);
	void GotoRow(float r = 0)			{ if (m_ss.flags() & std::ios::skipws) GotoRowTp(r); else GotoRowBt(r); }	// *g << row(r);
	void GotoRowTp(float r = 0)			{ m_y = GetHeight() - m_mu - (int)((r + 1) * m_curFont.leading) + m_curFont.baseline; }			// *g << top << row(r);
	void GotoRowBt(float r = 0)			{ m_y = m_mb + (int)(r * m_curFont.leading) - m_curFont.descent; }								// *g << bottom << row(r);
	void GotoRowCt(float r = 0)			{ m_y = m_mb + (GetHeight() - m_mu - m_mb - m_curFont.leading) / 2 - (int)(r * m_curFont.leading); }	// *g << vcenter << row(r);
	void GotoCol(float c = 0)			{ auto f = m_ss.flags() & std::ios::adjustfield; if (f == std::ios::left) GotoColLt(c); else if (f == std::ios::right) GotoColRt(c); else GotoColCt(c); }	// *g << col(c);
	void GotoColLt(float c = 0)			{ m_x = m_ml + (int)(c * m_curFont.width);  }								// *g << left << col(c);
	void GotoColRt(float c = 0)			{ m_x = GetWidth() - m_mr - (int)(c * m_curFont.width); }					// *g << right << col(c);
	void GotoColCt(float c = 0)			{ m_x = m_ml + (GetWidth() - m_ml - m_mr) / 2 + (int)(c * m_curFont.width); }	// *g << center << col(c);
	void GotoLn()						{ m_y -= m_curFont.leading * ((m_ss.flags() & std::ios::skipws) ? 1 : -1); GotoCol(); }// *g << endl;
	void GotoLnDn()						{ m_y -= m_curFont.leading; GotoCol(); }										// *g << down << endl;
	void GotoLnUp()						{ m_y += m_curFont.leading; GotoCol(); }										// *g << up << endl;
};


inline std::ios_base& center(std::ios_base& _Iosbase)	{ _Iosbase.setf(std::ios_base::internal, std::ios_base::adjustfield); return (_Iosbase); }
inline std::ios_base& centre(std::ios_base& _Iosbase)	{ _Iosbase.setf(std::ios_base::internal, std::ios_base::adjustfield); return (_Iosbase); }
inline std::ios_base& down(std::ios_base& _Iosbase)		{ _Iosbase.setf(std::ios_base::skipws); return (_Iosbase); }		// skipws flag would never be normally used: it's reused here
inline std::ios_base& up(std::ios_base& _Iosbase)		{ _Iosbase.unsetf(std::ios_base::skipws); return (_Iosbase); }	//    as the down/up flag
inline CGraphics& top(CGraphics& g)						{ g << std::flush << down; g.GotoRowTp(); g.GotoCol(); return g; }
inline CGraphics& bottom(CGraphics& g)					{ g << std::flush << up; g.GotoRowBt(); g.GotoCol(); return g; }
inline CGraphics& vcenter(CGraphics& g)					{ g << std::flush << down; g.GotoRowCt(); g.GotoCol(); return g; }
inline CGraphics& vcentre(CGraphics& g)					{ g << std::flush << down; g.GotoRowCt(); g.GotoCol(); return g; }
inline CGraphics::manip row(float n)					{ return [n]    (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.GotoRow(n); return gr; }; }
inline CGraphics::manip col(float n)					{ return [n]    (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.GotoCol(n); return gr; }; }
inline CGraphics::manip rowcol(float r, float c)		{ return [r, c] (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.GotoRow(r); gr.GotoCol(c); return gr; }; }
inline CGraphics::manip xy(int x, int y)				{ return [x, y] (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.GotoXY(x, y); return gr; }; }
inline CGraphics::manip font(std::string s)				{ return [s]    (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.SetFont(s); return gr; }; }
inline CGraphics::manip font(int n)						{ return [n]    (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.SetFont(n); return gr; }; }
inline CGraphics::manip font(std::string s, int n)		{ return [s, n] (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.SetFont(s, n); return gr; }; }
inline CGraphics::manip leading(int n)					{ return [n]    (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.SetFontLeading(n); return gr; }; }
inline CGraphics::manip color(CColor clr)				{ return [clr]  (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.SetTextColor(clr); return gr; }; }
inline CGraphics::manip color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){ return [r, g, b, a]  (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.SetTextColor(CColor(r, g, b, a)); return gr; }; }
inline CGraphics::manip margins(int l, int r, int u, int b)	 { return [l, r, u, b]  (CGraphics& gr) -> CGraphics& { gr << std::flush; gr.SetMargins(l, r, u, b); return gr; }; }
inline std::string timetext(long t)						{ std::stringstream s; s << std::setfill('0') << std::setw(2) << t/60000%100 << ":" << std::setw(2) << t/1000%60 << "." << std::setw(2) << t/10%100; return s.str(); }

//////////////////////////////////////////////////////////////////////
// Helper class for animated sequences
class CGraphicsGrid
{
	std::string m_strFileName;
	std::string m_strAliasName;
	CGraphics *m_pGraphics;
	short m_numCols, m_numRows, m_iColFrom, m_iRowFrom, m_iColTo, m_iRowTo;
	bool m_bHorizontally;

public:
	CGraphicsGrid(char *pFileName) : m_strFileName(pFileName), m_strAliasName(pFileName), m_pGraphics(NULL) { }
	CGraphicsGrid(char *pFileName, char *pAliasName) : m_strFileName(pFileName), m_strAliasName(pAliasName), m_pGraphics(NULL) { }
	CGraphicsGrid(CGraphics *pGraphics, char *pAliasName) : m_strFileName(""), m_strAliasName(pAliasName), m_pGraphics(pGraphics) { }




};

#endif
