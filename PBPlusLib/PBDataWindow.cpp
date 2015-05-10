#include "StdAfx.h"
#include "PBDataWindow.h"
#include "PBDWDataTrans.h"
BEGIN_PBPLUS_NASPACE
LRESULT CALLBACK PBDataWindow::CustDWMsgProc(HWND hwnd,UINT message, WPARAM wParam, LPARAM lParam)
{
	//由于使用了Thunk代码，所以第1个参数（hwnd）实际上就是this了
	PBDataWindow *pThis= (PBDataWindow *)hwnd;
	PBDWObject dwo(pThis->session);
	tstring mData;
	long eventReturnVal;
	tstring sqlerrText,sqlsyntax;
	PDwDataTrans rbd=nullptr;
	switch(message)
	{
	/*case WM_COPYDATA:
		 ::MessageBox(NULL,_T("WM_COPYDATA"),_T(""),MB_OK);
		 return 0;*/
	case WM_USER + 1:
		rbd=(PDwDataTrans)lParam;
			switch(wParam)
			{
			case PB_DWNSETFOCUS://GetFocus
				eventReturnVal = pThis->OnGetFocus();
				return 0;
			case PB_DWNKILLFOCUS://LoseFocus
				eventReturnVal = pThis->OnLoseFocus();
				return 0;
			case PB_DWNCHANGING://EditChanged				
				eventReturnVal = pThis->OnEditChanged(rbd->row,rbd->dwo,rbd->data);
				return 0;
			case PB_DWNITEMCHANGE://ItemChanged
				eventReturnVal =pThis->OnItemChanged(rbd->row,rbd->dwo,rbd->data);
				rbd->rtlVal = eventReturnVal;
				return 0;
			case PB_DWNITEMCHANGEFOCUS://ItemFocusChanged
				eventReturnVal =pThis->OnItemFocusChanged(rbd->row,rbd->dwo);
				return 0;
			case PB_DWNROWCHANGE://RowFocusChanged
				eventReturnVal =pThis->OnRowFocusChanged(rbd->currentRow);
				return 0;
			case PB_DWNROWCHANGING://RowFocusChanging
				eventReturnVal =pThis->OnRowFocusChanging(rbd->currentRow,rbd->newRow);
				rbd->rtlVal = eventReturnVal;
				return 0;
			case PB_DWNITEMVALIDATIONERROR://ItemError
				eventReturnVal =pThis->OnItemError(rbd->row,rbd->dwo,rbd->data);
				rbd->rtlVal = eventReturnVal;
				return 0;
			case PB_DWNLBUTTONCLK://单击
				eventReturnVal =pThis->OnClicked(rbd->xPos,rbd->yPos,rbd->row,rbd->dwo);
				rbd->rtlVal = eventReturnVal;
				//pThis->SetPBEventReturnValue(eventReturnVal);
				return 0;
			case PB_DWNRBUTTONDOWN://右击
				eventReturnVal =pThis->OnRButtonDown(rbd->xPos,rbd->yPos,rbd->row,rbd->dwo);
				//pThis->SetPBEventReturnValue(eventReturnVal);
				return 0;
			case PB_DWNLBUTTONDBLCLK://双击
				eventReturnVal =pThis->OnDoubleClicked(rbd->xPos,rbd->yPos,rbd->row,rbd->dwo);
				return 0;
			case PB_DWNSQL://SQLPreview
				eventReturnVal =pThis->OnSQLPreview(rbd->request,rbd->sqltype,rbd->sqlsyntax,rbd->buffer,rbd->row);
				rbd->rtlVal = eventReturnVal;
				return 0;
			case PB_DWNDBERROR://DBError
				eventReturnVal =pThis->OnDBError(rbd->sqlDBCode,rbd->sqlErrText,rbd->sqlsyntax,rbd->buffer,rbd->row);
				rbd->rtlVal = eventReturnVal;
				return 0;
			case PB_DWNPRINTEND://PrintEnd
				eventReturnVal = pThis->OnPrintEnd(rbd->pagesPrinted);
				return 0;
			case PB_DWNPRINTMARGINCHANGE:
				eventReturnVal = pThis->OnPrintMarginChange();
				return 0;
			case PB_DWNPRINTPAGE://PrintPage
				eventReturnVal = pThis->OnPrintPage(rbd->pageNumber,rbd->copy);
				rbd->rtlVal = eventReturnVal;
				return 0;
			case PB_DWNPRINTSTART:
				eventReturnVal = pThis->OnPrintStart(rbd->pagesMax);
				return 0;
			case PB_DWNRETRIEVEEND://RetrieveEnd
				eventReturnVal = pThis->OnRetrieveEnd(rbd->rowCount);
				return 0;
			case PB_DWNRETRIEVESTART://RetrieveStart
				eventReturnVal = pThis->OnRetrieveStart();
				rbd->rtlVal = eventReturnVal;
				return 0;
			case PB_DWNHSCROLL:
				eventReturnVal = pThis->OnScrollHorizontal(rbd->scrollpos,rbd->pane);
				return 0;
			case PB_DWNVSCROLL:
				eventReturnVal = pThis->OnScrollVertical(rbd->scrollpos);
				return 0;
			case PB_DWNUPDATEEND:
				eventReturnVal = pThis->OnUpdateEnd(rbd->RowsInserted,rbd->RowsUpdated,rbd->RowsDeleted);
				return 0;
			case PB_DWNUPDATESTART:
				eventReturnVal = pThis->OnUpdateStart();
				rbd->rtlVal = eventReturnVal;
				return 0;
			case PB_DWNRESIZE:
				eventReturnVal = pThis->OnResize(rbd->sizetype,rbd->newWidth,rbd->newHeight);
				return 0;
			}
			return 0;
	}
	//调用控件原来的消息处理函数
	return CallWindowProc(pThis->pOldProc,pThis->m_hWnd,message,wParam,lParam);
}
PBDataWindow::PBDataWindow(IPB_Session* s)
	:PBDragObject(s),pOldProc(nullptr)
{
}
PBDataWindow::PBDataWindow(const PBDataWindow& dwObj)
	:PBDragObject(dwObj.session)
	,m_DWThunk(dwObj.m_DWThunk),m_hWnd(dwObj.m_hWnd),pOldProc(dwObj.pOldProc)
{
	this->obj = dwObj.obj;
	this->cls = dwObj.cls;
}
PBDataWindow::~PBDataWindow(void)
{
	m_hWnd = PBSystem::Handle(session,this->obj);
	if(nullptr != pOldProc)
	 (WNDPROC)::SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)pOldProc);
}

