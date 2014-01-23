/*	Win32 Text out in OpenGL

	Last Modified	4-4-00
*/

#ifndef __OPENGLTEXT_CPP_
#define __OPENGLTEXT_CPP_

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include <gl\gl.h>			// open gl headers

#include "OpenGLTextOut.h"

GLuint		fnt_base = NULL;	// opengl font

////////////////////////////////

BOOL Build_Font(void)								// Build Our Bitmap Font
{
	HFONT	font	= NULL;							// Windows Font ID

	HDC		hDC		= NULL;

	if (!(hDC = GetDC(NULL)))
		goto FAILURE;


	fnt_base = glGenLists(256);								// Storage For 96 Characters

	if (!(font = CreateFont(	-24,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New")))				// Font Name
		goto FAILURE;

	SelectObject(hDC, font);							// Selects The Font We Want

	wglUseFontBitmaps(hDC, 0, 256, fnt_base);			// Builds 96 Characters Starting At Character 32

	ReleaseDC(NULL, hDC);
	DeleteObject(font);

	return(TRUE);

FAILURE:
	if (hDC)
		ReleaseDC(NULL, hDC);
	hDC = NULL;

	return(FALSE);
}	// end BOOL Build_Font()

///////////////

void Delete_Font()
{
	if (fnt_base)
		glDeleteLists(fnt_base, 256);					// Delete All 96 Characters
	fnt_base = NULL;

}	// end void Delete_Font()

///////////////

GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Typedef For Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
    vsprintf(text, fmt, ap);							// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(fnt_base);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}	// end GLvoid glPrint(..)

/////////////////////////

#endif	// __OPENGLTEXTOUT_CPP_