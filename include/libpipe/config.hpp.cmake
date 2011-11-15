/*
*
* Copyright (c) 2011 David-Matthias Sichau
* Copyright (c) 2010 Marc Kirchner
*
* This file is part of libpipe.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#ifndef __LIBPIPE_INCLUDE_LIBPIPE_CONFIG_HPP__

    #cmakedefine ENABLE_THREADING

      #ifdef _WIN32
        #define VC_EXTRALEAN
        #include <windows.h>
    	#define LIBPIPE_EXPORT __declspec( dllexport )
    	/* Disable a template related MSVC warning.
    	  See: http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html */
    	#pragma warning( disable: 4251 )
	    #pragma warning ( disable : 4996 )
    	#pragma warning ( disable : 4996 )
	    #pragma warning (disable: 4275)
        #pragma warning (disable: 4101)
        #pragma warning (disable: 4503)
        #pragma warning (disable: 4244) //time_h warnings long
        

    	#undef DELETE
    	#undef max
    	#undef min
    	
    	typedef long suseconds_t;
    #else
    	#define LIBPIPE_EXPORT
    #endif
    
#endif

