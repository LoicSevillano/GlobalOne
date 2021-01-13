#include "CBandeau.h"
#include "GlobalOneApp.h"
#include "CFormulaireAccueil.h"
extern CGlobalOneApp* theApp;
LRESULT CBandeau::virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

        auto color = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hDc, &r, color);
        EndPaint(hWnd, &ps);

    }
    else if(msg == WM_CREATE)
    {
        m_ButtonWelcome.Create(GetInstance(), WS_CHILD|BS_BITMAP, hWnd, 10, 10, 50, 50);
        HANDLE handleBitmap = LoadImage(NULL, L".\\img\\home.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        SendMessage(m_ButtonWelcome.GethWnd(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)handleBitmap);
        ShowWindow(m_ButtonWelcome.GethWnd(), SW_SHOW);

        m_ButtonCommande.Create(GetInstance(), WS_CHILD | BS_BITMAP, hWnd, 10, 70, 50, 50);
        handleBitmap = LoadImage(NULL, L".\\img\\cmd.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        SendMessage(m_ButtonCommande.GethWnd(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)handleBitmap);
        ShowWindow(m_ButtonCommande.GethWnd(), SW_SHOW);

        m_ButtonCustomer.Create(GetInstance(), WS_CHILD | BS_BITMAP, hWnd, 10, 130, 50, 50);
        handleBitmap = LoadImage(NULL, L".\\img\\customer.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        SendMessage(m_ButtonCustomer.GethWnd(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)handleBitmap);
        ShowWindow(m_ButtonCustomer.GethWnd(), SW_SHOW);

        m_ButtonAgency.Create(GetInstance(), WS_CHILD | BS_BITMAP, hWnd, 10, 190, 50, 50);
        handleBitmap = LoadImage(NULL, L".\\img\\agency.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        SendMessage(m_ButtonAgency.GethWnd(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)handleBitmap);
        ShowWindow(m_ButtonAgency.GethWnd(), SW_SHOW);
    }

    else if (msg == WM_COMMAND)
    {
        switch (LOWORD(wParam))
        {
        case BN_CLICKED:
            if ((HWND)lParam == m_ButtonWelcome.GethWnd())
            {
                RECT r;
                delete theApp->GetFormulaire();
                theApp->setFormulaire(new CFormulaireAccueil());
                GetWindowRect(theApp->getMainMhwnd(), &r);
                theApp->GetFormulaire()->Create(GetInstance(), WS_CHILDWINDOW, theApp->getMainMhwnd(), 100, 0, r.right - r.left - 100, r.bottom - r.top);
                ShowWindow(theApp->GetFormulaire()->GethWnd(), SW_SHOW);
            }
            else if ((HWND) lParam == m_ButtonCommande.GethWnd())
            {
                MessageBox(NULL, L"Commande", L"", MB_OK);

            }
            else if ((HWND)lParam == m_ButtonCustomer.GethWnd())
            {
                RECT r;
                delete theApp->GetFormulaire();
                theApp->setFormulaire(new CFormulaireClient());
                GetWindowRect(theApp->getMainMhwnd(), &r);
                theApp->GetFormulaire()->Create(GetInstance(), WS_CHILDWINDOW, theApp->getMainMhwnd(), 100, 0, r.right - r.left - 100, r.bottom - r.top);
                ShowWindow(theApp->GetFormulaire()->GethWnd(), SW_SHOW);

            }
            else if ((HWND)lParam == m_ButtonAgency.GethWnd())
            {
                MessageBox(NULL, L"Agency", L"", MB_OK);

            }
            break;
        default:
            break;

        }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
