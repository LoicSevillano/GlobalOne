#include "CFormulaireClient.h"
#include "GlobalOneApp.h"
#include "Tools.h"
extern CGlobalOneApp* theApp;


LRESULT CFormulaireClient::virtualFenetreProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_COMMAND:
        {
            WORD wmId, wmEvent;
            if (!lParam)
            {
                wmId = LOWORD(wParam);
                wmEvent = HIWORD(wParam);
            }
            else
            {
                wmId = HIWORD(wParam);
                wmEvent = LOWORD(wParam);
            }

            switch (wmId)
            {
                case LBN_SELCHANGE:
                    ChangeClient();
                    break;
                case BN_CLICKED:
                    Addclient();
                    break;
                default:
                    break;
            }
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


void CFormulaireClient::Addclient() {
	
	if (detailsRules())
	{
		wstring szRequest;
		szRequest = L"SELECT \"N°\" FROM \"Clients\"  WHERE CONCAT(\"Nom\",' ', \"Prenom\") = '" + m_EditNom.GetText()+L" "+ m_EditPrenom.GetText() + L"'";
		CTable* pRecord = theApp->getDatabase()->OpenRecordSetOnQuery(szRequest, 0);
		if (pRecord->IsEOF())
		{
			MessageBox(this->GethWnd(), L"Ca n'existe pas", L"Titi", MB_OK);
			pRecord = theApp->getDatabase()->OpenRecordSetOnQuery(L"SELECT MAX(\"N°\")+1 FROM \"Clients\"", 0);
			auto iMaxPrimary = pRecord->GetFieldValue(0);
			szRequest = L"INSERT INTO \"Clients\" (\"N°\",\"Nom\",\"Prenom\",\"Adresse\",\"Code_postal\", \"Ville\",\"Telephone_fixe\",\"Telephone_portable\",\"E_mail\", \"Date_de_naissance\") VALUES(";
			szRequest += CTools::Format(L"%d,", iMaxPrimary.lVal);
			szRequest += L"'" + CTools::SQLTreatStringField(m_EditNom.GetText()) + L"',";
			szRequest += L"'" + CTools::SQLTreatStringField(m_EditPrenom.GetText()) + L"',";
			szRequest += L"'" + CTools::SQLTreatStringField(m_EditAdresse.GetText()) + L"',";
			szRequest += L"'" + CTools::SQLTreatStringField(m_EditCP.GetText()) + L"',";
			szRequest += L"'" + CTools::SQLTreatStringField(m_EditVille.GetText()) + L"',";
			szRequest += L"'" + CTools::SQLTreatStringField(m_EditPhone.GetText()) + L"',";
			szRequest += L"'" + CTools::SQLTreatStringField(m_EditMobile.GetText()) + L"',";
			szRequest += L"'" + CTools::SQLTreatStringField(m_EditMail.GetText()) + L"',";

			if (!m_EditBirthday.GetText().empty())
				szRequest += L"'" + m_EditBirthday.GetText().substr(6, 4) + L"-" + m_EditBirthday.GetText().substr(3, 2) + L"-" + m_EditBirthday.GetText().substr(0, 2) + L"')";
			else
				szRequest += L"NULL)";
			theApp->getDatabase()->OpenRecordSetOnQuery(szRequest, 0);
			auto sZlist = m_EditNom.GetText() + L" " + m_EditPrenom.GetText();
            m_CustomerList.AddString(sZlist);
			auto iNum = m_CustomerList.FindString(sZlist);
            m_CustomerList.SetCursel(iNum);
		}
		else
		{
			MessageBox(GethWnd(), L"Cela existe", L"Titi", MB_OK);
			szRequest = L"UPDATE \"Clients\"";
			szRequest += L" SET \"Nom\"='" + CTools::SQLTreatStringField(m_EditNom.GetText()) + L"'";
			szRequest += L" , \"Prenom\"='" + CTools::SQLTreatStringField(m_EditPrenom.GetText()) + L"'";
			szRequest += L" , \"Adresse\"='" + CTools::SQLTreatStringField(m_EditAdresse.GetText()) + L"'";
			szRequest += L" , \"Code_postal\"='" + CTools::SQLTreatStringField(m_EditCP.GetText()) + L"'";
			szRequest += L" , \"Ville\"='" + CTools::SQLTreatStringField(m_EditVille.GetText()) + L"'";
			szRequest += L" , \"Telephone_fixe\"='" + CTools::SQLTreatStringField(m_EditPhone.GetText()) + L"'";
			szRequest += L" , \"Telephone_portable\"='" + CTools::SQLTreatStringField(m_EditMobile.GetText()) + L"'";
			szRequest += L" , \"E_mail\"='" + CTools::SQLTreatStringField(m_EditMail.GetText()) + L"'";


			if (!m_EditBirthday.GetText().empty())
				szRequest += L" , \"Date_de_naissance\"='" + m_EditBirthday.GetText().substr(6, 4) + L"-" + m_EditBirthday.GetText().substr(3, 2) + L"-" + m_EditBirthday.GetText().substr(0, 2) + L"'";
			else
				szRequest += L" , \"Date_de_naissance\"=NULL";
			szRequest += L"  WHERE \"N°\"= " + CTools::Format(L"%d",pRecord->GetIntFieldValue(L"N°"));
			theApp->getDatabase()->OpenRecordSetOnQuery(szRequest, 0);
		}

	}
	else MessageBox(GethWnd(), L"Error", L"Error", MB_OK);
}
bool CFormulaireClient::detailsRules()
{
    if (m_EditAdresse.GetText().empty())return false;
    if (!CTools::IsNumericPhone(m_EditPhone.GetText()) || !CTools::IsNumericPhone(m_EditMobile.GetText())) return false;
    if (!CTools::IsNumericCodePostal(m_EditCP.GetText())) return false;
    if (m_EditVille.GetText().empty())return false;
    if (!CTools::IsDate(m_EditBirthday.GetText())) return false;
    return true;
}
