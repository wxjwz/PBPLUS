#include "stdafx.h"
//#include "windowsx.h"
#include "PBProj.h"
//#include <sstream>
BEGIN_PBPLUS_NASPACE
typedef PBXEXPORT PBXRESULT (*P_PB_GetVM)(IPB_VM** vm);

CPBProj::CPBProj(tstring& t)
{
	session = nullptr;
	pbvm = nullptr;
	win = nullptr;
	hinst =NULL;
	//TCHAR szPath[MAX_PATH];
	tstring dir;
	if(t.length()>0)
		dir.assign(t + _T("\\"));
	else
		dir.assign(_T(""));
	/*if( GetModuleFileName( NULL, szPath, MAX_PATH ) )
		::MessageBox(NULL,szPath,_T("modu"),MB_OK);*/

	/*LPWSTR buff = new wchar_t[256];
		::GetCurrentDirectory(256,buff);
		::MessageBox(NULL,buff,_T("dll"),MB_OK);
*/
	tstring PBVMDLL;
#ifdef PB9
	PBVMDLL = dir+ _T("PBVM90.DLL");
#else
	PBVMDLL = dir+ _T("PBVM125.DLL");
#endif
	hinst = LoadLibrary(PBVMDLL.c_str());
	if(hinst == NULL)
	{
		return;
	}
	P_PB_GetVM getvm = (P_PB_GetVM)GetProcAddress(hinst,"PB_GetVM");
	if (getvm == NULL)
	{
		return;
	}
	getvm(&pbvm);
	if (pbvm == nullptr)
	{
		return;
	}
	tstring tmpList =(dir + _T("libjmsvcrt.dll")).c_str();
	LPCTSTR liblist[]={tmpList.c_str()};
	PBXRESULT pbxC;
//#ifdef _UNICODE
	pbxC = pbvm->CreateSession(_T("libjmsvcrt"), liblist, 1,&session);
//#else
//	pbxC = pbvm->CreateSession(_T("app"), liblist, 1,&session);
//#endif
	//::MessageBox(NULL,liblist,_T("dll"),MB_OK);
	
	if ( pbxC != PBX_OK )
	{
		return;
	}
	//PBSystem::AddToLibraryList(session,(dir + _T("appdemo.pbd")).c_str());
	//pbvm->CreateSession(_T("app"), liblist, 1,&session);
	win = new PBWindow(session);
	PBSystem::Open(session,_T("nwxj230506011bc87"),win);
	win->Hide();

	dw = new PBDataWindow(session);
}
CPBProj::~CPBProj(void)
{
	/*session->FreeCallInfo(&ci);
	delete &ci;*/
	// Release session
	if(trans != nullptr)delete trans;
	if(dw != nullptr) delete dw;
	if(win != nullptr)delete win;
	session->Release();
	session = nullptr;
	FreeLibrary(hinst);
}

HWND CPBProj::CreateDataWindow(tstring& dataobject, int w,int height)
{
	win->OpenUserObject(_T("nwxj230506011ab87"),*dw,0,0);
	//
	//PBCallInfo ci;
	//PBXInvokeFunc<void>(session,dw->cls,dw->obj,_T("of_register"),_T("Q"));
	if(dataobject.length()>0)
	dw->DataObject=dataobject;
	
	/*SHORT pbwidth = PBSystem::PixelsToUnits(session,w,XPixelsToUnits);
	SHORT pbheight = PBSystem::PixelsToUnits(session,height,YPixelsToUnits);
	dw->Resize(pbwidth,pbheight);
	win->Resize(pbwidth,pbheight);*/
	ResizeDataWindow(w,height);
	HWND hwndc = PBSystem::Handle(session,dw->obj);

	return hwndc;
}
void CPBProj::CreateTrans()
{
	trans = new PBTransAction(session);
	trans->CreateSelfInstance();
	trans->DBMS=_T("ODBC");
	trans->AutoCommit=false;
	trans->DBParm=_T("ConnectString='DSN=EAS Demo DB V125;UID=dba;PWD=sql'");
	trans->Connect();
	long sqlCode = trans->SQLCode;
	if(sqlCode != 0)
	{
		tstring str = trans->SQLErrText;
		MessageBox(NULL,str.c_str(),_T(""),MB_OK);
	}
	else
	{
		/*tstring err;
		tstring syn = trans->SyntaxFromSQL(_T("select timeslice,high ,low,amount  from stock"),_T(""),err);
		dw->Create(syn);*/
		/*dw->SetTransObject(*trans);
		dw->Retrieve();*/
	}
	//trans->DisConnect();//Ïàµ±ÓÚdisconnect using trans
}

void CPBProj::ResizeDataWindow(int width,int height)
{
	SHORT pbwidth = PBSystem::PixelsToUnits(session,width,XPixelsToUnits);
	SHORT pbheight = PBSystem::PixelsToUnits(session,height,YPixelsToUnits);
	dw->Resize(pbwidth,pbheight);
	win->Resize(pbwidth,pbheight);
}


HWND CPBProj::GetCanvas()
{
	HWND handle = PBSystem::Handle(session,win->obj);
	return handle;
}
void CPBProj::AcceptText()
{
	dw->AcceptText();
}
void CPBProj::ShowCanvas(bool show)
{
	if(win != nullptr)
	{
		(show == true)? win->Show(): win->Hide();
	}
}

END_PBPLUS_NASPACE