
#include "Gui.h"

// DISPLAY FUNCTIONS: ----------------------------------------------------------

void GUI::DisplayHelp()
{
    cout << endl;
    cout << "  Command lines:                 Current values:"          << endl;
    cout << "  +-----------------------+      "                         << endl;
    cout << "  |  0: Display help.     |      P     = " << Block::P     << endl;
    cout << "  |  1: Compress image.   |      Q     = " << Block::Q     << endl;
    cout << "  |  2: Decompress image. |      Alpha = " << Block::Alpha << endl;
    cout << "  |  3: Setup P.          |"                               << endl;
    cout << "  |  4: Setup Q.          |"                               << endl;
    cout << "  |  5: Setup Alpha.      |"                               << endl;
    cout << "  |  6: Clear screen.     |"                               << endl;
    cout << "  | -1: Exit.             |"                               << endl;
    cout << "  +-----------------------+"                               << endl;
    cout << endl;
}

void GUI::DisplayBadNumberError()
{
    cout << endl;
    cout << "  WARNING: Could not understand command line." << endl;
    cout << "  Type '0' to display the help view." << endl;
    cout << endl;
}

void GUI::DisplaySplash()
{
    system("clear");
    cout << endl;
    cout << "+---------------------------------------------------------------+";
    cout << endl;
    cout << "| WELCOME TO MuZIP  -  The Blazing Fast .PPM Image Compressor   |";
    cout << endl;
    cout << "+---------------------------------------------------------------+";
    cout << endl << endl;
    
    GUI::DisplayHelp();
}

// SETTINGS: -------------------------------------------------------------------

void GUI::SetP()
{
    int p;
    cout << endl << "  # Set 'p' value = ";
    cin >> p;
    Block::P = p;
    cout << endl;
}

void GUI::SetQ()
{
    int q;
    cout << endl << "  # Set 'q' value = ";
    cin >> q;
    Block::Q = q;
    cout << endl;
}

void GUI::SetAlpha()
{
    double alpha;
    cout << endl << "  # Set 'alpha' value = ";
    cin >> alpha;
    Block::Alpha = alpha;
    cout << endl;
}

// WINDOWS: --------------------------------------------------------------------

int GUI::DisplayMainMenu()
{
    cout << "  > ";
    
    int command;
    while (cin >> command)
    {
        switch (command)
        {
            case  0 : GUI::DisplayHelp(); break;
            case  1 : return 0;
            case  2 : return 1;
            case  3 : GUI::SetP(); break;
            case  4 : GUI::SetQ(); break;
            case  5 : GUI::SetAlpha(); break;
            case  6 : GUI::DisplaySplash(); break;
            case -1 : cout << endl << "  Exit" << endl << endl; exit(0);
            default : GUI::DisplayBadNumberError(); break;
        }
        
        cout << "  > ";
    }
}

// INIT: -----------------------------------------------------------------------

int GUI::InitMuZIP()
{
    GUI::DisplaySplash();
    return GUI::DisplayMainMenu();
}