
// RotateBmpView.h : CRotateBmpView 类的接口
//

#pragma once


class CRotateBmpView : public CView
{
protected: // 仅从序列化创建
	CRotateBmpView();
	DECLARE_DYNCREATE(CRotateBmpView)

// 特性
public:
	CRotateBmpDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL PreTranslateMessage(MSG* pMsg);
protected:

// 实现
public:
	virtual ~CRotateBmpView();
	void CRotateBmpView::DrawBmp(CDC *pDC, CString filepath, double angle);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // RotateBmpView.cpp 中的调试版本
inline CRotateBmpDoc* CRotateBmpView::GetDocument() const
   { return reinterpret_cast<CRotateBmpDoc*>(m_pDocument); }
#endif