#pragma region 对应函数
//Border
bool PBDataWindow::GetBorder()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("border"),value);
	return value;
}
void PBDataWindow::SetBorder(bool border)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("border"),border);
}

//ControlMenu
bool PBDataWindow::GetControlMenu()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("controlmenu"),value);
	return value;
}
void PBDataWindow::SetControlMenu(bool menu)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("controlmenu"),menu);
}

//Enabled
bool PBDataWindow::GetEnabled()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("Enabled"),value);
	return value;
}
void PBDataWindow::SetEnabled(bool enabled)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("Enabled"),enabled);
}

//HscrollBar
bool PBDataWindow::GetHScrollBar()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("HscrollBar"),value);
	return value;
}
void PBDataWindow::SetHScrollBar(bool hscBar)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("HscrollBar"),hscBar);
}

//HSplitScroll
bool PBDataWindow::GetHSplitScroll()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("HSplitScroll"),value);
	return value;
}
void PBDataWindow::SetHSplitScroll(bool hsp)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("HSplitScroll"),hsp);
}

//LiveScroll
bool PBDataWindow::GetLiveScroll()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("LiveScroll"),value);
	return value;
}
void PBDataWindow::SetLiveScroll(bool lsc)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("LiveScroll"),lsc);
}

//MaxBox
bool PBDataWindow::GetMaxBox()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("MaxBox"),value);
	return value;
}
void PBDataWindow::SetMaxBox(bool maxbox)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("MaxBox"),maxbox);
}

//MinBox
bool PBDataWindow::GetMinBox()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("MinBox"),value);
	return value;
}
void PBDataWindow::SetMinBox(bool minbox)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("MinBox"),minbox);
}

//Resizable
bool PBDataWindow::GetResizable()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("Resizable"),value);
	return value;
}
void PBDataWindow::SetResizable(bool resizeble)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("Resizable"),resizeble);
}

//RightToLeft
bool PBDataWindow::GetRightToLeft()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("RightToLeft"),value);
	return value;
}
void PBDataWindow::SetRightToLeft(bool r2l)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("RightToLeft"),r2l);
}

