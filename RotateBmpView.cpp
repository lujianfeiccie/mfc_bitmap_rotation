
// RotateBmpView.cpp : CRotateBmpView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CRotateBmpView 构造/析构

CRotateBmpView::CRotateBmpView()
{
	// TODO: 在此处添加构造代码

}

CRotateBmpView::~CRotateBmpView()
{
}

BOOL CRotateBmpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CRotateBmpView 绘制
 void CRotateBmpView::DrawBmp(CDC *pDC, CString filepath, double angle)

{
double SrcWidth = 0;//图片宽度
double SrcHeight = 0;//图片高度

CFile   file;                //用于读取BMP文件 
BITMAPFILEHEADER   bfhHeader;//bmp文件头 

BITMAPINFOHEADER   bmiHeader;   //bmp格式头   

 

LPBITMAPINFO   lpBitmapInfo;         //bmp格式具体信息 

 

if(!file.Open(filepath,CFile::modeRead)) 

return;                                                             //打开文件 

file.Read(&bfhHeader,sizeof(BITMAPFILEHEADER));//读取文件头 

if(bfhHeader.bfType!=0x4d42)                     //判断是否是BM 

return; 

if(bfhHeader.bfSize!=file.GetLength()) 

return; 

 

if(file.Read((LPSTR)&bmiHeader,sizeof(bmiHeader)) != sizeof(bmiHeader)) 

return;

 

SrcHeight   =   bmiHeader.biHeight;	//得到高度和宽度 

SrcWidth    =   bmiHeader.biWidth; 

file.SeekToBegin(); 

file.Read(&bfhHeader,sizeof(BITMAPFILEHEADER));   

UINT   uBmpInfoLen=(UINT)   bfhHeader.bfOffBits-sizeof(BITMAPFILEHEADER); 

lpBitmapInfo=(LPBITMAPINFO)   new   BYTE[uBmpInfoLen]; 

file.Read((LPVOID)   lpBitmapInfo,uBmpInfoLen); 

if((*   (LPDWORD)(lpBitmapInfo))!=sizeof(BITMAPINFOHEADER)) 

return; 

DWORD   dwBitlen=bfhHeader.bfSize   -   bfhHeader.bfOffBits; 

LPVOID   lpSrcBits=new   BYTE[dwBitlen];	//将数据读入lpSrcBits数组 

file.Read(lpSrcBits,dwBitlen); 

file.Close();	//关闭文件 

 

 

CDC bmpDC;

bmpDC.CreateCompatibleDC(pDC);

CBitmap bmp;

bmp.CreateCompatibleBitmap(pDC,SrcWidth,SrcHeight);

bmpDC.SelectObject(&bmp);

//该函数将DIB中矩形区域内像素使用的颜色数据拷贝到指定的目标矩形中
StretchDIBits(bmpDC.m_hDC,//指向目标设备环境的句柄。
	0,//指定目标矩形左上角位置的X轴坐标，按逻辑单位来表示坐标。
	0,//指定目标矩形左上角的Y轴坐标，按逻辑单位表示坐标。
	SrcWidth,//指定目标矩形的宽度。
	SrcHeight,//指定目标矩形的高度。
	0,//指定DIB中源矩形（左上角）的X轴坐标，坐标以像素点表示。
	0,//指定DIB中源矩形（左上角）的Y轴坐标，坐标以像素点表示。
	bmiHeader.biWidth,//按像素点指定DIB中源矩形的宽度。
	bmiHeader.biHeight,//按像素点指定DIB中源矩形的高度。
	lpSrcBits,//指向DIB位的指针，这些位的值按字节类型数组存储，有关更多的信息，参考下面的备注一节。
	lpBitmapInfo,//指向BITMAPINFO结构的指针，该结构包含有关DIB方面的信息。
	DIB_RGB_COLORS,MERGECOPY); 

//StretchDIBits不能去掉。将图片贴到bmpDC中
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

HDC dcDst;//旋转后的内存设备环境 

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
			BitBlt(dcDst,//指向目标设备环境的句柄。
				j,//指定目标矩形区域左上角的X轴逻辑坐标。
				i,//指定目标矩形区域左上角的Y轴逻辑坐标。
				1,//指定源在目标矩形区域的逻辑宽度。
				1,//指定源在目标矩形区域的逻辑高度。
				bmpDC.m_hDC, //指向源设备环境的句柄。
				(int)srcX,//指定源矩形区域左上角的X轴逻辑坐标。
				(int)srcY,//指定源矩形区域左上角的Y轴逻辑坐标。
				SRCCOPY); //将源矩形区域直接拷贝到目标矩形区域。
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

TransparentBlt(	pDC->m_hDC,//指向源设备环境的句柄。
	rtHour.left,//指定目标矩形左上角的X轴坐标，坐标以逻辑单位表示。
	rtHour.top, //指定目标矩形左上角的Y轴坐标，坐标以逻辑单位表示。
	rtHour.Width(), //指定目标矩形的宽度。
	rtHour.Height(),//指定目标矩形的高度。
	dcDst,//指向目标设备环境的句柄。
	0,//指定源矩形（左上角）的X轴坐标，坐标以逻辑单位表示。
	0,//指定源矩形（左上角）的Y轴坐标，坐标以逻辑单位表示。
	rtHour.Width(),//指定源矩形的宽度。
	rtHour.Height(),//指定源矩形的高度。
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
	// TODO: 在此处为本机数据添加绘制代码
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


// CRotateBmpView 诊断

#ifdef _DEBUG
void CRotateBmpView::AssertValid() const
{
	CView::AssertValid();
}

void CRotateBmpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRotateBmpDoc* CRotateBmpView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRotateBmpDoc)));
	return (CRotateBmpDoc*)m_pDocument;
}
#endif //_DEBUG


// CRotateBmpView 消息处理程序
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