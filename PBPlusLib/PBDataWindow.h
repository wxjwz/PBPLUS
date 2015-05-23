/*
* PBDataWindow.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
#include "pbdragobject.h"
#include "PBSystem.h"
#include "PBTransAction.h"
#include "PBDWObject.h"
#include <tuple>
#include "PBDate.h"
#include "PBDateTime.h"
//#include <atlwin.h>
BEGIN_PBPLUS_NASPACE
class PBDataWindow :
	public PBDragObject
{
private:
	ATL::CWndProcThunk m_DWThunk;
public:
	HWND m_hWnd;
private:
	WNDPROC pOldProc;
public:
	PBDataWindow(IPB_Session* s);
	PBDataWindow(const PBDataWindow& dw);
	~PBDataWindow(void);

#pragma region 对应属性
public:
	DECLAREPBPROPERTY(bool,Border)
	DECLAREPBPROPERTY(bool,ControlMenu)
	DECLAREPBPROPERTY(bool,Enabled)
	DECLAREPBPROPERTY(bool,HScrollBar)
	DECLAREPBPROPERTY(bool,HSplitScroll)
	DECLAREPBPROPERTY(bool,LiveScroll)
	DECLAREPBPROPERTY(bool,MaxBox)
	DECLAREPBPROPERTY(bool,MinBox)
	DECLAREPBPROPERTY(bool,Resizable)
	DECLAREPBPROPERTY(bool,RightToLeft)
	DECLAREPBPROPERTY(bool,TitleBar)
	DECLAREPBPROPERTY(bool,VScrollBar)
	DECLAREPBPROPERTY(PBBorderStyle,BorderStyle)
	//DWObject 未实现
	DECLAREPBPROPERTY(PBRichTextToolbarActivation,RichTextToolbarActivation)
	DECLAREPBPROPERTY(tstring,DataObject)
	DECLAREPBPROPERTY(tstring,Icon)
	DECLAREPBPROPERTY(tstring,Title)
#pragma endregion 对应属性
#pragma region 对应函数
public:
	SHORT AcceptText(void);
	bool CanUndo(void);
	SHORT CategoryCount( tstring grCtl );
	tstring CategoryName( tstring grCtl,SHORT c );
	SHORT Clear(void); 
	long Clear(bool gridFlag); 
	SHORT ClearAll(void);
	SHORT ClearValues( SHORT c );
	SHORT ClearValues( tstring c );
	SHORT Clipboard ( tstring data );
	SHORT Collapse(long row, long groupLevel);
	SHORT CollapseAll(void);
	SHORT CollapseLevel(long groupLevel);
	SHORT Copy(void);
	tstring CopyRTF(bool selected=true);
	tstring CopyRTF(bool selected,PBBand band);
	SHORT Create(tstring syn);
	SHORT Create(tstring syn,tstring errorbuffer);//errorbuffer还未实现
	SHORT CrossTabDialog(void);
	SHORT Cut(void);
	long DataCount( tstring graphcontrol, tstring seriesname );
	SHORT DBCancel(void);
	long DBErrorCode(void); 
	tstring DBErrorMessage(void);
	long DeletedCount(void);
	SHORT DeleteRow( long row );
	tstring Describe(tstring propertylist);
	SHORT Expand(long row, long groupLevel);
	SHORT ExpandAll();
	SHORT ExpandAllChildren(long row, long groupLevel);
	SHORT ExpandLevel (long groupLevel);
	SHORT Filter(void);
	long FilteredCount(void);
	long Find (tstring expression, long start, long end, PBDWBuffer buffer=Primary);
	long Find (tstring searchtext, bool forward,bool insensitive,bool wholeword,bool cursor );
	//FindCategory
	long FindGroupChange(long row,SHORT level );
	SHORT FindNext(void);
	SHORT FindRequired(PBDWBuffer dwbuffer,long& row,SHORT& colnbr,tstring& colname,bool updateonly); 
	SHORT FindSeries(tstring graphcontrol,tstring seriesname);
	SHORT GenerateHTMLForm (tstring& syntax,tstring& style,tstring action);
	SHORT GenerateHTMLForm (tstring& syntax,tstring& style,tstring action ,long startrow,long endrow,SHORT startcolumn,SHORT endcolumn , PBDWBuffer buffer=Primary );
	SHORT GenerateResultSet(PBDWBuffer buffer=Primary );
	tstring GetBandAtPointer();
	PBBorderStyle GetBorderStyle(SHORT column);
	PBBorderStyle GetBorderStyle(tstring column);
	long GetChanges(byte* changeblob,size_t& bytes);//返回之后，当bytes>0时需要delete []changeblob；bytes为字节数
	long GetChanges(tstring changeblob);
	//...
	//...
	long GetFullState (byte* &dwasblob,size_t& bytes);//返回之后，当bytes>0时需要delete []dwasblob；bytes为字节数
	long GetFullState (tstring& dwasstring);
	//...
	//...
	long InsertRow( long row );
	bool IsExpanded(long row, long groupLevel);
	bool IsSelected( long row ); 
	SHORT LineCount(void); 
	long ModifiedCount(void);
	tstring Modify( tstring modstring);
	//...
	//...
	SHORT Print( bool canceldialog=true ,bool showprintdialog=false);
	SHORT PrintCancel(void);

#ifdef ReplaceText 
#undef ReplaceText
#endif
	long ReplaceText(tstring str);
#ifdef UNICODE
#define ReplaceText  ReplaceTextW
#else
#define ReplaceText  ReplaceTextA
#endif // !UNICODE
//#ifdef USING_CPPCLI_PROJ
//	long ReplaceText_CLI(tstring str);//{return 0;/*ReplaceText(str);*/}
//#endif
	SHORT ReselectRow(long row); 
	SHORT Reset(void);
	//...
	//...
	SHORT ResetUpdate(void);
	long Retrieve(void);
	template<typename P1>long Retrieve(P1 t)
	{
		return 0;
	}
	template<typename P1,typename P2>long Retrieve(P1 t,P2 p2)
	{
		return 0;
	}
	//...
	//...
	long RowCount(void);
	//...
	//...
	SHORT RowsDiscard (long startrow, long endrow, PBDWBuffer buffer );
	//...
	//...
	SHORT Scroll(SHORT number);
	long ScrollNextPage (void );
	long ScrollNextRow(void );
	long ScrollPriorPage ( void);
	long ScrollPriorRow (void );
	SHORT ScrollToRow ( long row );
	SHORT SelectedLength (void );
	SHORT SelectedLine (void );
	SHORT SelectedStart(void );
	tstring SelectedText (void );
	SHORT SelectRow ( long row, bool select );
	//...
	//...
	/*template<typename V>*/SHORT SetItemString(long row, SHORT column,/*V*/tstring value);
	//{
	//	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("SetItem"),_T("ILXIA"),row,column,value);
	//}
	//SHORT SetItemDate(long row, SHORT column,/*V*/PBDate& value);
	//SHORT SetItemDateTime(long row, SHORT column,/*V*/PBDateTime& value);*/
	//...
	//...
	SHORT SetFullState(byte dwasblob[],size_t len);
	SHORT SetFullState(tstring dwasstring);
	//...
	//...
	SHORT SetTransObject(PBTransAction& atr);
	//...
	//...
	SHORT Sort(void);
	tstring TextLine(void);
	SHORT Undo(void);
	SHORT Update (bool accept =true, bool resetflag=true );

	