//TitleBar
bool PBDataWindow::GetTitleBar()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("TitleBar"),value);
	return value;
}
void PBDataWindow::SetTitleBar(bool tBar)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("TitleBar"),tBar);
}

//VScrollBar
bool PBDataWindow::GetVScrollBar()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("VScrollBar"),value);
	return value;
}
void PBDataWindow::SetVScrollBar(bool vscBar)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("VScrollBar"),vscBar);
}

//BorderStyle
PBBorderStyle PBDataWindow::GetBorderStyle()
{
	PBBorderStyle style;
	SHORT value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("BorderStyle"),value);
	style = (PBBorderStyle)value;
	return style;
}
void PBDataWindow::SetBorderStyle(PBBorderStyle style)
{
	SHORT value = style;
	PBSetPropertyValue(session,this->cls,this->obj,_T("BorderStyle"),value);
}

//RichTextToolbarActivation
PBRichTextToolbarActivation PBDataWindow::GetRichTextToolbarActivation()
{
	PBRichTextToolbarActivation style;
	SHORT value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("RichTextToolbarActivation"),value);
	style = (PBRichTextToolbarActivation)value;
	return style;
}
void PBDataWindow::SetRichTextToolbarActivation(PBRichTextToolbarActivation style)
{
	SHORT value = style;
	PBSetPropertyValue(session,this->cls,this->obj,_T("RichTextToolbarActivation"),value);
}

//DataObject
tstring PBDataWindow::GetDataObject()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("dataobject"),value);
	return value;
}
void PBDataWindow::SetDataObject(tstring dobj)
{
	if(nullptr != pOldProc)
		SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)pOldProc);
	PBSetPropertyValue(session,this->cls,this->obj,_T("dataobject"),dobj);
	SetWxjOwnerProc();
}

//Icon
tstring PBDataWindow::GetIcon()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("icon"),value);
	return value;
}
void PBDataWindow::SetIcon(tstring icon)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("icon"),icon);
}

