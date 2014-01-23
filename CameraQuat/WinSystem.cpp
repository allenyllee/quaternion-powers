/*	Win system

*/

#ifndef __WINSYSTEM_CPP_
#define __WINSYSTEM_CPP_

#include "include.h"
#include "externals.h"

///////////////////

HWND Init_Windows(HINSTANCE h_inst, void* wndproc)
{
	WNDCLASSEX	wndclass;		// generic window class
	HWND		hwnd = NULL;	// generic window handle

	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;	//types of received message
	wndclass.lpfnWndProc	= (long(__stdcall *)(HWND,unsigned int, unsigned int, long))wndproc;// event handler
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= GetModuleHandle(NULL);
	wndclass.hIcon			= NULL;
	wndclass.hCursor		= NULL;			// cursor
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	// background
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= "OpenGL Demo";
	wndclass.hIconSm		= NULL;				// small icon

	if (!RegisterClassEx(&wndclass))		// registering class
		goto FAILURE;
		
	hwnd = CreateWindowEx(
			WS_EX_APPWINDOW,
			"OpenGL Demo",
			"OpenGL Demo",
			WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
			0,
			0,
			800,
			600,
			NULL,								// parent
			NULL,								// menu
			h_inst,
			NULL);

	if (!hwnd)		// if error
		goto FAILURE;

	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	SetFocus(hwnd);

	return(hwnd);		// success

FAILURE:
	return(NULL);

}	// end HWND Init_Window(..)

///////////////////

BOOL Init_OpenGL(void)
{
	int nPixelFormat;

	PIXELFORMATDESCRIPTOR pfd;

	ZeroMemory(&pfd,sizeof(pfd));
	pfd.nSize		= sizeof(pfd);
	pfd.nVersion	= 1;
	pfd.dwFlags		= PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;

	pfd.iPixelType	= PFD_TYPE_RGBA;
	pfd.cColorBits	= 24;
	pfd.cDepthBits	= 32;
	pfd.iLayerType	= PFD_MAIN_PLANE;

	hDC = GetDC(hwnd_MainWindow);

	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
		goto FAILURE;

	if (!SetPixelFormat(hDC, nPixelFormat, &pfd))
		goto FAILURE;

	if (!(hRC = wglCreateContext(hDC)))
		goto FAILURE;
		
	if (!wglMakeCurrent(hDC,hRC))
		goto FAILURE;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// specify background color to black

	glClearDepth(1.0f);				// enable clearing of depth buffer
	glDepthFunc(GL_LESS);			// type of test to do
	glEnable(GL_DEPTH_TEST);		// enable depth testing
	
	glShadeModel(GL_SMOOTH);		// enables smooth shading
	glMatrixMode(GL_PROJECTION);	// select the projection matrix
	glLoadIdentity();				// reset the projection matrix

	gluPerspective(45.0, (GLfloat)800/600, 0.1f, 100.0f);		// calculate aspect ratio of window

	glMatrixMode(GL_MODELVIEW);		// select the model view mode

	return(TRUE);

FAILURE:
	return(FALSE);
}	// end BOOL Init_OpenGL()

////////////////////

#endif	// __WINSYSTEM_CPP_