///*
//Class:Window
//Author:Rich Davison
//Description:Creates and handles the Window, including the initialisation of the mouse and keyboard.
//*/
//#pragma once
//#pragma warning( disable : 4099 )
//
//#include <string>
//
//#include <windows.h>
//#include <io.h>
//#include <stdio.h>
//#include <fcntl.h>
//
//#include "OGLRenderer.h"
//#include "Keyboard.h"
//#include "Mouse.h"
//#include "GameTimer.h"
//
//#define WIN32_LEAN_AND_MEAN
//#define VC_EXTRALEAN
//#define WINDOWCLASS "WindowClass"
//
//class OGLRenderer;
//
//class Window {
//public:
//	Window(std::string title = "OpenGL Framework", int sizeX = 800, int sizeY = 600, bool fullScreen = false);
//	~Window(void);
//
//	bool	UpdateWindow();
//
//	void	SetRenderer(OGLRenderer* r);
//
//	HWND	GetHandle();
//
//	bool	HasInitialised();
//
//	void	LockMouseToWindow(bool lock);
//	void	ShowOSPointer(bool show);
//
//	Vector2	GetScreenSize() { return size; };
//
//	static Keyboard*	GetKeyboard() { return keyboard; }
//	static Mouse*		GetMouse() { return mouse; }
//
//	GameTimer*   GetTimer() { return timer; }
//
//protected:
//	void	CheckMessages(MSG &msg);
//	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//
//	HWND			windowHandle;
//
//	static Window*		window;
//	static Keyboard*	keyboard;
//	static Mouse*		mouse;
//
//	GameTimer*	timer;
//
//	OGLRenderer*		renderer;
//
//	bool				forceQuit;
//	bool				init;
//	bool				fullScreen;
//	bool				lockMouse;
//	bool				showMouse;
//
//	Vector2				position;
//	Vector2				size;
//
//	float				elapsedMS;
//
//	bool				mouseLeftWindow;
//};

#pragma once
#include "Common.h"

#include "Mouse.h"
#include "Keyboard.h"
#include "GameTimer.h"

#include <vector>

#include <windows.h>
#include <fcntl.h>

//These two defines cut a lot of crap out of the Windows libraries
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#define WINDOWCLASS "WindowClass"

typedef void(*ResizeCallbackFunction) (int x, int y);

//This is the OS-specific crap required to render our pixel blocks on screen
class Window {
public:
	Window(uint width, uint height);
	~Window(void);

	bool	UpdateWindow();

	HWND	GetHandle() { return windowHandle; }

	void RegisterResizeCallback(ResizeCallbackFunction func);

	GameTimer* GetTimer() {
		return &timer;
	}
protected:
	void CheckMessages(MSG &msg);

	void Resize();

	//Windows requires a static callback function to handle certain incoming messages.
	static LRESULT CALLBACK StaticWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HWND	windowHandle;	//OS handle
	HDC		deviceContext;

	uint	screenWidth;
	uint	screenHeight;

	bool	forceQuit;
	bool	hasInit;

	GameTimer timer;

	std::vector<ResizeCallbackFunction> resizeListeners;
};

