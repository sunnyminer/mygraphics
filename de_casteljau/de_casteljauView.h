
// de_casteljauView.h : Cde_casteljauView ��Ľӿ�
//

#pragma once


class Cde_casteljauView : public CView
{
protected: // �������л�����
	Cde_casteljauView();
	DECLARE_DYNCREATE(Cde_casteljauView)

// ����
public:
	Cde_casteljauDoc* GetDocument() const;

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
	virtual ~Cde_casteljauView();
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

#ifndef _DEBUG  // de_casteljauView.cpp �еĵ��԰汾
inline Cde_casteljauDoc* Cde_casteljauView::GetDocument() const
   { return reinterpret_cast<Cde_casteljauDoc*>(m_pDocument); }
#endif

