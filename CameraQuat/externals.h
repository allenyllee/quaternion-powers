/*	External declarations of globals

*/

#ifndef __EXTERNALS_H_
#define	__EXTERNALS_H_

#include "Maths\3DMaths.h"

///////////////////////

extern HWND			hwnd_MainWindow;
extern HINSTANCE	main_Instance;

extern HGLRC		hRC;		// handle to OpenGL rendering context
extern HDC			hDC;


const float		CAMERA_Z_MIN	= 1;
const float		CAMERA_Z_MAX	= 100;

const float		CAMERA_X_DELTA	= 1;
const float		CAMERA_Y_DELTA	= 1;
const float		CAMERA_Z_DELTA	= 1;

extern float	camera_pos[3];		// camera position in world coords

extern float	camera_roll;		// roll, pitch and yaw of camera
extern float	camera_pitch;
extern float	camera_yaw;


extern float	key_x, key_y, key_z;	// keys for camera change

extern Quaternion	camera_quat;	// camera quaternion

//////////////////////

#endif	// __EXTERNALS_H_