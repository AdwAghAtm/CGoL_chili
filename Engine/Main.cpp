/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Main.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "ChiliException.h"
#include <windows.h>
#include <process.h>

struct BoardLoopArg
{
	Game *theGame;
	MainWindow *wnd;
};

unsigned __stdcall BoardLoop(void* arg) {
	{
		// Cast the void* back to the correct struct type
		BoardLoopArg* myArgs = static_cast<BoardLoopArg*>(arg);

		// Access struct members
		Game* theGame = myArgs->theGame;
		MainWindow* wnd = myArgs->wnd;

		while( wnd->ProcessMessage() )
			{
				theGame->Go();
			}
	};

	return 0;
}

int WINAPI wWinMain( HINSTANCE hInst,HINSTANCE,LPWSTR pArgs,INT )
{
	struct BoardLoopArg arg;

	try
	{
		MainWindow wnd( hInst,pArgs );	
		arg.wnd = &wnd;
		try
		{
			Game theGame( wnd );
			arg.theGame = &theGame;

			theGame.Pre();

			// Create the thread and pass the struct as an argument
			HANDLE thread = (HANDLE)_beginthreadex(nullptr, 0, BoardLoop, &arg, 0, nullptr);

			// Wait for the thread to finish (optional)
			WaitForSingleObject(thread, INFINITE);
			CloseHandle(thread);

			/*while( wnd.ProcessMessage() )
			{
				theGame.Go();
			}*/
		}
		catch( const ChiliException& e )
		{
			const std::wstring eMsg = e.GetFullMessage() + 
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox( e.GetExceptionType(),eMsg,MB_ICONERROR );
		}
		catch( const std::exception& e )
		{
			// need to convert std::exception what() string from narrow to wide string
			const std::string whatStr( e.what() );
			const std::wstring eMsg = std::wstring( whatStr.begin(),whatStr.end() ) + 
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox( L"Unhandled STL Exception",eMsg,MB_ICONERROR );
		}
		catch( ... )
		{
			wnd.ShowMessageBox( L"Unhandled Non-STL Exception",
				L"\n\nException caught at Windows message loop.",MB_ICONERROR );
		}
	}
	catch( const ChiliException& e )
	{
		const std::wstring eMsg = e.GetFullMessage() +
			L"\n\nException caught at main window creation.";
		MessageBox( nullptr,eMsg.c_str(),e.GetExceptionType().c_str(),MB_ICONERROR );
	}
	catch( const std::exception& e )
	{
		// need to convert std::exception what() string from narrow to wide string
		const std::string whatStr( e.what() );
		const std::wstring eMsg = std::wstring( whatStr.begin(),whatStr.end() ) +
			L"\n\nException caught at main window creation.";
		MessageBox( nullptr,eMsg.c_str(),L"Unhandled STL Exception",MB_ICONERROR );
	}
	catch( ... )
	{
		MessageBox( nullptr,L"\n\nException caught at main window creation.",
			L"Unhandled Non-STL Exception",MB_ICONERROR );
	}

	return 0;
}