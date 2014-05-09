
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../data/Block.h"

using namespace std;

#ifndef GUI_CPP
#define GUI_CPP

/* +---------------------------------------------------------------------------+
   | GUI.CPP and GUI.H                                                         |
   |                                                                           |
   | This class handles the GUI controls so that the user interface is         |
   | separated from the application logic.                                     |
   +---------------------------------------------------------------------------+
*/

class GUI
{
    private:
        
        // PRIVATE FUNCTIONS: --------------------------------------------------
        
        static void DisplayHelp();
        static void DisplayBadNumberError();
        static void DisplaySplash();
        static int  DisplayMainMenu();
        
        static void SetP();
        static void SetQ();
        static void SetAlpha();
        
    public:
        
        // INIT: ---------------------------------------------------------------
        
        static int InitMuZIP();
};

#endif
