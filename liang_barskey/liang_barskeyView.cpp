
// liang_barskeyView.cpp : Cliang_barskeyView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cliang_barskeyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cliang_barskeyView ����/����

Cliang_barskeyView::Cliang_barskeyView()
{
	// TODO: �ڴ˴���ӹ������

}

Cliang_barskeyView::~Cliang_barskeyView()
{
}

BOOL Cliang_barskeyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// Cliang_barskeyView ����

bool clip(float p,float q,float &u1,float &u2)
//�ж�����
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
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���


// Cliang_barskeyView ��ӡ


void Cliang_barskeyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cliang_barskeyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void Cliang_barskeyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void Cliang_barskeyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// Cliang_barskeyView ���

#ifdef _DEBUG
void Cliang_barskeyView::AssertValid() const
{
	CView::AssertValid();
}

void Cliang_barskeyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cliang_barskeyDoc* Cliang_barskeyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cliang_barskeyDoc)));
	return (Cliang_barskeyDoc*)m_pDocument;
}
#endif //_DEBUG


// Cliang_barskeyView ��Ϣ�������
