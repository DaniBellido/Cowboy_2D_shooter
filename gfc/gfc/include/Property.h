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
#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include "Graphics.h"
#include <vector>

class EXT_DECL PROPERTY
{
	enum { INT, FLOAT, STR, IMG, NONE } type;

	union
	{
		int numi;
		float numf;
	};
	CGraphics *pIm;
	std::string str;

public:
	std::vector<PROPERTY> m_indexedProperties;

public:
	PROPERTY()					{ type = NONE; pIm = NULL; }
	PROPERTY(int d)				{ type = INT; numi = d; pIm = NULL; }
	PROPERTY(float d)			{ type = FLOAT; numf = d; pIm = NULL; }
	PROPERTY(const char *p)		{ type = STR; str = p; pIm = NULL; }
	PROPERTY(CGraphics *p)		{ type = IMG; pIm = new CGraphics(*p); }

	void Erase()				{ if (pIm) delete pIm; for each (PROPERTY prop in m_indexedProperties) prop.Erase(); }
	void CopyFrom(PROPERTY &p)				
	{
		//if (pIm) delete pIm; pIm = NULL;
		pIm = NULL;
		str = "";
		switch (type)
		{
		case INT: numi = p.numi; break;
		case FLOAT: numf = p.numf; break;
		case STR: str = p.str; break;
		case IMG: pIm = new CGraphics(p.pIm); break;
		}
		if (p.m_indexedProperties.size() > 0)
		{
			m_indexedProperties.resize(p.m_indexedProperties.size());
			for (size_t i = 0; i < p.m_indexedProperties.size(); i++)
				m_indexedProperties[i].CopyFrom(p.m_indexedProperties[i]);
		}
	}

	operator int()				{ if (type == INT) return numi; else if (type == FLOAT) return (int)numf; else return 0; } 
	operator unsigned()			{ if (type == INT) return (unsigned)numi; else if (type == FLOAT) return (unsigned)numf; else return 0; } 
	operator float()			{ if (type == FLOAT) return numf; else if (type == INT) return (float)numi; else return 0; }
	operator const char *()		{ if (type == STR) return str.c_str(); else return ""; }
	operator char *()			{ if (type == STR) return (char*)str.c_str(); else return "NO VALUE"; }
	operator CGraphics *()		{ if (type == IMG) return pIm; else return (pIm = new CGraphics("")); }
};

	
	

#endif //#ifndef __PROPERTY_H__
