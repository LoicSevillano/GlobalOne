#pragma once
#include <windows.h>
#include ".\..\LibOutils\AdoDatabase.h"
#include "CBandeau.h"
#include "CFormulaireClient.h"

class CGlobalOneApp
{
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	CAdoDatabase m_database;
	CBandeau m_fenetreMenu;

	CFormulaireClient m_fenetreClient;
	CFormulaireClient m_fenetreAccueil;
	CFormulaire* m_pFormulaire;

public:
	CGlobalOneApp(HINSTANCE hInst, HWND hWnd, wstring sConnect);

	CAdoDatabase* getDatabase() { return &m_database; }

	CFormulaire* GetFormulaire()
	{
		return m_pFormulaire;
	}

	CFormulaireClient* GetFenetreAccueil()
	{
		return &m_fenetreAccueil;
	}

	void setFormulaire(CFormulaire* hF) 
	{
		m_pFormulaire = hF;
	}

	HWND getMainMhwnd()
	{
		return m_hWnd;
	}

};
/*HINSTANCE GetInstance(NULL)()
{
	return GetInstance();
}*/