//Title
tstring PBDataWindow::GetTitle()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("Title"),value);
	return value;
}
void PBDataWindow::SetTitle(tstring title)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("Title"),title);
}
#pragma endregion
//==============================================================
//函数
//--------------------------------------------------------------
SHORT PBDataWindow::AcceptText(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("AcceptText"),_T("I"));
}
bool PBDataWindow::CanUndo(void)
{
	return PBXInvokeFunc<bool>(session,this->cls,this->obj,_T("CanUndo"),_T("B"));
}
SHORT PBDataWindow::CategoryCount( tstring grCtl )
{
	return PBXInvokeFunc<SHORT,tstring>(session,this->cls,this->obj,_T("CategoryCount"),_T("IS"),grCtl);
}
tstring PBDataWindow::CategoryName( tstring grCtl,SHORT c  )
{
	return PBXInvokeFunc<tstring,tstring,SHORT>(session,this->cls,this->obj,_T("CategoryName"),_T("SSI"),grCtl,c);
}
SHORT PBDataWindow::Clear (void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Clear"),_T("I"));
}
long PBDataWindow::Clear (bool gridFlag)
{
	return PBXInvokeFunc<long,bool>(session,this->cls,this->obj,_T("Clear"),_T("LB"),gridFlag);
}
SHORT PBDataWindow::ClearAll(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("ClearAll"),_T("I"));
}
SHORT PBDataWindow::ClearValues( SHORT c )
{
	return PBXInvokeFunc<SHORT,SHORT>(session,this->cls,this->obj,_T("ClearValues"),_T("IXI"),c);
}
SHORT PBDataWindow::ClearValues( tstring c )
{
	return PBXInvokeFunc<SHORT,tstring>(session,this->cls,this->obj,_T("ClearValues"),_T("IXS"),c);
}
SHORT PBDataWindow::Clipboard ( tstring data )
{
	return PBXInvokeFunc<SHORT,tstring>(session,this->cls,this->obj,_T("Clipboard"),_T("IS"),data);
}
SHORT PBDataWindow::Collapse(long row, long groupLevel)
{
	return PBXInvokeFunc<SHORT,long,long>(session,this->cls,this->obj,_T("Collapse"),_T("ILL"),row,groupLevel);
}
SHORT PBDataWindow::CollapseAll(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("CollapseAll"),_T("I"));
}
SHORT PBDataWindow::CollapseLevel(long groupLevel)
{
	return PBXInvokeFunc<SHORT,long>(session,this->cls,this->obj,_T("CollapseLevel"),_T("IL"),groupLevel);
}
SHORT PBDataWindow::Copy(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Copy"),_T("I"));

}
tstring PBDataWindow::CopyRTF(bool selected)
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("CopyRTF"),_T("SB"),selected);
}
tstring PBDataWindow::CopyRTF(bool selected,PBBand band)
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("CopyRTF"),_T("SBCband."),selected,(long)band);
}
SHORT PBDataWindow::Create(tstring syn)
{
	SHORT rtn;
	if(nullptr != pOldProc)
		SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)pOldProc);
	rtn = PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Create"),_T("IXS"),syn);
	SetWxjOwnerProc();
	return rtn;
}
SHORT PBDataWindow::Create(tstring syn,tstring errorbuffer)
{
	SHORT rtn;
	if(nullptr != pOldProc)
		SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)pOldProc);
	rtn = PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Create"),_T("IXS"),syn);
	SetWxjOwnerProc();
	return rtn;
}
SHORT PBDataWindow::CrossTabDialog(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("CrossTabDialog"),_T("I"));
}
SHORT PBDataWindow::Cut(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Cut"),_T("I"));
}
long PBDataWindow::DataCount( tstring graphcontrol, tstring seriesname )
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("DataCount"),_T("LSS"),graphcontrol,seriesname);
}
SHORT PBDataWindow::DBCancel(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("DBCancel"),_T("I"));
}
long PBDataWindow::DBErrorCode(void)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("DBErrorCode"),_T("L"));
}
tstring PBDataWindow::DBErrorMessage(void)
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("DBErrorMessage"),_T("S"));
}
long PBDataWindow::DeletedCount(void)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("DeletedCount"),_T("L"));
}
SHORT PBDataWindow::DeleteRow( long row )
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("DeleteRow"),_T("IL"));
}
tstring PBDataWindow::Describe(tstring propertylist)
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("Describe"),_T("SXS"),propertylist);
}
SHORT PBDataWindow::Expand(long row, long groupLevel)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Expand"),_T("ILL"),row,groupLevel);
}
SHORT PBDataWindow::ExpandAll()
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("ExpandAll"),_T("I"));
}
SHORT PBDataWindow::ExpandAllChildren(long row, long groupLevel)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("ExpandAllChildren"),_T("ILL"),row,groupLevel);
}
SHORT PBDataWindow::ExpandLevel (long groupLevel)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("ExpandLevel"),_T("IL"),groupLevel);
}
SHORT PBDataWindow::Filter(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Filter"),_T("I"));
}
long PBDataWindow::FilteredCount(void)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("FilteredCount"),_T("L"));
}
long PBDataWindow::Find (tstring expression, long start, long end, PBDWBuffer buffer)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("Find"),_T("LXSLLCdwbuffer."),expression,start,end,(long)buffer);
}
long PBDataWindow::Find (tstring searchtext, bool forward,bool insensitive,bool wholeword,bool cursor )
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("Find"),_T("ISBBBB."),searchtext,forward,insensitive,wholeword,cursor);
}
//FindCategory
long PBDataWindow::FindGroupChange(long row,SHORT level )
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("FindGroupChange"),_T("LLI"),row,level);
}
SHORT PBDataWindow::FindNext(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("FindNext"),_T("I"));
}
SHORT PBDataWindow::FindRequired (PBDWBuffer dwbuffer,long& row,SHORT& colnbr,tstring& colname,bool updateonly)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("FindRequired"),_T("ICdwbuffer.RLRIRSB"),(long)dwbuffer,row,colnbr,colname,updateonly);
}
SHORT PBDataWindow::FindSeries(tstring graphcontrol,tstring seriesname)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("FindSeries"),_T("ISS"),graphcontrol,seriesname);
}
SHORT PBDataWindow::GenerateHTMLForm (tstring& syntax,tstring& style,tstring action)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("GenerateHTMLForm"),_T("IRSRSS"),syntax,style,action);
}
SHORT PBDataWindow::GenerateHTMLForm (tstring& syntax,tstring& style,tstring action , long startrow, long endrow, SHORT startcolumn,SHORT endcolumn , PBDWBuffer buffer )
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("GenerateHTMLForm"),_T("IRSRSSLLIICdwbuffer."),syntax,style,action,startrow,endrow,startcolumn,endcolumn,(long)buffer);
}
SHORT PBDataWindow::GenerateResultSet(PBDWBuffer buffer)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("GenerateResultSet"),_T("ICdwbuffer."),(long)buffer);
}
tstring PBDataWindow::GetBandAtPointer()
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("GetBandAtPointer"),_T("S"));
}
PBBorderStyle PBDataWindow::GetBorderStyle(SHORT column)
{
	return (PBBorderStyle)PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("GetBorderStyle"),_T("Cborder.XI"),column);
}
PBBorderStyle PBDataWindow::GetBorderStyle(tstring column)
{
	return (PBBorderStyle)PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("GetBorderStyle"),_T("Cborder.XS"),column);
}
long PBDataWindow::GetChanges(byte* changeblob,size_t& bytes)
{
	int refParm = 1;//第1个参数不传入参数
	pbblob data=nullptr;
	PBCallInfo ci;
	PBXExcuteFunc(session,this->cls,this->obj,_T("GetChanges"),_T("LRO"),data,ci,refParm);
	data = ci.pArgs->GetAt(0)->GetBlob();
	bytes = session->GetBlobLength(data);
	if(bytes >0)
	{
		changeblob = new byte[bytes];
		memmove(changeblob,session->GetBlob(data),bytes);
	}
	long rVal = ci.returnValue->GetLong();
	session->FreeCallInfo(&ci);
	return rVal;
}
long PBDataWindow::GetChanges(tstring changeblob)
{
	int refParm = 1;//第1个参数不传入参数
	pbstring data=nullptr;
	PBCallInfo ci;
	PBXExcuteFunc(session,this->cls,this->obj,_T("GetChanges"),_T("LRS"),data,ci,refParm);
	LPCTSTR c_data = session->GetString(ci.pArgs->GetAt(0)->GetString());
	changeblob.assign(c_data);
	long rVal = ci.returnValue->GetLong();
	session->FreeCallInfo(&ci);
	return rVal;
}
//...
//...
long PBDataWindow::GetFullState (byte* &dwasblob,size_t& bytes)
{
	int refParm = 1;//第1个参数不传入参数
	pbblob data=nullptr;
	PBCallInfo ci;
	PBXExcuteFunc(session,this->cls,this->obj,_T("GetFullState"),_T("LRO"),data,ci,refParm);
	data = ci.pArgs->GetAt(0)->GetBlob();
	bytes = session->GetBlobLength(data);
	if(bytes >0)
	{
		dwasblob = new byte[bytes];
		memcpy((void*)dwasblob,session->GetBlob(data),bytes);
	}
	long rVal = ci.returnValue->GetLong();
	session->FreeCallInfo(&ci);
	return rVal;
}
long PBDataWindow::GetFullState (tstring& dwasblob)
{
	int refParm = 1;//第1个参数不传入参数
	pbstring data=nullptr;
	PBCallInfo ci;
	PBXExcuteFunc(session,this->cls,this->obj,_T("GetFullState"),_T("LRS"),data,ci,refParm);
	LPCTSTR c_data = session->GetString(ci.pArgs->GetAt(0)->GetString());
	dwasblob.assign(c_data);
	long rVal = ci.returnValue->GetLong();
	session->FreeCallInfo(&ci);
	return rVal;
}
//...
//...
long PBDataWindow::InsertRow( long row )
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("InsertRow"),_T("LL"),row);
}
bool PBDataWindow::IsExpanded(long row, long groupLevel)
{
	return PBXInvokeFunc<bool>(session,this->cls,this->obj,_T("IsExpanded"),_T("BLL"),row,groupLevel);
}
bool PBDataWindow::IsSelected( long row )
{
	return PBXInvokeFunc<bool>(session,this->cls,this->obj,_T("IsSelected"),_T("BL"),row);
}
SHORT PBDataWindow::LineCount(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("LineCount"),_T("I"));
}
long PBDataWindow::ModifiedCount(void)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("ModifiedCount"),_T("L"));
}
tstring PBDataWindow::Modify( tstring modstring)
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("Modify"),_T("SXS"),modstring);
}
//...
//...
SHORT PBDataWindow::Print( bool canceldialog ,bool showprintdialog)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Print"),_T("IBB"),canceldialog,showprintdialog);
}
SHORT PBDataWindow::PrintCancel(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("PrintCancel"),_T("I"));
}
#ifdef ReplaceText 
#undef ReplaceText
#endif
long PBDataWindow::ReplaceText(tstring str)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("ReplaceText"),_T("IS"),str);
}
#ifdef UNICODE
#define ReplaceText  ReplaceTextW
#else
#define ReplaceText  ReplaceTextA
#endif // !UNICODE

//#ifdef USING_CPPCLI_PROJ
//long PBDataWindow::ReplaceText_CLI(tstring str)
//{
//	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("ReplaceText"),_T("IS"),str);
//}
//#endif
SHORT PBDataWindow::ReselectRow(long row)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("ReselectRow"),_T("IL"),row);
}
SHORT PBDataWindow::Reset(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Reset"),_T("I"));
}
//...
//...
SHORT PBDataWindow::ResetUpdate(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("ResetUpdate"),_T("I"));
}
long PBDataWindow::Retrieve(void)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("Retrieve"),_T("L"));
}
//template<typename P1>long PBDataWindow::Retrieve(P1& p1 )
//{
//	return PBXInvokeFunc<long,P1>(session,this->cls,this->obj,_T("Retrieve"),_T("LAV"),p1);
//}
//...
//...
long PBDataWindow::RowCount(void)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("RowCount"),_T("L"));
}
//...
//...
SHORT PBDataWindow::RowsDiscard (long startrow, long endrow, PBDWBuffer buffer )
{
	//枚举值其实也是long(或int),所以直接强制转换
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("RowsDiscard"),_T("ILLCdwbuffer."),startrow,endrow,(long)buffer);
	//return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("RowsDiscard"),_T("ILLI"),startrow,endrow,(SHORT)buffer);
}
//...
//...
SHORT PBDataWindow::Scroll(SHORT number)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Scroll"),_T("II"),number);
}
long PBDataWindow::ScrollNextPage (void )
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("ScrollNextPage"),_T("L"));
}
long PBDataWindow::ScrollNextRow(void )
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("ScrollNextRow"),_T("L"));
}
long PBDataWindow::ScrollPriorPage ( void)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("ScrollPriorPage"),_T("L"));
}
long PBDataWindow::ScrollPriorRow (void )
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("ScrollPriorRow"),_T("L"));
}
SHORT PBDataWindow::ScrollToRow ( long row )
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("ScrollToRow"),_T("IL"),row);
}
//SetItem系列
SHORT PBDataWindow::SetItemString(long row, SHORT column,/*V*/tstring value)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SetItem"),_T("ILXIA"),row,column,value);
}

