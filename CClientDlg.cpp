#include "CClientDlg.h"
#include "resource.h"
#include ".\..\LibOutils\AdoDatabase.h"
#include "GlobalOneApp.h"
#include <string> 
#include "CEditBox.h"
#include ".\..\LibOutils\Timeutils.h"
#include "Tools.h"


extern CGlobalOneApp*theApp;



DLGPROC CClientDlg::dialog_procedure(UINT msg, WPARAM wParam, LPARAM lParam)
{
	int wmId = NULL, wmEvent = NULL;

	switch (msg)
	{
	case WM_INITDIALOG:
		initDialog();
		break;
	case WM_DESTROY:
		EndDialog(getwnd(), 1);
		return 0;
		break;

	case WM_COMMAND:
		if (!lParam)
		{
			wmId = HIWORD(wParam);
			wmEvent = LOWORD(wParam);
		}
		else
		{
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
		}

		switch (wmId) 
		{
		case IDCANCEL:
			EndDialog(getwnd(), 1);
			break;
		case IDC_ADDBUTTON:
			Addclient();
			break;
		case IDC_LISTBOXCLIENT:
			switch (wmEvent)
			{
			case LBN_SELCHANGE:
				ChangeClient();
				break;
			}
			break;
		case IDC_EDITNOM:
		case IDC_EDITPRENOM:
			switch (wmEvent)
			{
			case EN_CHANGE:
				//applyrules();
				break;
			}
			break;

		}
		break;

	}
	return 0;
}
void CClientDlg::initDialog()
{
	auto LeDialog = getwnd();
	HWND Litem = GetDlgItem(LeDialog, IDC_LISTBOXCLIENT);
	m_ListBoxClient.SethWnd(Litem);
	m_EditNom.SethWnd(GetDlgItem(getwnd(), IDC_EDITNOM));
	m_EditPrenom.SethWnd(GetDlgItem(getwnd(), IDC_EDITPRENOM));
	m_EditAdresse.SethWnd(GetDlgItem(getwnd(), IDC_EDITADRESS));
	m_EditBirthday.SethWnd(GetDlgItem(getwnd(), IDC_EDITBIRTHDAY));
	m_EditCP.SethWnd(GetDlgItem(getwnd(), IDC_EDITCP));
	m_EditVille.SethWnd(GetDlgItem(getwnd(), IDC_EDITTOWN));
	m_EditMail.SethWnd(GetDlgItem(getwnd(), IDC_EDITMAIL));
	m_EditPhone.SethWnd(GetDlgItem(getwnd(), IDC_EDITTEL));
	m_EditMobile.SethWnd(GetDlgItem(getwnd(), IDC_EDITMOB));
	m_AddButton.SethWnd(GetDlgItem(getwnd(), IDC_ADDBUTTON));
	m_AddButton.Enable(true);

	CTable* pTable = theApp->getDatabase()->OpenRecordSetOnQuery(L"SELECT * FROM \"Clients\"", 0);
	while (!pTable->m_pRecordset->adoEOF)
	{
		auto szNom = pTable->GetStringFieldValue(L"""Nom""") + L" " + pTable->GetStringFieldValue(L"""Prenom""");
		m_ListBoxClient.AddString(szNom);
		pTable->MoveNext();
	}

}
void CClientDlg::ChangeClient()
{

	m_bRules = false;
	wstring szRequest;
	auto iCur = m_ListBoxClient.GetCurSel();
	auto szNom = m_ListBoxClient.GetText(iCur);

	szRequest = L"SELECT * FROM \"Clients\"  WHERE CONCAT(\"Nom\",' ', \"Prenom\") = '" + szNom + L"'";

	CTable*pRecord = theApp->getDatabase()->OpenRecordSetOnQuery(szRequest, 0);

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
void CClientDlg::Addclient() {
	
	if (detailsRules())
	{
		wstring szRequest;
		szRequest = L"SELECT \"N°\" FROM \"Clients\"  WHERE CONCAT(\"Nom\",' ', \"Prenom\") = '" + m_EditNom.GetText()+L" "+ m_EditPrenom.GetText() + L"'";
		CTable* pRecord = theApp->getDatabase()->OpenRecordSetOnQuery(szRequest, 0);
		if (pRecord->IsEOF())
		{
			MessageBox(getwnd(), L"Ca n'existe pas", L"Titi", MB_OK);
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
			m_ListBoxClient.AddString(sZlist);
			auto iNum = m_ListBoxClient.FindString(sZlist);
			m_ListBoxClient.SetCursel(iNum);
		}
		else
		{
			MessageBox(getwnd(), L"Cela existe", L"Titi", MB_OK);
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
	else MessageBox(getwnd(), L"Error", L"Error", MB_OK);
}

void CClientDlg::applyrules() {
	if (!m_bRules) return;

	wstring concat = m_EditNom.GetText() + wstring(L" ") + m_EditPrenom.GetText();

	if (m_EditNom.GetText().empty() || m_ListBoxClient.FindString(concat)>=0)
	{
		m_AddButton.Enable(false);
	}
	else
	{
		m_AddButton.Enable(true);
	}
}

bool CClientDlg::detailsRules() {
	if (m_EditAdresse.GetText().empty())return false;
	if (!CTools::IsNumericPhone(m_EditPhone.GetText()) || !CTools::IsNumericPhone(m_EditMobile.GetText())) return false;
	if (!CTools::IsNumericCodePostal(m_EditCP.GetText())) return false; 
	if (m_EditVille.GetText().empty())return false;
	if (!CTools::IsDate(m_EditBirthday.GetText())) return false;
	return true;
}
