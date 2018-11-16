// Widget.h
//

#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "epdpaint.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//

#define WS_TA_LEFT			0x0000 // WidgetStyle_TextAlign: default LEFT, MIDDLE
#define WS_TA_RIGHT			0x0001
#define WS_TA_CENTER		0x0002
#define WS_TA_MIDDLE		0x0000
#define WS_TA_TOP			0x0004
#define WS_TA_BOTTOM		0x0008
#define WS_LA_LEFT			0x0000 // WidgetStyle_LabelAlign: default LEFT
#define WS_LA_RIGHT			0x0010
#define WS_LA_CENTER		0x0020
#define WS_HAS_LABEL		0x0100
#define WS_HAS_BOARDER		0x0200
#define WS_OWNERDRAW		0x8000 // WidgetStyle_OwnerDraw


////////////////////////////////////////////////////////////////////////////////////////////////
//

typedef enum _WidgetContent
{
    Widget_Empty,

	Widget_Speed_Ground,
	Widget_Speed_Air,

	Widget_Date_Current,
	Widget_Time_Current,
	Widget_Time_Flight,

	Widget_Altitude_GPS,
	Widget_Altitude_Baro,
	Widget_Altitude_Takeoff,
	Widget_Altitude_Ref,
	Widget_Altitude_AGL,

	Widget_Glider_Ratio,

	Widget_Vario_Active,
	Widget_Vario_History,
	Widget_Vario_Bar,

	Widget_GPS_Status,
//	Widget_GPS_Speed,
	Widget_GPS_Heading,
	Widget_GPS_Heading_G,
	Widget_GPS_Longigute,
	Widget_GPS_Latitude,

	//Widget_Bearing,
	//Widget_Compass_Heading,
	//Widget_Compass_North,

	Widget_Battery_Power,
	Widget_Bluetooth_Status,
	Widget_Pressure,
	Widget_Temperature,

	Widget_Thermal_Assist
	//Widget_Thermal_Time
	//Widget_Thermal_Gain

} WidgetContent;


typedef struct _Widget Widget;
typedef struct _WidgetStyle WidgetStyle;


typedef struct _Widget
{
	unsigned short cId; // content id
	unsigned short sId; // style id
	unsigned short x, y, w, h;

} Widget;

typedef struct _WidgetStyle
{
	unsigned short style;
	unsigned char bkgndColor;
	unsigned char textColor;
	unsigned char lableFont;
	unsigned char textFont;

} WidgetStyle;

typedef struct _WidgetRepository
{
	unsigned short 	id;

	const char * 	(* getLabel)();
	const char * 	(* getString)();

} WidgetRepository;


////////////////////////////////////////////////////////////////////////////////////////////////
//


//extern Widget 			_widget[];
extern WidgetStyle 		_widgetStyles[];
extern WidgetRepository	_repo[];


////////////////////////////////////////////////////////////////////////////////////////////////
//

void Widget_Draw(Widget * this, Paint * paint);
void Widget_OwnerDraw(Widget * this, Paint * paint);


////////////////////////////////////////////////////////////////////////////////////////////////
//

inline const char * Widget_GetLabel(unsigned short id)
{
	return _repo[id].getLabel();
}

inline const char * Widget_GetString(unsigned short id)
{
	return _repo[id].getString();
}


#endif  // __WIDGET_H__
