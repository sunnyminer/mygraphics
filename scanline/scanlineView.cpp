
// scanlineView.cpp : CscanlineView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "scanline.h"
#endif
#include "wingdi.h"
#include "scanlineDoc.h"
#include "scanlineView.h"
#include <iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CscanlineView

IMPLEMENT_DYNCREATE(CscanlineView, CView)

BEGIN_MESSAGE_MAP(CscanlineView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CscanlineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CscanlineView 构造/析构

CscanlineView::CscanlineView()
{
	// TODO: 在此处添加构造代码

}

CscanlineView::~CscanlineView()
{
}

BOOL CscanlineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CscanlineView 绘制

void CscanlineView::OnDraw(CDC* pDC)
{CscanlineDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    // TODO: add draw code for native data here
	
	
	
	const int POINTNUM = 6;

	struct XET
	{
		float x,dx, ymax;
		XET* next;
	};

	struct point
	{
		float x,y;
	} polypoint[POINTNUM] = {100,100,200,100,250,150,200,200,100,200,50,150};

	

	//-------------------------ymax 扫描结束----------------------
	int ymax=0;
	for (int i=0;i<POINTNUM;i++)
		if(polypoint[i].y>ymax)ymax=polypoint[i].y;

	
	
	//--------初始化AET-----------------
	XET *AET=new XET;
	AET->next=NULL;
	//--------初始化NET---------------
        
	XET *NET[1024];
	for(int i = 0;i<ymax;i++)
	{
		NET[i]=new XET;
		NET[i]->next=NULL;
	}
	
	//-----------扫描并建立NET---------
	
	for(int i=0;i<=ymax;i++)
	{
		for(int j=0;j<=POINTNUM;j++)
		{
			if(polypoint[j].y==i)
			{

		if(polypoint[j].y<polypoint[(j-1+POINTNUM)%POINTNUM].y)
		{
			XET * p=new XET;
			p->x = polypoint[j].x;
			p->dx = (polypoint[(j-1+POINTNUM)%POINTNUM].x-polypoint[j].x)/(polypoint[(j-1+POINTNUM)%POINTNUM].y-polypoint[j].y);
			p->ymax=polypoint[(j-1+POINTNUM)%POINTNUM].y;
			p->next=NET[i]->next;
			NET[i]->next=p;
		}
		
		if(polypoint[j].y<polypoint[(j+1+POINTNUM)%POINTNUM].y)
		{
			XET * p=new XET;
			p->x = polypoint[j].x;
			p->dx = (polypoint[(j+1+POINTNUM)%POINTNUM].x-polypoint[j].x)/(polypoint[(j+1+POINTNUM)%POINTNUM].y-polypoint[j].y);
			p->ymax=polypoint[(j+1+POINTNUM)%POINTNUM].y;
			p->next=NET[i]->next;
			NET[i]->next=p;
		}
			}
			
		}

			
	}

	
	//-----------扫描并建立AET-------------------------------
	for(int i=0;i<ymax;i++)
	{  
	
		
		
		
		XET *p=new XET;
		XET *q=new XET;
		
	
		
		
		
		//--------NET新点插入AET---------
		
		p=NET[i]->next;
		q=AET;
		while(p)
		{
			XET * s;
			while(q->next&&p->x>=q->next->x)
				q=q->next;
			s = p->next;
			p->next=q->next;
			q->next=p;
			p=s;
			q=AET;
		}
		  
		//--------写像素---------
		p=AET->next;
		while(p&&p->next)
		{
			
			for(int j=p->x;j<=p->next->x;j++)
				pDC->SetPixel(static_cast<int>(j),i,RGB(255,0,0));
			
			p=p->next->next;
		}

			//-------扫描线下移，更新AET-----
		p=AET->next;
		while(p)
		{
			p->x=p->x+p->dx;
			p=p->next;
		}
		//--------删除ymax==i+1的结点，此边不与下一条扫描线相交------
		p=AET;
		while(p->next)
		{
			if(p->next->ymax==i+1)
				p->next=p->next->next;
			else p=p->next;
		}
   }

}

// CscanlineView 打印


void CscanlineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CscanlineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CscanlineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CscanlineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CscanlineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CscanlineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CscanlineView 诊断

#ifdef _DEBUG
void CscanlineView::AssertValid() const
{
	CView::AssertValid();
}

void CscanlineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CscanlineDoc* CscanlineView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CscanlineDoc)));
	return (CscanlineDoc*)m_pDocument;
}
#endif //_DEBUG


// CscanlineView 消息处理程序
