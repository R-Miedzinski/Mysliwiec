#include <windows.h>
#include <cstdio>
#include <iostream>
using namespace std;

HANDLE hStdin;
DWORD fdwSaveOldMode;

int main(VOID)
{
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    int counter = 0;

    // Get the standard input handle.
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        exit(0);
    // Save the current input mode, to be restored on exit.
    if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
        exit(0);
    // Enable the window and mouse input events.
    fdwMode = ENABLE_WINDOW_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
        exit(0);


    // ---------------------------------------
    cout<< "jestes pewien?" << endl;

    SYSTEMTIME st;
    GetSystemTime(&st);
    int starttime = st.wSecond;         // pobieramy aktualny czas systemu
    int klawisz=0;
    //petla
    while (klawisz==0 && st.wSecond-starttime<2)// (counter++ <= 100)
    {
        GetSystemTime(&st);

        // OBSLUGA ZDARZEN
        FlushConsoleInputBuffer(hStdin);
        if (!PeekConsoleInput(
            hStdin,      // input buffer handle
            irInBuf,     // buffer to read into
            128,         // size of read buffer
            &cNumRead)) // number of records read
        exit(0);

        // petla po zdarzeniach
        for (i = 0; i < cNumRead; i++)
        {
            switch (irInBuf[i].EventType)
            {
            case KEY_EVENT: // nacisniety klawisz
                klawisz = irInBuf[i].Event.KeyEvent.wVirtualKeyCode;
                break;
            default:
                exit(0);
                break;
            }
        }
    }


    if(klawisz)
    {
        cout << "wcisnieto klawisz: " << klawisz;
    }
    else
    {
        cout << "nie bylo klawisza" << endl;
    }



    // na koniec programu
    // Restore input mode on exit.
    SetConsoleMode(hStdin, fdwSaveOldMode);

    return 0;
}

