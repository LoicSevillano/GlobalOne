#pragma once
#include <CFenetre.h>
#include "Cbutton.h"

class CBandeau :
    public CFenetre
{
private:
    LRESULT virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    Cbutton m_ButtonWelcome;
    Cbutton m_ButtonCustomer;
    Cbutton m_ButtonAgency;
    Cbutton m_ButtonSeller;
    Cbutton m_ButtonEnd;
    Cbutton m_ButtonCommande;


};

