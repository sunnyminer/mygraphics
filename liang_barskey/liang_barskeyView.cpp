
// liang_barskeyView.cpp : Cliang_barskeyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "liang_barskey.h"
#endif

#include "liang_barskeyDoc.h"
#include "liang_barskeyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cliang_barskeyView

IMPLEMENT_DYNCREATE(Cliang_barskeyView, CView)

BEGIN_MESSAGE_MAP(Cliang_barskeyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cliang_barskeyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cliang_barskeyView 构造/析构

Cliang_barskeyView::Cliang_barskeyView()
{
	// TODO: 在此处添加构造代码

}

Cliang_barskeyView::~Cliang_barskeyView()
{
}

BOOL Cliang_barskeyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Cliang_barskeyView 绘制

bool clip(float p,float q,float &u1,float &u2)
//判断区域
{
   float r;
   if(p<0.0)
   {
	   r=q/p;
	   if(r>u2)return false;
	   if(r>u1) u1=r;
   }else if(p>0.0)
   {
	   r=q/p;
	   if(r<u1)return false;
	   if(r<u2)u2=r;
   }else return (q>=0.0);
   return true;
}

void Cliang_barskeyView::OnDraw(CDC* pDC)
{
	Cliang_barskeyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


   	struct rects
	{
		int rx1,ry1,rx2,ry2;
	}rect={100,100,300,300};
	struct lines
	{
		int x1,y1,x2,y2;
	}line={50,100,600,600};
pDC->Rectangle(rect.rx1,rect.ry1,rect.rx2,rect.ry2);
    float dx,dy,u1,u2;
	  u1=0.0;u2=1.0;
    dx=line.x2-line.x1;
	dy=line.y2-line.y1;
	if(clip(-dx,line.x1-rect.rx1,u1,u2))
		if(clip(dx,rect.rx2-line.x1,u1,u2))
			if(clip(-dy,line.y1-rect.ry1,u1,u2))
				if(clip(dy,rect.ry2-line.y1,u1,u2))
					if(u1<=u2)
						{
							pDC->MoveTo(line.x1+u2*dx,line.y1+u2*dy);
							pDC->LineTo(line.x1+u1*dx,line.y1+u1*dy);
						}
}
	// TODO: 在此处为本机数据添加绘制代码


// Cliang_barskeyView 打印


void Cliang_barskeyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cliang_barskeyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cliang_barskeyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cliang_barskeyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Cliang_barskeyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cliang_barskeyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cliang_barskeyView 诊断

#ifdef _DEBUG
void Cliang_barskeyView::AssertValid() const
{
	CView::AssertValid();
}

void Cliang_barskeyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cliang_barskeyDoc* Cliang_barskeyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cliang_barskeyDoc)));
	return (Cliang_barskeyDoc*)m_pDocument;
}
#endif //_DEBUG


// Cliang_barskeyView 消息处理程序
