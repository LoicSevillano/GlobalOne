#include "CFormulaire.h"

LRESULT CFormulaire::virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_PAINT)
    {
        PAINTSTRUCT ps;
        HDC hDc = BeginPaint(hWnd, &ps); // Handle sur device control
        RECT r;
        GetWindowRect(hWnd, &r);
        r.right -= r.left;
        r.left = 0;
        r.bottom -= r.top;
        r.top = 0;

        auto color = CreateSolidBrush(RGB(230, 230, 230));
        FillRect(hDc, &r, color);
        EndPaint(hWnd, &ps);

    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
