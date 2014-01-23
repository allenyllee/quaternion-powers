#ifndef __INCLUDES_H_
#define __INCLUDES_H_

//////////////////////////////

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NODEFAULTLIB
#define NODEFAULTLIB
#endif

#include <windows.h>		// include important windows stuff
#include <windowsx.h>
#include <mmsystem.h>
#include <objbase.h>		// COM stuff
#include <iostream.h>		// include important C/C++ stuff
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h> 
#include <math.h>
#include <io.h>
#include <fcntl.h>
//#include <time.h>

//#include <winuser.h>		// control stuff

//#define NDEBUG			// remove assertions
#include <assert.h>			// assertions

#include <gl\gl.h>			// open gl headers
#include <gl\glu.h>
#include <gl\glaux.h>
#include <gl\glut.h>

////////////////////////////

#endif	// __INCLUDES_H_