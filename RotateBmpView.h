
// RotateBmpView.h : CRotateBmpView ��Ľӿ�
//

#pragma once


class CRotateBmpView : public CView
{
protected: // �������л�����
	CRotateBmpView();
	DECLARE_DYNCREATE(CRotateBmpView)

// ����
public:
	CRotateBmpDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL PreTranslateMessage(MSG* pMsg);
protected:

// ʵ��
public:
	virtual ~CRotateBmpView();
	void CRotateBmpView::DrawBmp(CDC *pDC, CString filepath, double angle);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // RotateBmpView.cpp �еĵ��԰汾
inline CRotateBmpDoc* CRotateBmpView::GetDocument() const
   { return reinterpret_cast<CRotateBmpDoc*>(m_pDocument); }
#endif