//SHORT PBDataWindow::SetItemDate(long row, SHORT column,PBDate& value)
//{
//	pbdate val= session->NewDate();
//	session->SetDate(val,value.GetYear(), value.GetMonth(),value.GetDay());
//	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SetItem"),_T("ILXIA"),row,column,val);
//}
//SHORT PBDataWindow::SetItemDateTime(long row, SHORT column,/*V*/PBDateTime& value)
//{
//	pbdatetime val= session->NewDateTime();
//	session->SetDateTime(val,value.GetYear(), value.GetMonth(),value.GetDay(),value.GetHour(),value.GetMinute(),value.GetSecond());
//	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SetItem"),_T("ILXIA"),row,column,val);
//}*/
//SetItem系列
SHORT PBDataWindow::SelectedLength (void )
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SelectedLength"),_T("I"));
}
SHORT PBDataWindow::SelectedLine (void )
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SelectedLine"),_T("I"));
}
SHORT PBDataWindow::SelectedStart(void )
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SelectedStart"),_T("I"));
}
tstring PBDataWindow::SelectedText (void )
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("SelectedText"),_T("I"));
}
SHORT PBDataWindow::SelectRow ( long row, bool select )
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SelectRow"),_T("ILB"),row,select);
}
//...
//...
SHORT PBDataWindow::SetFullState(byte dwasblob[],size_t len)
{
	if(len<1 || dwasblob==nullptr ) return 0;
	if(nullptr != pOldProc)
		SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)pOldProc);
	this->SetRedraw(false);
	pbblob data = session->NewBlob(dwasblob,len);
	SHORT rval= PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SetFullState"),_T("IXO"),data);
	//session->PopLocalFrame();
	SetWxjOwnerProc();
	this->SetRedraw(true);
	return rval;
	//int refParm = 2;//第2个参数不传入参数
	//PBCallInfo ci;
	//pbobject newDW=nullptr;
	//PBXExcuteFunc<pbblob,pbobject>(session,this->cls,this->obj,_T("of_setfullstate"),_T("IXORCdatawindow."),data,newDW,ci,refParm);
	//newDW = ci.pArgs->GetAt(1)->GetObject();
	//this->obj = newDW;
	//this->cls=session->GetClass(newDW);
	//SHORT rVal = ci.returnValue->GetInt();
	//SetWxjOwnerProc();
	//this->SetRedraw(true);
	////this->DataObject = this->DataObject;
	// //session->UpdateField(obj,fid)
	//return rVal;
}
SHORT PBDataWindow::SetFullState(tstring dwasstring)
{
	if(nullptr != pOldProc)
		SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)pOldProc);
	this->SetRedraw(false);
	SHORT rVal= PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SetFullState"),_T("IXS"),dwasstring);
	////SHORT rval= PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("of_setfullstate"),_T("IXORCdatawindow."),dwasstring);
	//int refParm = 2;//第2个参数不传入参数
	//PBCallInfo ci;
	//pbobject newDW=nullptr;
	//PBXExcuteFunc<tstring,pbobject>(session,this->cls,this->obj,_T("of_setfullstate"),_T("IXSRCdatawindow."),dwasstring,newDW,ci,refParm);
	//newDW = ci.pArgs->GetAt(1)->GetObject();
	//this->obj = newDW;
	//this->cls=session->GetClass(newDW);
	//SHORT rVal = ci.returnValue->GetInt();
	SetWxjOwnerProc();
	this->SetRedraw(true);
	return rVal;
}
//...
//...
SHORT PBDataWindow::SetTransObject(PBTransAction& atr)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SetTransObject"),_T("ICtransaction."),atr.obj);
}
//...
//...
SHORT PBDataWindow::Sort(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Sort"),_T("I"));
}
tstring PBDataWindow::TextLine(void)
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("TextLine"),_T("S"));
}
SHORT PBDataWindow::Undo(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Undo"),_T("I"));
}
SHORT PBDataWindow::Update (bool accept, bool resetflag )
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Update"),_T("IBB"),accept,resetflag);
}

