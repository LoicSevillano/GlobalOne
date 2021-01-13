#pragma once
#include "CFormulaire.h"
#include "CListBox.h"
#include "CEditBox.h"
#include "Cbutton.h"
#include "CStaticText.h"
#include "CFenetre.h"
#include "TimeUtils.h"


class CFormulaireClient :
    public CFormulaire

{
private:
   
    CListBox m_CustomerList;
    CStaticText m_StaticNom;
    CEditBox m_EditNom;
    CStaticText m_StaticPrenom;
    CEditBox m_EditPrenom;
    CStaticText m_StaticBirthday;
    CEditBox m_EditBirthday;
    CStaticText m_StaticAdresse;
    CEditBox m_EditAdresse;
    CStaticText m_StaticCP;
    CEditBox m_EditCP;
    CStaticText m_StaticVille;
    CEditBox m_EditVille;
    CStaticText m_StatictMail;
    CEditBox m_EditMail;
    CStaticText m_StaticPhone;
    CEditBox m_EditPhone;
    CStaticText m_StaticMobile;
    CEditBox m_EditMobile;
    Cbutton m_AddButton;
    Cbutton m_ButtonSave;
    bool m_bRules;
    
    LRESULT virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wPAram, LPARAM lParam);

    void ChangeClient();
    void Addclient();
    bool detailsRules();
};

