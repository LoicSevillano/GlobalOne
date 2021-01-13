#include "CFormulaireAccueil.h"

LRESULT CFormulaireAccueil::virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){

	switch (msg) {
		case WM_CREATE:
			m_hBitmap = LoadImage(NULL, L".\\img\\welcome.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			break;
		case WM_PAINT:
		{
			RECT r;
			GetWindowRect(hWnd, &r);
			PAINTSTRUCT ps;
			HDC	hdc = BeginPaint(hWnd, &ps);

			HDC hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, m_hBitmap);
			StretchBlt(hdc, 0, 0, r.right - r.left, r.bottom - r.top, hdcMem, 0, 0, 1920, 1080, SRCCOPY);
			DeleteObject(hdcMem);
			EndPaint(hWnd, &ps);
			
		}
			break;
		default:
			break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}