#pragma endregion 对应函数

#pragma region 对应事件
public:
	//返回值：0-继续事件的其他操作，1执行到本事件为止
	virtual long OnClicked(int xpos,int ypos,long row,PBDWObject& dwo);//鼠标单击
	//返回值：只有0
	virtual long OnDoubleClicked(int xpos,int ypos,long row,PBDWObject& dwo);//鼠标双击
	//返回值：0-显示错误信息，并且触发事务对象的DBError事件（当有定义该事件时）
	//		  1-不显示错误信息，并且触发事务对象的DBError事件（当有定义该事件时）
	//		  2-显示错误信息，忽略事务对象的DBError事件（当有定义该事件时）
	//		  3-不显示错误信息，忽略事务对象的DBError事件（当有定义该事件时）
	virtual long OnDBError(long sqldbcode,tstring sqlerrtext,tstring sqlSyntax,PBDWBuffer buffer,long row);//DBError
	//返回值：只有0
	virtual long OnEditChanged(long row,PBDWObject& dwo,tstring data);
	//返回值：只有0,继续处理
	virtual long OnGetFocus();
	
	//返回值：0-接受数据，1拒绝输入的数据并不允许焦点离开，2-拒绝输入的数据但允许焦点离开
	virtual long OnItemChanged(long row,PBDWObject& dwo,tstring data);
	//返回值：只有0
	virtual long OnItemFocusChanged(long row,PBDWObject& dwo);
	//返回值：0-拒绝输入的数据并显示错误信息框，1-拒绝输入的数据不显示错误信息框
	//		  2-接受数据，3-拒绝数据，允许光标切换
	virtual long OnItemError(long row,PBDWObject& dwo,tstring data);
	//返回值：只有0,继续处理
	virtual long OnLoseFocus();
	//返回值：只有0,继续处理
	virtual long OnPrintEnd(long printPages);
	//返回值：只有0,继续处理
	virtual long OnPrintMarginChange();
	//返回值：0-不要跳过页码，1-跳过页码
	virtual long OnPrintPage(long printNumber,long copy);
	//返回值：只有0,继续处理
	virtual long OnPrintStart(long pagesMax);
	//返回值：只有0,继续处理
	virtual long OnResize (ULONG sizetype,USHORT newwidth,USHORT newheight);
	//返回值：只有0,继续处理
	virtual long OnRetrieveEnd(long rowcount);
	//返回值：0-继续处理,1-不执行检索，2-从数据库检索时不清空原有数据
	virtual long OnRetrieveStart();
	//返回值：只有0
	virtual long OnRowFocusChanged(long currentrow);
	//返回值：0-继续处理（当前行被更改），1-阻止当前被修改
	virtual long OnRowFocusChanging(long currentrow,long newRow);
	//返回值：只有0
	virtual long OnRButtonDown(int xpos,int ypos,long row,PBDWObject& dwo);//鼠标又击
	//返回值：只有0
	virtual long OnScrollHorizontal (long scrollpos,SHORT pane);
	//返回值：只有0
	virtual long OnScrollVertical (long scrollpos);
	//返回值：0继续处理，1-停止处理，2-跳过本次request处理下个request
	virtual long OnSQLPreview(PBSQLPreviewFunction request,PBSQLPreviewType sqltype,tstring sqlsyntax,PBDWBuffer buffer,long row);
	//返回值：只有0,继续处理
	virtual long OnUpdateEnd (long rowsinserted,long rowsupdated,long rowsdeleted);
	//返回值：0-继续处理，1-不执行UPDATE操作
	virtual long OnUpdateStart(void);
#pragma endregion 对应事件
private:
	void SetPBEventReturnValue(long val);
	bool SetWxjOwnerProc();
	static LRESULT CALLBACK CustDWMsgProc(HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam);
	virtual WNDPROC GetWindowProc()
	{
		return CustDWMsgProc ;//WindowProc;
	}
};

END_PBPLUS_NASPACE