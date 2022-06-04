/****************************************************************************
GFC - Games Fundamental Classes
Copyright (C) 2009-2016 Jarek Francik, Kingston University London

This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License:
http://creativecommons.org/licenses/by-sa/4.0/

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Created by Jarek Francik
jarek@kingston.ac.uk
****************************************************************************/
#pragma once

#include <list>
#include <vector>
#include <algorithm>

// GFC-specific extensions to std

namespace std
{
	// This function is applicable to a collection of object pointers.
	// It applies the zero-parameter member function fn to objects referenced by each iterator in range [first, last), in order.
	template<class _Iter, class _Class>
	void for_each(_Iter first, _Iter last, void (_Class::*fn)()) {
		for_each(first, last, [fn](_Class *p) { (p->*fn)(); });
	}

	// This function is applicable to a collection of object pointers.
	// It applies the one-parameter member function fn to objects referenced by each pointer in range [first, last), in order.
	// Passes the value param, of any type, as a sole parameter in each function call.
	template<class _Iter, class _Class, class _Param>
	void for_each(_Iter first, _Iter last, void (_Class::*fn)(_Param param), _Param param) {
		for_each(first, last, [fn, param](_Class *p) { (p->*fn)(param); });
	}


	// GFC specific extensions applicable for STL collections (such as list, vector) of pointers to objects
	template <class _Ty>
	class _gfc_std_ext : public _Ty
	{
	public:
		// Constructors
		_gfc_std_ext() : _Ty() { }
		_gfc_std_ext(_Ty &t) : _Ty(t) { }
		template<class _Iter> _gfc_std_ext(_Iter first, _Iter last) : _Ty(first, last) { }

		// Removes all elements for which predicate pr returns true;
		// additionally, if the element is a pointer, deletes the object referenced by that pointer.
		// This function is similar to list::remove_if (which does not delete the objects)
		template <class _Pr>
		void delete_if(_Pr pr)
		{
			[this](auto _pr)
			{
				if constexpr (is_base_of<list<typename _Ty::value_type>, _Ty>::value)
					remove_if(_pr);
				else
					erase(std::remove_if(begin(), end(), _pr), end());
			}([pr](typename _Ty::value_type t) { bool b = pr(t); if constexpr(std::is_pointer<typename _Ty::value_type>::value) if (b) delete t; return b; });
		}

		// Applies the zero-paramter member function fn to objects referenced by each pointer in the collection, in order
		// Example: sprites.for_each(&CSprite::UnDelete);
		template<class _Fn>
		void for_each(_Fn fn) { std::for_each(begin(), end(), fn); }

		// Applies the one-paramter member function fn to objects referenced by each pointer in the collection, in order.
		// Passes the value param, of any type, as a sole parameter in each function call.
		// Example: sprites.for_each(&CSprite::Update, GetTime());
		template<class _Fn, class _Param>
		void for_each(_Fn fn, _Param param) { std::for_each(begin(), end(), fn, param); }

		// Deletes objects referenced by each pointer in the collection and then removes all elements leaving the container with a size of 0
		void delete_all() { for_each([](typename _Ty::value_type t) { if constexpr(std::is_pointer<typename _Ty::value_type>::value) delete t; }); clear(); }
	};
}

template <class T> bool deleted(T p) { return p->IsDeleted(); }
inline bool deleted(CSprite *p) { return deleted<CSprite*>(p); }

typedef std::_gfc_std_ext<std::list<CSprite*>> CSpriteList;
typedef std::_gfc_std_ext<std::vector<CSprite*>> CSpriteVector;
