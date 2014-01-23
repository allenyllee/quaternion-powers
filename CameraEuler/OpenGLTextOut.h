/*	Text out in win32 OpenGL

	Last Modified	23-2-00
*/

/*

	// disable blend to speed it up
  
	glLoadIdentity();							// reset the view
	glTranslatef(0.0f,0.0f,-10.0f);				// translate for raster positioning
	glColor3f(0.8f, 0.8f, 0.8f);
	glRasterPos2f(-5, 0);		// raster pos is relative to translation
	glPrint("Test");

*/

#ifndef __OPENGLTEXTOUT_H_
#define	__OPENGLTEXTOUT_H_

///////////////////////

BOOL Build_Font(void);					// Build Our Bitmap Font
void Delete_Font();						// free memory for font
GLvoid glPrint(const char *fmt, ...);	// Custom GL "Print" Routine

////////////////////////

#endif	// __OPENGLTEXTOUT_H_