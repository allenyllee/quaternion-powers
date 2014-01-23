/* Main file

*/

#include "include.h"		// common includes

#include "globals.h"		// global vars

#include "OpenGLTextOut.h"

///////////////

extern LRESULT CALLBACK Main_Proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);	// wndproc

extern HWND Init_Windows(HINSTANCE h_inst, void* WNDPROC);
extern BOOL Init_OpenGL(void);

void Main_Shutdown(void);
void Main_Loop(void);

////////////

void Set_Up_Camera(void);	// sets up the camera

///////////////////////////

int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR lp_cmd_line, int show_cmd)
{
	MSG msg;

	if (!(hwnd_MainWindow = Init_Windows(h_instance, Main_Proc)))
	{
		MessageBox(hwnd_MainWindow,"Error initializing window","Error",MB_OK);
		return(0);
	}

	if (!Init_OpenGL())
	{
		MessageBox(hwnd_MainWindow,"Error initializing OpenGL","Error",MB_OK);
		return(0);
	}

	Build_Font();


	Set_Up_Camera();

	while(1)
	{
		if (PeekMessage(&msg, NULL,0,0,PM_REMOVE))
		{
			if (WM_QUIT == msg.message)		// break out of loop
				break;

			TranslateMessage(&msg);			// send to procedure
			DispatchMessage(&msg);
		} //end if PeekMessage(..)
		else
		{
			Main_Loop();		// main loop
		}	// end else if bAppIsActive
	} // end while

	Main_Shutdown();			// release all resources


	return(msg.wParam);			// return to windows

}	// end WINMAIN

/////////////

void Main_Shutdown(void)
{
	Delete_Font();

	wglMakeCurrent(NULL, NULL);

	if (hRC)
		wglDeleteContext(hRC);
	hRC = NULL;

	ReleaseDC(hwnd_MainWindow, hDC);

	DestroyWindow(hwnd_MainWindow);		// flush buffer

}	// end void Clean_up(void)

/////////////

void Main_Loop(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear the screen

	glLoadIdentity();										// reset the view

	glTranslatef(-camera_pos[0], -camera_pos[1], -camera_pos[2]);	// move camera
	glRotatef(camera_roll,	0.0f, 0.0f, 1.0f);				// Rotate X, Y, Z
	glRotatef(camera_yaw,	0.0f, 1.0f, 0.0f);
	glRotatef(camera_pitch,	1.0f, 0.0f, 0.0f);

	// model objects - just draw frame and cubes
	glColor3f(0.5, 0.5, 0.5);		// origin
	glutWireCube(1.0);

	glPushMatrix();			// x axis
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(5, 0, 0);
	glEnd();
	glTranslatef(5,0,0);	
	glutWireCube(1.0);
	glPopMatrix();

	glPushMatrix();			// y axis
	glColor3f(0, 0.5, 0.5);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 5, 0);
	glEnd();
	glTranslatef(0,5,0);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();			// z axis
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 5);
	glEnd();
	glTranslatef(0,0,5);
	glutWireCube(1);
	glPopMatrix();


	glLoadIdentity();							// reset the view
	glTranslatef(0.0f,0.0f,-10.0f);				// translate for raster positioning

	glRasterPos2f(-5, 3.0f);					// output camera position on screen
	glPrint("Roll %f", camera_roll);
	glRasterPos2d(-5, 2.5f);
	glPrint("Pitch %f", camera_pitch);
	glRasterPos2d(-5, 2);
	glPrint("Yaw %f", camera_yaw);

	SwapBuffers(hDC);		// OpenGL page flipping

}	// end void Main_Loop()

////////////////

void Set_Up_Camera(void)
{
	// set up camera position initially
	camera_pos[0]	= 0;
	camera_pos[1]	= 0;
	camera_pos[2]	= 20;


	return;
}	// end void Set_Up_Arm(void)

///////

