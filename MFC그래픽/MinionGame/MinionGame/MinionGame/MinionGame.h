
// MinionGame.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMinionGameApp:
// �� Ŭ������ ������ ���ؼ��� MinionGame.cpp�� �����Ͻʽÿ�.
//

class CMinionGameApp : public CWinApp
{
public:
	CMinionGameApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMinionGameApp theApp;