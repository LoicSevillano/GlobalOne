#include "GlobalOneApp.h"
extern HINSTANCE hInst;

CGlobalOneApp::CGlobalOneApp(HINSTANCE hInst, HWND hWnd, wstring sConnect)
{

	m_hInstance = hInst;
	m_hWnd = hWnd;
	ShowWindow(hWnd, SW_MAXIMIZE);
	m_database.OpenDatabase(sConnect);
	RECT r;
	GetWindowRect(hWnd, &r);
	m_fenetreMenu.Create(hInst,WS_CHILDWINDOW, hWnd, 0, 0, 100, r.bottom - r.top);
	ShowWindow(m_fenetreMenu.GethWnd(), SW_SHOW);
}
HINSTANCE GetInstance()
{
	return hInst;
}

