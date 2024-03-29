#include "Main.h"
//------------------------------------
//  Reliable Software, (c) 1996-2002
//------------------------------------
#include "WinClass.h"
#include "Control.h"
#include "WinEx.h"
#include "resource.h"
#include <sstream>

#include <iostream>
#include <io.h>
#include <fcntl.h>

// The main window is a modeless dialog box

int main()
{
	std::cout << "POOTIS";
	return WinMain(GetModuleHandle(NULL), NULL, GetCommandLine(), SW_SHOW);;

}

int WINAPI WinMain
   (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow)
{
	Win::ClassMaker viewClass ("WinViewClass", hInst);
	viewClass.SetSizeRedraw ();
	HBRUSH brush = reinterpret_cast<HBRUSH> (::GetStockObject (BLACK_BRUSH));
	viewClass.SetBgBrush (brush);
	viewClass.Register ();

	HWND hDialog = ::CreateDialog (hInst, MAKEINTRESOURCE (DLG_MAIN), 0, DialogProc);

    if (hDialog == 0)
    {
		std::ostringstream buf;
		buf << "Error 0x" << std::hex << GetLastError ();
		::MessageBox (0, buf.str ().c_str (), "CreateDialog", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    MSG  msg;
	int status;
	while ((status = ::GetMessage (&msg, NULL, 0, 0 )) != 0)
    {
		if (status == -1)
			break;
		if (!::IsDialogMessage (hDialog, &msg))
        {
			::TranslateMessage (&msg);
			::DispatchMessage (&msg);
        }
    }

	//Adds console
	using namespace std;

    AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;

    // use the console just like a normal one - printf(), getchar(), ...

	cout << "POOTEND";

	//END ADD CONSOLE

    return msg.wParam;
}