void PBDataWindow::SetPBEventReturnValue(long val)
{
	pbfieldID fid = session-> GetFieldID(cls, _T("EventLongRtnVal"));
	session->SetLongField( obj,  fid, val );
}
bool PBDataWindow::SetWxjOwnerProc()
{

	m_hWnd = PBSystem::Handle(session,this->obj);
	this->m_DWThunk.Init(this->GetWindowProc(), this);
	WNDPROC pProc = this->m_DWThunk.GetWNDPROC();
	//if(pOldProc == nullptr)
	pOldProc = (WNDPROC)::SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG_PTR)pProc);
	return true;
}

long PBDataWindow::OnClicked(int xpos,int ypos,long row,PBDWObject& dwo)
{
	/*tstringstream ss;
	ss<<_T("X位置:")<<xpos<<_T("\tY位置:")<<ypos<<_T("\t行:")<<row<<_T("\t对象类型:")<<dwo.Type.c_str()
		<<_T("\t对象名称:")<<dwo.Name.c_str();
	::MessageBox(this->m_hWnd,ss.str().c_str(),_T("鼠标单击"),MB_OK);*/
	return 0;
}
long PBDataWindow::OnDoubleClicked(int xpos,int ypos,long row,PBDWObject& dwo)
{
	/*tstringstream ss;
	ss<<_T("X位置:")<<xpos<<_T("\tY位置:")<<ypos<<_T("\t行:")<<row<<_T("\t对象类型:")<<dwo.Type.c_str()
		<<_T("\t对象名称:")<<dwo.Name.c_str();
	::MessageBox(this->m_hWnd,ss.str().c_str(),_T("鼠标双击"),MB_OK);*/
	return 0;
}
long PBDataWindow::OnDBError(long sqldbcode,tstring sqlerrtext,tstring sqlSyntax,PBDWBuffer buffer,long row)
{
	/*tstringstream ss;
	ss<<_T("sqldbcode:")<<sqldbcode<<_T("\tsqlerrtext:")<<sqlerrtext<<_T("\tsqlSyntax:")<<sqlSyntax
		<<_T("\tPBDWBuffer:")<<buffer<<_T("\trow:")<<row;
	::MessageBox(this->m_hWnd,ss.str().c_str(),_T("DBError"),MB_OK);*/
	return 0;
}
long PBDataWindow::OnEditChanged(long row,PBDWObject& dwo,tstring data)
{
	/*tstringstream ss;
	ss<<_T("行:")<<row<<_T("\t对象类型:")<<dwo.Type.c_str()
		<<_T("\t对象名称:")<<dwo.Name.c_str()<<_T("\tData:")<<data;
	::MessageBox(this->m_hWnd,ss.str().c_str(),_T("EditChange"),MB_OK);*/
	return 0;
}
long PBDataWindow::OnGetFocus()
{
	return 0;
}
long PBDataWindow::OnLoseFocus()
{
	return 0;
}

