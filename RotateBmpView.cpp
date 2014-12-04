
// RotateBmpView.cpp : CRotateBmpView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "RotateBmp.h"
#endif

#include <math.h>
#include "RotateBmpDoc.h"
#include "RotateBmpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRotateBmpView

IMPLEMENT_DYNCREATE(CRotateBmpView, CView)

BEGIN_MESSAGE_MAP(CRotateBmpView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CRotateBmpView ����/����

CRotateBmpView::CRotateBmpView()
{
	// TODO: �ڴ˴���ӹ������

}

CRotateBmpView::~CRotateBmpView()
{
}

BOOL CRotateBmpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CRotateBmpView ����
 void CRotateBmpView::DrawBmp(CDC *pDC, CString filepath, double angle)

{
double SrcWidth = 0;//ͼƬ���
double SrcHeight = 0;//ͼƬ�߶�

CFile   file;                //���ڶ�ȡBMP�ļ� 
BITMAPFILEHEADER   bfhHeader;//bmp�ļ�ͷ 

BITMAPINFOHEADER   bmiHeader;   //bmp��ʽͷ   

 

LPBITMAPINFO   lpBitmapInfo;         //bmp��ʽ������Ϣ 

 

if(!file.Open(filepath,CFile::modeRead)) 

return;                                                             //���ļ� 

file.Read(&bfhHeader,sizeof(BITMAPFILEHEADER));//��ȡ�ļ�ͷ 

if(bfhHeader.bfType!=0x4d42)                     //�ж��Ƿ���BM 

return; 

if(bfhHeader.bfSize!=file.GetLength()) 

return; 

 

if(file.Read((LPSTR)&bmiHeader,sizeof(bmiHeader)) != sizeof(bmiHeader)) 

return;

 

SrcHeight   =   bmiHeader.biHeight;	//�õ��߶ȺͿ�� 

SrcWidth    =   bmiHeader.biWidth; 

file.SeekToBegin(); 

file.Read(&bfhHeader,sizeof(BITMAPFILEHEADER));   

UINT   uBmpInfoLen=(UINT)   bfhHeader.bfOffBits-sizeof(BITMAPFILEHEADER); 

lpBitmapInfo=(LPBITMAPINFO)   new   BYTE[uBmpInfoLen]; 

file.Read((LPVOID)   lpBitmapInfo,uBmpInfoLen); 

if((*   (LPDWORD)(lpBitmapInfo))!=sizeof(BITMAPINFOHEADER)) 

return; 

DWORD   dwBitlen=bfhHeader.bfSize   -   bfhHeader.bfOffBits; 

LPVOID   lpSrcBits=new   BYTE[dwBitlen];	//�����ݶ���lpSrcBits���� 

file.Read(lpSrcBits,dwBitlen); 

file.Close();	//�ر��ļ� 

 

 

CDC bmpDC;

bmpDC.CreateCompatibleDC(pDC);

CBitmap bmp;

bmp.CreateCompatibleBitmap(pDC,SrcWidth,SrcHeight);

bmpDC.SelectObject(&bmp);

//�ú�����DIB�о�������������ʹ�õ���ɫ���ݿ�����ָ����Ŀ�������
StretchDIBits(bmpDC.m_hDC,//ָ��Ŀ���豸�����ľ����
	0,//ָ��Ŀ��������Ͻ�λ�õ�X�����꣬���߼���λ����ʾ���ꡣ
	0,//ָ��Ŀ��������Ͻǵ�Y�����꣬���߼���λ��ʾ���ꡣ
	SrcWidth,//ָ��Ŀ����εĿ�ȡ�
	SrcHeight,//ָ��Ŀ����εĸ߶ȡ�
	0,//ָ��DIB��Դ���Σ����Ͻǣ���X�����꣬���������ص��ʾ��
	0,//ָ��DIB��Դ���Σ����Ͻǣ���Y�����꣬���������ص��ʾ��
	bmiHeader.biWidth,//�����ص�ָ��DIB��Դ���εĿ�ȡ�
	bmiHeader.biHeight,//�����ص�ָ��DIB��Դ���εĸ߶ȡ�
	lpSrcBits,//ָ��DIBλ��ָ�룬��Щλ��ֵ���ֽ���������洢���йظ������Ϣ���ο�����ı�עһ�ڡ�
	lpBitmapInfo,//ָ��BITMAPINFO�ṹ��ָ�룬�ýṹ�����й�DIB�������Ϣ��
	DIB_RGB_COLORS,MERGECOPY); 

//StretchDIBits����ȥ������ͼƬ����bmpDC��
double x1,x2,x3; 

double y1,y2,y3; 

double maxWidth,maxHeight,minWidth,minHeight; 

double srcX,srcY; 

double sinA,cosA; 

double DstWidth; 

double DstHeight; 

angle=angle/ 180.0 * 3.14159265;

sinA = sin(angle); 

cosA = cos(angle); 

 

x1 = SrcWidth * cosA;

y1 = SrcWidth * sinA;

x2 = SrcWidth * cosA - SrcHeight * sinA;

y2 = SrcWidth * sinA + SrcHeight * cosA;

x3 = -SrcHeight *sinA;

y3 = SrcHeight  *cosA;

minWidth = x3> (x1> x2?x2:x1)?(x1> x2?x2:x1):x3; 

minWidth = minWidth> 0?0:minWidth; 

minHeight = y3> (y1> y2?y2:y1)?(y1> y2?y2:y1):y3; 

minHeight = minHeight> 0?0:minHeight; 

maxWidth = x3> (x1> x2?x1:x2)?x3:(x1> x2?x1:x2); 

maxWidth = maxWidth> 0?maxWidth:0; 

maxHeight = y3> (y1> y2?y1:y2)?y3:(y1> y2?y1:y2); 

maxHeight = maxHeight> 0?maxHeight:0; 

DstWidth = abs(maxWidth - minWidth)+1; 

DstHeight =abs(maxHeight - minHeight)+1; 

HDC dcDst;//��ת����ڴ��豸���� 

HBITMAP newBitmap; 

dcDst = CreateCompatibleDC(pDC->m_hDC); 

newBitmap = CreateCompatibleBitmap(pDC->m_hDC,(int)DstWidth,(int)DstHeight); 

SelectObject(dcDst,newBitmap);

::FillRect(dcDst,CRect(0,0,DstWidth,DstHeight),CBrush(RGB(255,255,255)));

int i = 0;

int j = 0;

for(i = 0; i < DstHeight; i++) 
{ 
	for(j = 0; j  <  DstWidth; j++) 
	{ 

		srcX = (j + minWidth) * cosA + (i + minHeight) * sinA; 

		srcY = (i + minHeight) * cosA - (j + minWidth) * sinA; 

		if((srcX >= 0) && (srcX <= SrcWidth) &&(srcY >=  0) && (srcY <= SrcHeight)) 
		{ 
			BitBlt(dcDst,//ָ��Ŀ���豸�����ľ����
				j,//ָ��Ŀ������������Ͻǵ�X���߼����ꡣ
				i,//ָ��Ŀ������������Ͻǵ�Y���߼����ꡣ
				1,//ָ��Դ��Ŀ�����������߼���ȡ�
				1,//ָ��Դ��Ŀ�����������߼��߶ȡ�
				bmpDC.m_hDC, //ָ��Դ�豸�����ľ����
				(int)srcX,//ָ��Դ�����������Ͻǵ�X���߼����ꡣ
				(int)srcY,//ָ��Դ�����������Ͻǵ�Y���߼����ꡣ
				SRCCOPY); //��Դ��������ֱ�ӿ�����Ŀ���������
		} 
	 } 
} 

CPoint pCenter;
pCenter.x = 300;
pCenter.y =300;

CRect rtHour;

rtHour.left=pCenter.x-DstWidth/2;

rtHour.right=rtHour.left+DstWidth;

rtHour.top=pCenter.y-DstHeight/2;

rtHour.bottom=rtHour.top+DstHeight;

TransparentBlt(	pDC->m_hDC,//ָ��Դ�豸�����ľ����
	rtHour.left,//ָ��Ŀ��������Ͻǵ�X�����꣬�������߼���λ��ʾ��
	rtHour.top, //ָ��Ŀ��������Ͻǵ�Y�����꣬�������߼���λ��ʾ��
	rtHour.Width(), //ָ��Ŀ����εĿ�ȡ�
	rtHour.Height(),//ָ��Ŀ����εĸ߶ȡ�
	dcDst,//ָ��Ŀ���豸�����ľ����
	0,//ָ��Դ���Σ����Ͻǣ���X�����꣬�������߼���λ��ʾ��
	0,//ָ��Դ���Σ����Ͻǣ���Y�����꣬�������߼���λ��ʾ��
	rtHour.Width(),//ָ��Դ���εĿ�ȡ�
	rtHour.Height(),//ָ��Դ���εĸ߶ȡ�
	RGB(255,255,255)
	);

delete[] lpBitmapInfo;

delete[] lpSrcBits;

lpBitmapInfo = NULL;

lpSrcBits = NULL;

::ZeroMemory(&bfhHeader,sizeof(bfhHeader));

::ZeroMemory(&bmiHeader,sizeof(bmiHeader));

::ZeroMemory(&lpBitmapInfo,sizeof(lpBitmapInfo));

bmpDC.DeleteDC();

bmp.DeleteObject();

DeleteDC(dcDst); 

DeleteObject(newBitmap); 
}

static int degree = 0;
void CRotateBmpView::OnDraw(CDC* pDC)
{
	CRotateBmpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawBmp(pDC,L"F:\\RotateBmp\\RotateBmp\\RotateBmp\\steering_wheel.bmp",degree*12);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CRotateBmpView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRotateBmpView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRotateBmpView ���

#ifdef _DEBUG
void CRotateBmpView::AssertValid() const
{
	CView::AssertValid();
}

void CRotateBmpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRotateBmpDoc* CRotateBmpView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRotateBmpDoc)));
	return (CRotateBmpDoc*)m_pDocument;
}
#endif //_DEBUG


// CRotateBmpView ��Ϣ�������
BOOL CRotateBmpView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYDOWN)
	{
		switch( pMsg->wParam )
		{
			case VK_LEFT:
				{
						--degree;
						Invalidate(FALSE);
				}
			break;
			case VK_RIGHT:
				{
						++degree;
						Invalidate(FALSE);
				}
			break;
		}
	}
	else
	if (pMsg->message==WM_KEYUP)
	{
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 
	return CWnd::PreTranslateMessage(pMsg); 
}