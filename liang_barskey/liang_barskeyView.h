
// liang_barskeyView.h : Cliang_barskeyView ��Ľӿ�
//

#pragma once


class Cliang_barskeyView : public CView
{
protected: // �������л�����
	Cliang_barskeyView();
	DECLARE_DYNCREATE(Cliang_barskeyView)

// ����
public:
	Cliang_barskeyDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~Cliang_barskeyView();
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

#ifndef _DEBUG  // liang_barskeyView.cpp �еĵ��԰汾
inline Cliang_barskeyDoc* Cliang_barskeyView::GetDocument() const
   { return reinterpret_cast<Cliang_barskeyDoc*>(m_pDocument); }
#endif

