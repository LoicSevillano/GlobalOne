#pragma once
#include "CFormulaire.h"
class CFormulaireAccueil :
    public CFormulaire
{
private:
    HANDLE m_hBitmap;
    LRESULT virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wPAram, LPARAM lParam);
};

