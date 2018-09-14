#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#if __WIN32 || __WIN64
#	include <conio.h>
#	include <windows.h>
#elif linux || __linux__ || __APPLE__
#	define __USE_MISC
#	include <unistd.h>
#	include <termios.h>
#	undef __USE_MISC
#	include "include/conio_gnu.h"
#else
#	error "Unknown build platform."
#endif
#include "include/functions.h"

int main(void)
{
    char key;

    OpenDebugLog();

    PrepareSettings();

    OpenAllDevicesAndReadLists();

    usage();

#if linux || __linux__ || __APPLE__
	_initTermios(0);
#endif
	do
	{
	    PrintRealTimeEventTable();

		while (!_kbhit())
		{
            AppLoop();
		}

		key = _getch();
		menu(key);
	}
	while (key != '\x1b');

    CloseDebugLog();
#if linux || __linux__ || __APPLE__
	_resetTermios();
	tcflush(0, TCIFLUSH); // Clear stdin to prevent characters appearing on prompt
#endif
	return EXIT_SUCCESS;
}

