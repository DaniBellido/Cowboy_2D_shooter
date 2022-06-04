Please distribute this file with the GFC runtime environment.

==========================
GFC - Games Fundamental Classes
==========================

Games Fundamental Classes - GFC - is a library created to facilitate building simple 2D games in C++
by Jarek Francik - purposely developed as an aid to the Games Programming and Game Science modules
taught at Kingston University, London.

The GFC source code is available from:
https://github.com/jfrancik/gfc

This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License:
http://creativecommons.org/licenses/by-sa/4.0/

GFC has been build on top of SDL (Simple DirectMedia Layer), a cross platform graphics library written by Sam Lantinga, 
with extensions by various authors. SDL is available under the terms of GNU LGPL license at:
http://www.libsdl.org/

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Created by Jarek Francik
Copyright (C) 2009-2018 Jarek Francik, Kingston University London
jarek@kingston.ac.uk

Sample projects: catchit, fruitninja and spacefighter are written by Andreas Hoppe.

Version 1.0 20/03/2009
Version 1.1 11/04/2009
Version 1.2 25/04/2009
Version 1.4 11/02/2011
Version 1.5 6/11/2011
Version 1.6 24/03/2012
Version 1.7 7/04/2012
Version 1.71 14/03/2013
Version 2.00 5/12/2013
Version 2.01 12/12/2013
Version 2.02  8/01/2014
Version 2.03 17/01/2014
Version 2.04 23/01/2014
Version 2.05 26/01/2014
Version 2.06 17/02/2014
Version 2.10 10/03/2014
Version 2.20 15/09/2014
Version 2.30 14/12/2015
Version 2.40 1/10/2016
Version 2.50 1/10/2017
Version 2.60 30/9/2018


Planned Future Extensions
===================

1. Bezier curves
2. Textured polygons
3. Dynamic link to Box2D

Changes in Version 2.60
===================

1. Compatibility with Visual Studio 2017 and C++17 standard.
2. New functionality (in beta version): CSprite::Clone. Use with care!
3. New functionality: CSprite::LoadAnimation (to replace old-style AddImage calls)
4. Bug fix: SetAnimation is now safe (used to crash the program unless the grid was properly provided)
5. GFC-specifc extensions to list and vectors:
    - new delete_if syntax which replaces remove_if;
      for example, instead of: sprites.remove_if(deleted);
      use: sprites.delete_if(deleted);
      This new function call guarantees that all objects (e.g. sprites) will be deleted - with no memory leaks
    - new delete_all function applicable to all sprite collections - deletes all sprites - with no memory leaks
    - new for_each syntax, for example sprites.for_each(&CSprite::Update, GetTime());
6. CGameApp::DebugMemoryLeaks added - to anable memory leak report
7. Updated version of SDL_gfx library
8. Bug fix: alpha channel added to a number of processing functions in CGraphics
9. Bug fix: Distance function changed the contents of the first vector - fixed
10. Bug fix: CGraphics::DrawLine did not work properly if the line was drawn from right to left - fixed
11. Bug fix: Memory leaks in CMusicPlayer::Play and deleted<CSprite*>
12. Minor fix: result or parameter type changed from long to Uint32 in Game::GetTime, GetDeltaTime, GetTimeGameOver, ResetTime, SetTime and SetTimeGameOver


Changes in Version 2.50
===================

1. Added function: CGameApp *CGame::GetApp() - returning a pointer to the global Game Application object
2. Added function: CGame::ForceDraw() - forces an additionsl draw cycle (screen graphics update) at any time
3. Bug fix: the health value used by GetHealth/SetHealth function is now initialised to 0

Changes in Version 2.40
===================

1. Updated for use with Visual Studio 2015
2. New support for scrolling: GetScrollPos and SetScrollPos functions in CGraphics class
3. New support for console windows: CGameApp:OpenConsole()
4. Dying functionality added to Sprites
5. Bug removed from Sound system and Play Modes added
6. Minor fixes in game life cycle control
7. Proceed / ProceedVelocity / ProceedOmega functions added

Changes in Version 2.30
===================

1. Updated for use with Visual Studio 2013
2. New set of mouse handling functions:
    - GetMouseCoords
    - IsMouseFocus
    - IsL/R/MButtonDown
    - Hide/ShowMouse
3. Changes to facilitate porting projects between GFC and GTech:
    - Get/SetStatus and Get/SetHealth functions in CSprite
    - GetGameMode
    - CFont class to mimic GTech-style text output
4. SDL and platform dependent functions: _GetSDLVersion and _GetWindowHandle

Changes in Version 2.20
===================

1. Updated for use with Visual Studio 2012

Changes in Version 2.10
===================

This is a major update - may require source code modifications for existing projects

1. CSprite::OnUpdate: change of deltaTime parameter type from Uint32 to Sint32
    to allow Updates going back in time.
    WARNING: May break compatibility!
