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
public:
	CFormulaireClient m_fenetreFormulaire;

public:
	CGlobalOneApp(HINSTANCE hInst, HWND hWnd, wstring sConnect);

	CAdoDatabase* getDatabase() { return &m_database; }

	
};
HINSTANCE GetInstance();
