
// de_casteljauView.cpp : Cde_casteljauView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "de_casteljau.h"
#endif

#include "de_casteljauDoc.h"
#include "de_casteljauView.h"

#include<stdio.h>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define pointnum 4

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cde_casteljauView

IMPLEMENT_DYNCREATE(Cde_casteljauView, CView)

BEGIN_MESSAGE_MAP(Cde_casteljauView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cde_casteljauView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cde_casteljauView 构造/析构

Cde_casteljauView::Cde_casteljauView()
{
	// TODO: 在此处添加构造代码

}

Cde_casteljauView::~Cde_casteljauView()
{
}

BOOL Cde_casteljauView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}



typedef struct Point{
	int x;
	int y;
}Point;

float hornbez(int degree, float* array0, float t){
	int r,i;
	float t1;
	float parray[10];

	for(i = 0; i <= degree; i++){
		parray[i] = array0[i]; 
	}
	for(int r=1;r<=degree;r++)
		for(int i=0;i<=degree-r;i++)
		{
			parray[i]=(1-t)*parray[i]+t*parray[i+1];
		}
	return parray[0];
}

void bezier(CDC *pDC,Point p[], int color){
	float bx[pointnum];
	float by[pointnum];

	for(int  i=0; i<pointnum; i++){
		bx [i] = p[i].x * 1.0;
		by [i] = p[i].y * 1.0;
	}
	int num = 1000;
	int x,y;
	for(float j = 0.0; j <num; j++){
		x = (int)hornbez(pointnum - 1, bx, j/num);
		y = (int)hornbez(pointnum - 1, by, j/num);
		pDC->SetPixel( x, y, color);
	}
}
// Cde_casteljauView 绘制
void Cde_casteljauView::OnDraw(CDC* pDC)
{
	Cde_casteljauDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	Point p[4]={100,100,300,400,500,50,750,400};
	
	for(int i=0; i<pointnum; i++){	
		pDC->MoveTo( p[i].x, p[i].y);
		pDC->LineTo(p[i+1].x, p[i+1].y);
	}
	bezier(pDC,p,RGB(0,0,255));
	// TODO: 在此处为本机数据添加绘制代码
}


// Cde_casteljauView 打印


void Cde_casteljauView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cde_casteljauView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cde_casteljauView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cde_casteljauView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Cde_casteljauView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cde_casteljauView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cde_casteljauView 诊断

#ifdef _DEBUG
void Cde_casteljauView::AssertValid() const
{
	CView::AssertValid();
}

void Cde_casteljauView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cde_casteljauDoc* Cde_casteljauView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cde_casteljauDoc)));
	return (Cde_casteljauDoc*)m_pDocument;
}
#endif //_DEBUG


// Cde_casteljauView 消息处理程序