2. Distributed with zlib license
3. SDL upgraded to version 1.2.15
4. New interface for loading images into sprites: LoadImage, SetImage and AddImage
5. New interface for sprite animation (SetAnimation)
6. Thick lines and rounded rectangles added in CGraphics

Changes in Version 2.06
===================

This version has nener been released

1. Bug fix: problems with transparency with some graphics data formats,
    and particularly with rotating sprites - fixed
2. Bug fix - rotating sprites were sometimes shaky - fixed
3. Path list support for file loading (graphics and sound) 
4. Cached file input for graphics and sound
5. Simplified interface for playing sounds

Changes in Version 2.05
===================

1. Bug fix: Normalize function for a zero length vector
2. Bug fix: text output following font size change


Changes in Versions 2.03 - 2.04
========================

1. Bug fix - text position after font size changed 

Changes in Versions 2.03 - 2.04
========================

1. CVector Reflect function
2. New framework for game levels
3. More precised timing for Update
4. Bug fixes

Changes in Versions 2.00/2.01/2.02
==========================

Total rebuild, change of most of class interfaces, in particular:

1. Change of sprite coordinates and size from integer to float vector
2. Support for vector oriented calculations
2. Change of the Y coordination direction (Y is pointing up)
3. New functions in CSprite (Get/SetMass, Accelerate, ApplyForce)

THE LIBRARY IS NOW NOT COMPATIBLE WITH 1.* VERSIONS!


Changes in Version 1.71
======================

1. Fixed problem with sdl_gfc.dll: it was dependent on debug version of MVC runtime - thanks to Andy Walker for spotting this!

2. Fixed problem with CSprite::SetDirection(double, double): parameters (0, 0) will not alter the direction

Changes in Version 1.7
======================

1. Sound API

2. Using a bitmap file that does not exist does not crash the application any more - instead, default pattern is shown

3. Speed and velocity related functions in CSprite class reorganised to become more physically consistent:
   - new GetSpeed and SetSpeed functions to replace GetVelocity and SetVelocity
   - new SetVelocity function to replace SetMotion
   - GetVelocity(), SetVelocity(double) and SetMotion(double, double) are now obsolete but kept for compatibility reasons

4. Redesigned text output functionality in CGraphics object:
   - mix-typed text output may be pushed using << operator
   - most standard C++ stream manipulators may be used, for example: endl, hex, setprecision
   - special manipulators added like left, right, center, bottom, font, color and many other to facilitate text output
   Example of the new-style text output:

      *g << top << left << "Score: " << score << right << "Time: " << timetext(GetTime()) << flush;
      if (IsGameOver())
      {
        *g << vcenter << center << font(32) << color(CColor::Red()) << "GAME OVER";
        *g << endl << font(20) << "SCORE: " << score << flush;
      }
   


Changes in Version 1.6
======================

1. Bug fixed
Description: SetVelocity did not impose any motion unless preceded by SetDirection
Cause: m_vX and m_vY both initialised to 0 in CSprite::CSprite
Solution: m_vY initialised to 1
Result: Fixed

2. <sstream> included as standard
#include <sstream> added to gfc.h

3. GFC_VERSION added in gfc.h
Added: #define GFC_VERSION	160

4. Some problems with displaying semi-transparent images are fixed
This fix involved upgrade of SDL_gfx library from ver. 2.0.18 to ver. 2.0.23


Changes in Version 1.5
======================

1. Removing items from collections added:
- CSprite::MarkAsRemoved
- CSprite::IsMarkedAsRemoved
- marked_as_removed

2. CSpriteVector added


Changes in Version 1.41
=======================

- IsKeyDown function added
- CSprite::SetX & CSprite::SetY functions added


Changes in Version 1.4
======================

1. Copy Constructor added to CGraphics class

2. New CGraphics derived classes: 
- CGraphicsFragment - graphics file based on a rectangular fragment of another graphics object or file
- CGraphicsTile - as above, but the fragment based on a regular subdivision of the larger Graphics object
into a set of tiles - determined by number of columns and rows.

3. CSpriteBitmap class functionality moved to CSprite. CSpriteBitmap is kept for backward compatibility
but it has empty implementation

4. Repertoire of constructors for CSprite class enhanced - to reflect new functionality taken over from 
CSpriteBitmap

5. New family of functions added to CSprite to operate on named properties:
- GetProperty
- SetProperty

6. New image and animation functions added to CSprite:
- ClearImage
- SetImageFromFile
- SetImage
- SetAnimation

7. New pixel-wise collision detection added:
- HitTestPixel

8. New low level graphics functions in CSprite class:
- GetGraphics
- GetRotoGraphics
- PrepareGraphics

9. CSprite::OnDraw is no longer a pure virtual function, and CSprite is no longer an abstract class

