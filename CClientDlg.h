#pragma once
#include "CDialog.h"
#include ".\..\LibOutils\CListBox.h"
#include ".\..\LibOutils\CEditBox.h"
#include ".\..\LibOutils\Cbutton.h"

class CClientDlg :
    public CDialog
{
private:
    CListBox m_ListBoxClient;
    CEditBox m_EditNom;
    CEditBox m_EditPrenom;
    CEditBox m_EditBirthday;
    CEditBox m_EditAdresse;
    CEditBox m_EditCP;
    CEditBox m_EditVille;
    CEditBox m_EditMail;
    CEditBox m_EditPhone;
    CEditBox m_EditMobile;
    Cbutton m_AddButton;
    bool m_bRules;
    
    void ChangeClient();

public:
    DLGPROC dialog_procedure(UINT msg, WPARAM wParam, LPARAM lParam);
    void initDialog();
private:
    void Addclient();
    void applyrules();
    bool detailsRules();



    

    
};

