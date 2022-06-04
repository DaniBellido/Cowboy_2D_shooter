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
#ifndef __FILE_LOADER_H__
#define __FILE_LOADER_H__

#include <string>
#include <map>
#include <fstream>

// WARNING: This part depends on Windows API
// Potential porting problem
#undef INADDR_ANY
#undef INADDR_LOOPBACK
#undef INADDR_BROADCAST
#undef INADDR_NONE
#include <windows.h>


// Smart file loader, implements:
// - list of paths to be scanned
// - cached loading

template <class T>
class CFileMgr
{
	// The FileMgr works with a file list path: a list of directories separated by semicolons.
	// Percent sign is replaced by the executable path.
	// Example: "%;%images\\;.\\;images\\"
	std::string path;							

	std::string respath;
	std::map<std::string, T*> m_cache;

	// Handlers
	std::function<T*(std::string filename)> m_loadHandler;
	std::function<void (T*)> m_deleteHandler;

public:
	CFileMgr(std::string path, std::function<T*(std::string filename)> loadHandler, std::function<void (T*)> deleteHandler)				
	{ 
		SetPathString(path);
		m_loadHandler = loadHandler;
		m_deleteHandler = deleteHandler;
	}

	~CFileMgr()
	{
		for each (std::pair<std::string, T*> p in m_cache)
			m_deleteHandler(p.second);
	}

	std::string GetPathString()					{ return path; }

	void SetPathString(std::string new_path)
	{ 
		path = respath = new_path; 

		// THIS IS WINDOWS-SPECIFIC CALL!
		// There is no portable possibility to determine the executable path
		// main argc/argv values arrive too late - this function is typically called
		// from within constructors of static objects!
		char mfn[256];
		GetModuleFileNameA(0, mfn, 256);

		char drive[_MAX_DRIVE];
		char dir[_MAX_PATH];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];	
		_splitpath_s(mfn, drive, sizeof(drive), dir, sizeof(dir), fname, sizeof(fname), ext, sizeof(ext));
		std::string baseDir = std::string(drive) + std::string(dir);
	
		respath = path;
		if (respath[respath.size() - 1] != ';')
			respath += ";";
		size_t i = respath.find_first_of("%");
		while (i != std::string::npos)
		{
			respath.replace(i, 1, baseDir);
			i = respath.find_first_of("%");
		}
	}

	std::string FindPathStr(std::string filename)
	{
		// split the filename - do nothing more if a drive or dir is already specified
		char drive[_MAX_DRIVE];
		char dir[_MAX_PATH];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];	
		if (_splitpath_s(filename.c_str(), drive, sizeof(drive), dir, sizeof(dir), fname, sizeof(fname), ext, sizeof(ext)) != 0) return filename;
		if (*drive || *dir) return filename;	// full path specified, no scan

		// use path to resolve the filename	
		size_t i = 0, j = respath.find_first_of(";", i);
		while (j != std::string::npos)
		{
			std::string p = respath.substr(i, j - i);

			std::ifstream f(p + filename);
			if (f.good())
			{
				f.close();
				return p + filename;
			}

			i = j + 1;
			j = respath.find_first_of(";", i);
		}
		return filename;
	}

	T *Load(std::string filename)
	{
		auto i = m_cache.find(filename);
		if (i == m_cache.end())
			m_cache[filename] = m_loadHandler(FindPathStr(filename));

		return m_cache[filename];
	}
};

#endif //#ifndef __PROPERTY_H__
