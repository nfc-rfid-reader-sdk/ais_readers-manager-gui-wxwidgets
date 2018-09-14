#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#if __WIN32 || __WIN64
#	include <conio.h>
#	include <windows.h>
#elif linux || __linux__ || __APPLE__
#	define __USE_MISC 1
#	include <unistd.h>
#	include <termios.h>
#	undef __USE_MISC
#	include "include/conio_gnu.h"
#else
#	error "Unknown build platform."
#endif
#include "include/utils.h"
#include "include/functions.h"


int main(int argc, char **argv)
{


#if linux || __linux__ || __APPLE__
	_initTermios(0);
#endif


        if (argc > 1) {



        string argument = argv[1];

            if (argument == "-gui"){

                gui_on = 1;

                    char key;

    OpenDebugLog();

    PrepareSettings();

    OpenAllDevicesAndReadLists();

    usage();

                do{

PrintRealTimeEventTable();


		while (gui_command=='0')
		{
        //cout << endl<<  "AppLoop" << endl;

            fflush(stdin);

            AppLoop();

            gui_command=getchar();

		}
        fseek(stdin,0,SEEK_END);
		menu(gui_command);
        //fflush(stdin);
		gui_command = '0';

	}
	while (gui_command != '\x1b');

CloseDebugLog();
#if linux || __linux__ || __APPLE__
	_resetTermios();
	tcflush(0, TCIFLUSH); // Clear stdin to prevent characters appearing on prompt
#endif
	return EXIT_SUCCESS;
        }
    }
else {

        gui_on = 0;


    char key;

    OpenDebugLog();

    PrepareSettings();

    OpenAllDevicesAndReadLists();

    usage();


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
}

