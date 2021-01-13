#include "CFormulaireClient.h"
#include "GlobalOneApp.h"

extern CGlobalOneApp* theApp;


LRESULT CFormulaireClient::virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
    {
        auto wp = LOWORD(wParam);
        switch(HIWORD(wParam))
        {
        case LBN_SELCHANGE:
            ChangeClient();
            break;
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDc = BeginPaint(hWnd, &ps); // Handle sur device control
        RECT r;
        GetWindowRect(hWnd, &r);
        r.right -= r.left;
        r.left = 0;
        r.bottom -= r.top;
        r.top = 0;

        auto color = CreateSolidBrush(RGB(243, 243, 243));
        FillRect(hDc, &r, color);
        EndPaint(hWnd, &ps);

        break;
    }
    case WM_CREATE:
    {

        m_StaticNom.Create(GetInstance(), WS_CHILD, hWnd, 149, 78, 277, 40);
        m_StaticNom.SetText(L"Nom");
        ShowWindow(m_StaticNom.GethWnd(), SW_SHOW);
        m_EditNom.Create(GetInstance(), WS_CHILD | WS_BORDER, hWnd, 216, 78, 277, 40);
        ShowWindow(m_EditNom.GethWnd(), SW_SHOW);

        m_StaticPrenom.Create(GetInstance(), WS_CHILD, hWnd, 603, 78, 277, 40);
        m_StaticPrenom.SetText(L"Prénom");
        ShowWindow(m_StaticPrenom.GethWnd(), SW_SHOW);
        m_EditPrenom.Create(GetInstance(), WS_CHILD | WS_BORDER, hWnd, 683, 78, 277, 40);
        ShowWindow(m_EditPrenom.GethWnd(), SW_SHOW);

        m_StaticAdresse.Create(GetInstance(), WS_CHILD, hWnd, 149, 128, 277, 40);
        m_StaticAdresse.SetText(L"Adresse");
        ShowWindow(m_StaticAdresse.GethWnd(), SW_SHOW);
        m_EditAdresse.Create(GetInstance(), WS_CHILD | WS_BORDER, hWnd, 216, 128, 744, 40);
        ShowWindow(m_EditAdresse.GethWnd(), SW_SHOW);

        m_StaticCP.Create(GetInstance(), WS_CHILD, hWnd, 149, 182, 277, 40);
        m_StaticCP.SetText(L"CP");
        ShowWindow(m_StaticCP.GethWnd(), SW_SHOW);
        m_EditCP.Create(GetInstance(), WS_CHILD | WS_BORDER, hWnd, 216, 182, 277, 40);
        ShowWindow(m_EditCP.GethWnd(), SW_SHOW);

        m_StaticPhone.Create(GetInstance(), WS_CHILD, hWnd, 149, 234, 277, 40);
        m_StaticPhone.SetText(L"Phone");
        ShowWindow(m_StaticPhone.GethWnd(), SW_SHOW);
        m_EditPhone.Create(GetInstance(), WS_CHILD | WS_BORDER, hWnd, 216, 234, 277, 40);
        ShowWindow(m_EditPhone.GethWnd(), SW_SHOW);

        m_StatictMail.Create(GetInstance(), WS_CHILD, hWnd, 149, 286, 277, 40);
        m_StatictMail.SetText(L"Mail");
        ShowWindow(m_StatictMail.GethWnd(), SW_SHOW);
        m_EditMail.Create(GetInstance(), WS_CHILD | WS_BORDER, hWnd, 216, 286, 277, 40);
        ShowWindow(m_EditMail.GethWnd(), SW_SHOW);

        m_StaticMobile.Create(GetInstance(), WS_CHILD, hWnd, 603, 234, 277, 40);
        m_StaticMobile.SetText(L"Mobile");
        ShowWindow(m_StaticMobile.GethWnd(), SW_SHOW);
        m_EditMobile.Create(GetInstance(), WS_CHILD | WS_BORDER, hWnd, 683, 234, 277, 40);
        ShowWindow(m_EditMobile.GethWnd(), SW_SHOW);

        m_StaticBirthday.Create(GetInstance(), WS_CHILD, hWnd, 603, 286, 277, 40);
        m_StaticBirthday.SetText(L"Birthday");
        ShowWindow(m_StaticBirthday.GethWnd(), SW_SHOW);
        m_EditBirthday.Create(GetInstance(), WS_CHILD | WS_BORDER, hWnd, 683, 286, 277, 40);
        ShowWindow(m_EditBirthday.GethWnd(), SW_SHOW);

        m_CustomerList.Create(GetInstance(), WS_CHILD | WS_BORDER | LBS_NOTIFY | LBS_SORT | WS_VSCROLL | LBS_HASSTRINGS, hWnd, 1013, 78, 473, 680);
        ShowWindow(m_CustomerList.GethWnd(), SW_SHOW);

        m_StaticVille.Create(GetInstance(), WS_CHILD, hWnd, 603, 182, 277, 40);
        m_StaticVille.SetText(L"Ville");
        ShowWindow(m_StaticVille.GethWnd(), SW_SHOW);
        m_EditVille.Create(GetInstance(), WS_CHILD | WS_BORDER, hWnd, 683, 182, 277, 40);
        ShowWindow(m_EditVille.GethWnd(), SW_SHOW);

        m_ButtonSave.Create(GetInstance(), WS_CHILD | BS_BITMAP, hWnd, 513, 393, 64, 64);
        HANDLE handleBitmap = LoadImage(NULL, L".\\img\\ButtonSave.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        SendMessage(m_ButtonSave.GethWnd(), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)handleBitmap);
        ShowWindow(m_ButtonSave.GethWnd(), SW_SHOW);


        CTable* pTable = theApp->getDatabase()->OpenRecordSetOnQuery(L"SELECT * FROM \"Clients\"", 0);
        while (!pTable->m_pRecordset->adoEOF)
        {
            auto szNom = pTable->GetStringFieldValue(L"""Nom""") + L" " + pTable->GetStringFieldValue(L"""Prenom""");
            m_CustomerList.AddString(szNom);
            pTable->MoveNext();
        }
    }
		break;

    default:
		break;
	}
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
void CFormulaireClient::ChangeClient()
{

    m_bRules = false;
    wstring szRequest;
    auto iCur = m_CustomerList.GetCurSel();
    auto szNom = m_CustomerList.GetText(iCur);

    szRequest = L"SELECT * FROM \"Clients\"  WHERE CONCAT(\"Nom\",' ', \"Prenom\") = '" + szNom + L"'";

    CTable* pRecord = theApp->getDatabase()->OpenRecordSetOnQuery(szRequest, 0);

    auto szName = pRecord->GetStringFieldValue(L"""Nom""");
    m_EditNom.SetText(szName);

    auto sz = pRecord->GetStringFieldValue(L"""Prenom""");
    m_EditPrenom.SetText(sz);

    auto dBirthday = pRecord->GetDateFieldValue(3);
    m_EditBirthday.SetText(CTimeUtils::TimetToString(dBirthday));

    auto szCP = pRecord->GetStringFieldValue(L"""Code_postal""");
    m_EditCP.SetText(szCP);

    auto szAdresse = pRecord->GetStringFieldValue(L"""Adresse""");
    m_EditAdresse.SetText(szAdresse);

    auto szVille = pRecord->GetStringFieldValue(L"""Ville""");
    m_EditVille.SetText(szVille);

    auto szMail = pRecord->GetStringFieldValue(L"""E_mail""");
    m_EditMail.SetText(szMail);

    auto szPhone = pRecord->GetStringFieldValue(L"""Telephone_fixe""");
    m_EditPhone.SetText(szPhone);

    auto szMobile = pRecord->GetStringFieldValue(L"""Telephone_portable""");
    m_EditMobile.SetText(szMobile);

    m_bRules = true;
    //applyrules();
}

