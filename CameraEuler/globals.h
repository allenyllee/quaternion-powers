/* Global variables */


#ifndef __GLOBALS_H_
#define __GLOBALS_H_

//////////////

HWND		hwnd_MainWindow	= NULL;
HINSTANCE	main_Instance	= NULL;

HGLRC		hRC	= NULL;		// handle to OpenGL rendering context
HDC			hDC	= NULL;


float	camera_pos[3];			// camera position in world coords
float	camera_roll		= 0,	// camera roll, pitch and yaw	
		camera_pitch	= 0,
		camera_yaw		= 0;

//////////////

#endif	// __GLOBALS_H_