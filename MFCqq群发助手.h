
// MFCqqȺ������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCqqȺ������App: 
// �йش����ʵ�֣������ MFCqqȺ������.cpp
//

class CMFCqqȺ������App : public CWinApp
{
public:
	CMFCqqȺ������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCqqȺ������App theApp;