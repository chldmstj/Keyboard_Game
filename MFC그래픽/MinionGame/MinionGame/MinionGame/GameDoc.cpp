// GameDoc.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MinionGame.h"
#include "GameDoc.h"


// GameDoc

IMPLEMENT_DYNCREATE(GameDoc, CDocument)

GameDoc::GameDoc()
{
}

BOOL GameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

GameDoc::~GameDoc()
{
}


BEGIN_MESSAGE_MAP(GameDoc, CDocument)
END_MESSAGE_MAP()


// GameDoc �����Դϴ�.

#ifdef _DEBUG
void GameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void GameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// GameDoc serialization�Դϴ�.

void GameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}
#endif


// GameDoc ����Դϴ�.
