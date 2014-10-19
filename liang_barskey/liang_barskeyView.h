
// liang_barskeyView.h : Cliang_barskeyView 类的接口
//

#pragma once


class Cliang_barskeyView : public CView
{
protected: // 仅从序列化创建
	Cliang_barskeyView();
	DECLARE_DYNCREATE(Cliang_barskeyView)

// 特性
public:
	Cliang_barskeyDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Cliang_barskeyView();
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

#ifndef _DEBUG  // liang_barskeyView.cpp 中的调试版本
inline Cliang_barskeyDoc* Cliang_barskeyView::GetDocument() const
   { return reinterpret_cast<Cliang_barskeyDoc*>(m_pDocument); }
#endif

