/***
*inputf.h - input formatted
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*		https://github.com/sidealong/console_inputer
*Purpose:
*       defines inputf() - input formatted data
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <windows.h>
#include <wincon.h>

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

void input(
	const char *s
	)
/*
 *	do the real work
 */
{
	DWORD        w;
	HANDLE       h = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD i = { 0 };
	i.EventType    = KEY_EVENT;
	while (*s) {
		i.Event.KeyEvent.uChar.AsciiChar = *s != '\n' ? *s : VK_RETURN;

		i.Event.KeyEvent.bKeyDown = TRUE;
		WriteConsoleInput(h, &i, 1, &w);
		i.Event.KeyEvent.bKeyDown = FALSE;
		WriteConsoleInput(h, &i, 1, &w);
		++s;
	}
}

/***
*int inputf(format, ...) - input formatted data
*
*Purpose:
*       Inputs formatted data on stdin using the format string to
*       format data and getting as many arguments as called for
*       Uses temporary buffering to improve efficiency.
*       input does the real work here
*
*Entry:
*       char *format - format string to control data format/number of arguments
*       followed by list of arguments, number and type controlled by
*       format string
*
*Exit:
*       returns number of characters inputed
*
*Exceptions:
*
*******************************************************************************/
int inputf(
	const char *format,
	...
	)
/*
 * stdin 'INPUT', 'F'ormatted
 */
{
	va_list arglist;
	char    buffer[1024];
	int     retval = 0;

	//_VALIDATE_RETURN((format != NULL), EINVAL, -1);

	va_start(arglist, format);
	retval = vsprintf_s(buffer, sizeof(buffer), format, arglist);
	
	input(buffer);
	return retval;
}

#ifdef __cplusplus
} /* extern "C" */
#endif  /* __cplusplus */