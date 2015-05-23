/*
* PBConstants.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
BEGIN_PBPLUS_NASPACE
//像素、PB单位的转换方式
//enum PBPixelsToUnitsType
enum PBConvertType
{
	XPixelsToUnits=1,
	YPixelsToUnits=2,
	XUnitsToPixels,
	YUnitsToPixels
};

//Values for specifying the AccessibleRole property for DataWindows and controls in DataWindows.
enum PBAccessibleRole
{
	DefaultRole = 0,
	TitleBarRole= 1,
	MenuBarRole =2,
	ScrollBarRole= 3,
	GripRole = 4,
	SoundRole =5,
	CursorRole= 6,
	CaretRole = 7,
	AlertRole = 8,
	WindowRole = 9,
	ClientRole = 10,
	MenuPopupRole=11,
	MenuItemRole=12,
	ToolTipRole=13,
	ApplicationRole=14,
	DocumentRole=15,
	PaneRole= 16,
	ChartRole =17,
	DialogRole=18,
	BorderRole=19,
	GroupingRole=20,
	SeparatorRole=21,
	ToolBarRole=22,
	StatusBarRole=23,
	TableRole=24,
	ColumnHeaderRole=25,
	RowHeaderRole=26,
	ColumnRole=27,
	RowRole=28,
	CellRole=29,
	LinkRole=30,
	HelpBalloonRole=31,
	CharacterRole=32,
	ListRole=33,
	ListItemRole=34,
	OutlineRole= 35,
	OutlineItemRole=36,
	PageTabRole=37,
	PropertyPageRole=38,
	IndicatorRole=39,
	GraphicRole=40,
	StaticTextRole=41,
	TextRole=42,
	PushButtonRole=43, 
	CheckButtonRole=44,
	RadioButtonRole=45, 
	ComboBoxRole= 46,
	DropListRole= 47, 
	ProgressBarRole=48,
	DialRole=49,
	HotkeyFieldRole=50,
	SliderRole=51,
	SpinButtonRole= 52,
	DiagramRole=53,
	AnimationRole=54,
	EquationRole= 55,
	ButtonDropDownRole=56,
	ButtonMenuRole=57,
	ButtonDropDownGridRole= 58,
	WhiteSpaceRole=59,
	PageTabListRole=60,
	ClockRole=61,
	SplitButtonRole= 62,
	IPAddressRole=63,
	OutlineButtonRole= 64
};
//边框样式
enum PBBorderStyle
{
	StyleNoBorder = 0,
	StyleShadowBox = 1,
	StyleBox = 2,
	StyleResizeBorder = 3,
	StyleUnderline = 4,
	StyleLowered = 5,
	StyleRaised = 6
};
//DataWindow Band
enum PBBand
{
	Detail = 0,
	Header = 1,
	Footer = 2
};

//Values for specifying when a font toolbar appears for a DataWindow.
enum PBRichTextToolbarActivation
{
	RichTextToolbarActivationNever = 0,//Never displays a rich text toolbar
	RichTextToolbarActivationOnEdit = 1,//Displays a rich text toolbar whenever a column with the rich text edit style has focus. This is the default setting.
	RichTextToolbarActivationAlways = 2//Displays a rich text toolbar at all times when the DataWindow is visible.
};

enum PBDWBuffer
{
	Primary=0,
	Delete=1,
	Filter=2
};

enum PBSQLPreviewFunction
{
	PreviewFunctionRetrieve=1,//调用datawindow的Retrieve方法
	PreviewFunctionReselectRow=2,//调用Datawindow的ReselectRow方法
	PreviewFunctionUpdate=3//调用datawindow的update方法
};

enum PBSQLPreviewType
{
	PreviewSelect=1,//A SELECT statement
	PreviewInsert=2,//An INSERT statement
	PreviewDelete=3,//A DELETE statement
	PreviewUpdate=4//An UPDATE statement
};

//执行函数类型
enum PBFunctionType
{
	PBSystemFunctions=0,
	PBUserDefineFuctions
};

END_PBPLUS_NASPACE
