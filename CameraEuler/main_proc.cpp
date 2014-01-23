#ifndef __MAIN_PROC_CPP_
#define __MAIN_PROC_CPP_

#include "include.h"

#include "externals.h"

/////////////////////////////////////

LRESULT CALLBACK Main_Proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_CREATE:			// when window is first created
		{
		}	break;
	case WM_CLOSE:		// called when Alt-F4 is pressed or X is clicked
		{
			SendMessage(hwnd,WM_DESTROY,0,0);	// destroy windows
		}; break;		// return 0 to disable closing for now
	case WM_DESTROY:		// when window is destroyed
		{
			PostQuitMessage(0);		// send WM_QUIT to message queue, allows 1 while loop break
		}	break;		// end case WM_DESTROY
	case WM_PAINT:			// when windows needs repainting
		{
			PAINTSTRUCT	ps;

			HDC hdc = BeginPaint(hwnd, &ps);	// get graphic device context
			EndPaint(hwnd, &ps);			// release the graphic device context
		} break;		// end case WM_PAINT
	case WM_SYSCOMMAND:
		{
			switch(wparam)		// switch system command
			{
			case SC_KEYMENU:			// to bring up menu, fall throught
			case SC_MONITORPOWER:		// fall through
			case SC_SCREENSAVE:
				{
					return(0);
				} break;
			default:
				return(DefWindowProc(hwnd, msg, wparam, lparam));	// return unhandled msgs
			}	// end switch(wparam)

		}	break;		// end case WM_SYSCOMMAND
	case WM_KEYDOWN:
		{
			int virtual_code = (int)wparam;		// get virtual key

			switch(virtual_code)
			{
			case VK_ESCAPE:		// Escape key
				{
					PostQuitMessage(0);			// break out of 1 loop
				}	break;
			case 0x52:		// R key
				{
					camera_roll		= 0;
					camera_pitch	= 0;
					camera_yaw		= 0;
				}	break;
			case 0x41:		// A key
				{
					camera_pos[2] -= CAMERA_Z_DELTA;		// getting closer to object point
					if (camera_pos[2] < CAMERA_Z_MIN)
						camera_pos[2] = CAMERA_Z_MIN;
				}	break;
			case 0x5A:		// Z key
				{
					camera_pos[2] += CAMERA_Z_DELTA;		// getting further from object point
					if (camera_pos[2] > CAMERA_Z_MAX)
						camera_pos[2] = CAMERA_Z_MAX;
				}	break;
			case VK_UP:		// up
				{
					camera_pitch += CAMERA_X_DELTA;		// dive camera
					if (camera_pitch >= 360)			// wrap around
						camera_pitch -= 360;
				}	break;
			case VK_DOWN:	// down
				{
					camera_pitch -= CAMERA_X_DELTA;		// lift camera
					if (camera_pitch < 0)				// wrap around
						camera_pitch += 360;
				}	break;
			case VK_LEFT:	// left
				{
					camera_yaw -= CAMERA_Y_DELTA;
					if (camera_yaw < 0)				// wrap around
						camera_yaw += 360;
				}	break;
			case VK_RIGHT:	// right
				{
					camera_yaw += CAMERA_Y_DELTA;
					if (camera_yaw >= 360)			// wrap around
						camera_yaw -= 360;
				}	break;
			case VK_INSERT:	// insert
				{
					camera_roll += CAMERA_Z_DELTA;
					if (camera_roll >= 360)
						camera_roll -= 360;
				}	break;
			case VK_PRIOR:	// page up
				{
					camera_roll -= CAMERA_Z_DELTA;
					if (camera_roll < 0)
						camera_roll +=360;
				}	break;
			default:
				return(DefWindowProc(hwnd, msg, wparam, lparam));	// return unhandled msgs
			}	// end switch(virtual code)
		}	break;		// end case WM_KEYDOWN
	default:
		return(DefWindowProc(hwnd, msg, wparam, lparam));	// return unhandled msgs
	}		// end switch(msg)

	return(0);		// tell windows message is processed
}		// end LRESULT CALLBACK Main_Proc(..)

///////////////////////////////

#endif	// __MAIN_PROC_CPP_