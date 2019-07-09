// HowToPlayDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MinionGame.h"
#include "HowToPlayDlg.h"
#include "afxdialogex.h"


// HowToPlayDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(HowToPlayDlg, CDialogEx)

HowToPlayDlg::HowToPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HOWTOPLAY, pParent)
{

}

HowToPlayDlg::~HowToPlayDlg()
{
}

void HowToPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_GRU, m_ctlPicGru);
}


BEGIN_MESSAGE_MAP(HowToPlayDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// HowToPlayDlg �޽��� ó�����Դϴ�.

//ȭ�������� ����!--------------------------
BOOL HowToPlayDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	//----- ����� â���� -------
	int cx = (GetSystemMetrics(SM_CXSCREEN) / 2 - 435);
	int cy = (GetSystemMetrics(SM_CYSCREEN) / 2 - 525 / 2);  //â�� ����� ��ġ��Ű�� ����

	//----ȭ��ũ������----
	MoveWindow(cx, cy, 870, 525);//��ġx,��ġy,ũ��x,ũ��y
	return TRUE;
}

void HowToPlayDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	
	//----���ȭ�� ��������!----
	HBITMAP hbit;
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_GRU));
	m_ctlPicGru.SetBitmap(hbit);  //�׷����
	//-------------------------
}