long PBDataWindow::OnItemChanged(long row,PBDWObject& dwo,tstring data)
{
	//tstringstream ss;
	//ss<<_T("行:")<<row<<_T("\t对象类型:")<<dwo.Type.c_str()
	//	<<_T("\t对象名称:")<<dwo.Name.c_str()<<_T("\tData:")<<data;
	//::MessageBox(this->m_hWnd,ss.str().c_str(),_T("ItemChanged"),MB_OK);
	return 0;
}
long PBDataWindow::OnItemFocusChanged(long row,PBDWObject& dwo)
{
	//tstringstream ss;
	//ss<<_T("行:")<<row<<_T("\t对象类型:")<<dwo.Type.c_str()
	//	<<_T("\t对象名称:")<<dwo.Name.c_str();
	//::MessageBox(this->m_hWnd,ss.str().c_str(),_T("ItemFocusChanged"),MB_OK);
	return 0;
}
long PBDataWindow::OnPrintEnd(long printPages)
{
	return 0;
}
long PBDataWindow::OnPrintMarginChange()
{
	return 0;
}
long PBDataWindow::OnPrintPage(long printNumber,long copy)
{
	return 0;
}
long PBDataWindow::OnPrintStart(long pagesMax)
{
	return 0;
}
long PBDataWindow::OnResize (ULONG sizetype,USHORT newwidth,USHORT newheight)
{
	return 0;
}
long PBDataWindow::OnRetrieveEnd(long rowcount)
{
	return 0;
}
long PBDataWindow::OnRetrieveStart()
{
	return 0;
}
long PBDataWindow::OnScrollHorizontal (long scrollpos,SHORT pane)
{
	return 0;
}
long PBDataWindow::OnScrollVertical (long scrollpos)
{
	return 0;
}
long PBDataWindow::OnRowFocusChanged(long currentrow)
{
	/*tstringstream ss;
	ss<<_T("行:")<<currentrow;
	::MessageBox(this->m_hWnd,_T("RowFocusChanged"),ss.str().c_str(),MB_OK);*/
	return 0;
}
long PBDataWindow::OnRowFocusChanging(long currentrow,long newRow)
{
	/*tstringstream ss;
	ss<<_T("行:")<<currentrow<<_T("\t新行：")<<newRow;
	::MessageBox(this->m_hWnd,ss.str().c_str(),_T("RowFocusChanging"),MB_OK);*/
	return 0;
}
long PBDataWindow::OnItemError(long row,PBDWObject& dwo,tstring data)
{
	return 0;
}
long PBDataWindow::OnRButtonDown(int xpos,int ypos,long row,PBDWObject& dwo)
{
	//tstringstream ss;
	//ss<<_T("X位置:")<<xpos<<_T("\tY位置:")<<ypos<<_T("\t行:")<<row<<_T("\t对象类型:")<<dwo.Type.c_str()
	//	<<_T("\t对象名称:")<<dwo.Name.c_str();
	//::MessageBox(this->m_hWnd,ss.str().c_str(),_T("鼠标右击"),MB_OK);
	return 0;
}
long PBDataWindow::OnSQLPreview(PBSQLPreviewFunction request,PBSQLPreviewType sqltype,tstring sqlsyntax,PBDWBuffer buffer,long row)
{
	/*tstringstream ss;
	ss<<_T("调用函数：")<<request<<_T("\t语句类型：")<<sqltype<<_T("\t语法：")<<sqlsyntax.c_str()
		<<_T("\t缓冲区：")<<buffer<<_T("\t行：")<<row;
	::MessageBox(this->m_hWnd,ss.str().c_str(),_T("SQL预览"),MB_OK);*/
	return 0;
}
long PBDataWindow::OnUpdateEnd (long rowsinserted,long rowsupdated,long rowsdeleted)
{
	return 0;
}
long PBDataWindow::OnUpdateStart(void)
{
	return 0;
}
END_PBPLUS_NASPACE