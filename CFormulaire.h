#pragma once
#include <CFenetre.h>
class CFormulaire :
    public CFenetre
{
public:
     LRESULT virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wPAram, LPARAM lParam);

};

