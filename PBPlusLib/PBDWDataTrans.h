/*
* PBDWDataTrans.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
BEGIN_PBPLUS_NASPACE
typedef struct _dwDataTrans
{
	short xPos;
	short yPos;
	long row;
	tstring data;
	PBDWObject dwo;
	long rtlVal;
	PBSQLPreviewFunction request;
	PBSQLPreviewType sqltype;
	tstring sqlsyntax;
	PBDWBuffer buffer;
	long sqlDBCode;
	tstring sqlErrText;
	long currentRow;
	long newRow;
	long pagesPrinted;
	long pageNumber;
	long copy;
	long pagesMax;
	unsigned long sizetype;
	SHORT newWidth;
	SHORT newHeight;
	long rowCount;
	long scrollpos;
	SHORT pane;
	long RowsInserted;
	long RowsUpdated;
	long RowsDeleted;
	_dwDataTrans(IPB_Session* s):dwo(s){};
}*PDwDataTrans;
//typedef struct _dwClicked
//{
//	short xPos;
//	short yPos;
//	long row;
//	PBDWObject dwo;
//	long rtlVal;
//	_dwClicked(IPB_Session* s):dwo(s){};
//}*PDwClicked;

END_PBPLUS_NASPACE