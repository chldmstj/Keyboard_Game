// GameDoc.cpp : 구현 파일입니다.
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


// GameDoc 진단입니다.

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
// GameDoc serialization입니다.

void GameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}
#endif


// GameDoc 명령입니다.
