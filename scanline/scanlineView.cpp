
// scanlineView.cpp : CscanlineView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CscanlineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CscanlineView ����/����

CscanlineView::CscanlineView()
{
	// TODO: �ڴ˴���ӹ������

}

CscanlineView::~CscanlineView()
{
}

BOOL CscanlineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CscanlineView ����

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

	

	//-------------------------ymax ɨ�����----------------------
	int ymax=0;
	for (int i=0;i<POINTNUM;i++)
		if(polypoint[i].y>ymax)ymax=polypoint[i].y;

	
	
	//--------��ʼ��AET-----------------
	XET *AET=new XET;
	AET->next=NULL;
	//--------��ʼ��NET---------------
        
	XET *NET[1024];
	for(int i = 0;i<ymax;i++)
	{
		NET[i]=new XET;
		NET[i]->next=NULL;
	}
	
	//-----------ɨ�貢����NET---------
	
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

	
	//-----------ɨ�貢����AET-------------------------------
	for(int i=0;i<ymax;i++)
	{  
	
		
		
		
		XET *p=new XET;
		XET *q=new XET;
		
	
		
		
		
		//--------NET�µ����AET---------
		
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
		  
		//--------д����---------
		p=AET->next;
		while(p&&p->next)
		{
			
			for(int j=p->x;j<=p->next->x;j++)
				pDC->SetPixel(static_cast<int>(j),i,RGB(255,0,0));
			
			p=p->next->next;
		}

			//-------ɨ�������ƣ�����AET-----
		p=AET->next;
		while(p)
		{
			p->x=p->x+p->dx;
			p=p->next;
		}
		//--------ɾ��ymax==i+1�Ľ�㣬�˱߲�����һ��ɨ�����ཻ------
		p=AET;
		while(p->next)
		{
			if(p->next->ymax==i+1)
				p->next=p->next->next;
			else p=p->next;
		}
   }

}

// CscanlineView ��ӡ


void CscanlineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CscanlineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CscanlineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CscanlineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CscanlineView ���

#ifdef _DEBUG
void CscanlineView::AssertValid() const
{
	CView::AssertValid();
}

void CscanlineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CscanlineDoc* CscanlineView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CscanlineDoc)));
	return (CscanlineDoc*)m_pDocument;
}
#endif //_DEBUG


// CscanlineView ��Ϣ�������
