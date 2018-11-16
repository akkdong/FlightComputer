// WidgetData.c
//

#include <stdlib.h>
#include <string.h>
#include "Widget.h"
#include "epd4in2.h"
#include "epdif.h"
#include "epdpaint.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//

char _Widget_TempString[16];

#if 0
Widget _widget[] =
{
	{
		0, 0, 60, 16,
		0,
		Widget_Date_Current
	},
	{
		60, 0, 60, 16,
		1,
		Widget_Time_Current
	},
	{
		120, 0, 60, 16,
		6,
		Widget_Battery_Power
	},
	{
		2, 18, 120, 48,
		4,
		Widget_Altitude_GPS
	},
	{
		122, 18, 120, 48,
		4,
		Widget_Speed_Ground
	},
	{
		242, 18, 120, 48,
		4,
		Widget_Vario_Active
	},
	{
		2, 84, 120, 48,
		5,
		Widget_Speed_Air
	},
	{
		140, 132, 160, 160,
		7,
		Widget_GPS_Heading_G
	}
};
#endif

WidgetStyle _widgetStyles[] =
{
	// 0: no label, reverse, center --> for title
	{
		WS_TA_CENTER,
		COLORED,
		UNCOLORED,
		Font_12,
		Font_12
	},
	// 1: no label, center --> for title
	{
		WS_TA_RIGHT | WS_HAS_BOARDER,
		UNCOLORED,
		COLORED,
		Font_12,
		Font_12
	},
	// 2: left aligned label, right aligned text, big font
	{
		WS_LA_LEFT | WS_TA_LEFT | WS_TA_TOP | WS_HAS_LABEL | WS_HAS_BOARDER,
		UNCOLORED,
		COLORED,
		Font_12,
		Font_24
	},
	// 3: left aligned label, right aligned text, small font
	{
		WS_LA_RIGHT | WS_TA_CENTER | WS_TA_MIDDLE | WS_HAS_LABEL | WS_HAS_BOARDER,
		UNCOLORED,
		COLORED,
		Font_12,
		Font_24
	},
	// 4: left aligned label, right aligned text, small font
	{
		WS_LA_LEFT | WS_TA_RIGHT | WS_TA_BOTTOM | WS_HAS_LABEL | WS_HAS_BOARDER,
		UNCOLORED,
		COLORED,
		Font_12,
		Font_24
	},
	// 5: left aligned label, right aligned text, small font
	{
		WS_LA_CENTER | WS_TA_RIGHT | WS_HAS_LABEL | WS_HAS_BOARDER,
		UNCOLORED,
		COLORED,
		Font_12,
		Font_20
	},
	// 6: no label, center --> for title
	{
		WS_TA_LEFT | WS_HAS_BOARDER,
		COLORED,
		UNCOLORED,
		Font_12,
		Font_12
	},
	// 7: owner-draw
	{
		WS_OWNERDRAW,
		UNCOLORED,
		COLORED,
		Font_12,
		Font_12,
	}
};

// Widget_Empty
//

const char * _getLabel__Empty()
{
	return "";
}

const char * _getString__Empty()
{
	return "";
}

// Widget_Speed_Ground
//

const char * _getLabel__Speed_Ground()
{
	return (const char *)"G Speed";
}

const char * _getString__Speed_Ground()
{
	itoa(rand() % 60, &_Widget_TempString[0], 10);
	return (const char *)&_Widget_TempString[0];
}

// Widget_Speed_Air
//

const char * _getLabel__Speed_Air()
{
	return (const char *)"A Speed";
}

const char * _getString__Speed_Air()
{
	itoa(rand() % 60, &_Widget_TempString[0], 10);
	return (const char *)&_Widget_TempString[0];
}

// Widget_Date_Current
//

const char * _getLabel__Date_Current()
{
	return (const char *)"Data";
}

const char * _getString__Date_Current()
{
	return (const char *)"11/15";
}

// Widget_Time_Current
//

const char * _getLabel__Time_Current()
{
	return (const char *)"Time";
}

const char * _getString__Time_Current()
{
	return (const char *)"17:35";
}

// Widget_Time_Flight
//

const char * _getLabel__Time_Flight()
{
	return (const char *)"F Time";
}

const char * _getString__Time_Flight()
{
	return (const char *)"1:30";
}


// Widget_Altitude_GPS
//

const char * _getLabel__Altitude_GPS()
{
	return (const char *)"Altitude";
}

const char * _getString__Altitude_GPS()
{
	return (const char *)"";
}

// Widget_Altitude_Baro
//

const char * _getLabel__Altitude_Baro()
{
	return (const char *)"B Alt";
}

const char * _getString__Altitude_Baro()
{
	return (const char *)"";
}

// Widget_Altitude_Takeoff
//

const char * _getLabel__Altitude_Takeoff()
{
	return (const char *)"T Alt";
}

const char * _getString__Altitude_Takeoff()
{
	return (const char *)"";
}

// Widget_Altitude_Ref
//

const char * _getLabel__Altitude_Ref()
{
	return (const char *)"Ref Alt";
}

const char * _getString__Altitude_Ref()
{
	return (const char *)"";
}

// Widget_Altitude_AGL
//

const char * _getLabel__Altitude_AGL()
{
	return (const char *)"AGL";
}

const char * _getString__Altitude_AGL()
{
	return (const char *)"";
}


// Widget_Glider_Ratio
//

const char * _getLabel__Glider_Ratio()
{
	return (const char *)"LD";
}

const char * _getString__Glider_Ratio()
{
	return (const char *)"";
}

// Widget_Vario_Active
//

const char * _getLabel__Vario_Active()
{
	return (const char *)"Vario";
}

const char * _getString__Vario_Active()
{
	return (const char *)"";
}

// Widget_Vario_History
//

const char * _getLabel__Vario_History()
{
	return (const char *)"V History";
}

const char * _getString__Vario_History()
{
	return (const char *)"";
}

// Widget_Vario_Bar
//

const char * _getLabel__Vario_Bar()
{
	return (const char *)"V Bar";
}

const char * _getString__Vario_Bar()
{
	return (const char *)"";
}

// Widget_GPS_Status
//

const char * _getLabel__GPS_Status()
{
	return (const char *)"GPS";
}

const char * _getString__GPS_Status()
{
	return (const char *)"";
}

// Widget_GPS_Heading
//

const char * _getLabel__GPS_Heading()
{
	return (const char *)"Heading";
}

const char * _getString__GPS_Heading()
{
	return (const char *)"";
}

// Widget_GPS_Heading_G
//

const char * _getLabel__GPS_Heading_G()
{
	return (const char *)"Heading";
}

const char * _getString__GPS_Heading_G()
{
	return (const char *)"";
}

// Widget_GPS_Longigute
//

const char * _getLabel__GPS_Longigute()
{
	return (const char *)"Lon";
}

const char * _getString__GPS_Longigute()
{
	return (const char *)"";
}

// Widget_GPS_Latitude
//

const char * _getLabel__GPS_Latitude()
{
	return (const char *)"Lat";
}

const char * _getString__GPS_Latitude()
{
	return (const char *)"";
}

// Widget_Bearing
//

// Widget_Compass_Heading
//

// Widget_Compass_North
//

// Widget_Battery_Power
//

const char * _getLabel__Battery_Power()
{
	return (const char *)"Bat";
}

const char * _getString__Battery_Power()
{
	return (const char *)"";
}

// Widget_Bluetooth_Status
//

const char * _getLabel__Bluetooth_Status()
{
	return (const char *)"BT";
}

const char * _getString__Bluetooth_Status()
{
	return (const char *)"";
}

// Widget_Pressure
//

const char * _getLabel__Pressure()
{
	return (const char *)"Prs";
}

const char * _getString__Pressure()
{
	return (const char *)"";
}

// Widget_Temperature
//

const char * _getLabel__Temperature()
{
	return (const char *)"Temp";
}

const char * _getString__Temperature()
{
	return (const char *)"";
}

// Widget_Thermal_Assist
//

const char * _getLabel__Thermal_Assist()
{
	return (const char *)"Temp";
}

const char * _getString__Thermal_Assist()
{
	return (const char *)"";
}

// Widget_Thermal_Time
// Widget_Thermal_Gain



WidgetRepository _repo[] =
{
	{
		Widget_Empty,
		_getLabel__Empty,
		_getString__Empty
	},

	{
		Widget_Speed_Ground,
		_getLabel__Speed_Ground,
		_getString__Speed_Ground
	},
	{
		Widget_Speed_Air,
		_getLabel__Speed_Air,
		_getString__Speed_Air
	},

	{
		Widget_Date_Current,
		_getLabel__Date_Current,
		_getString__Date_Current
	},
	{
		Widget_Time_Current,
		_getLabel__Time_Current,
		_getString__Time_Current
	},
	{
		Widget_Time_Flight,
		_getLabel__Time_Flight,
		_getString__Time_Flight
	},

	{
		Widget_Altitude_GPS,
		_getLabel__Altitude_GPS,
		_getString__Altitude_GPS
	},
	{
		Widget_Altitude_Baro,
		_getLabel__Altitude_Baro,
		_getString__Altitude_Baro
	},
	{
		Widget_Altitude_Takeoff,
		_getLabel__Altitude_Takeoff,
		_getString__Altitude_Takeoff
	},
	{
		Widget_Altitude_Ref,
		_getLabel__Altitude_Ref,
		_getString__Altitude_Ref
	},
	{
		Widget_Altitude_AGL,
		_getLabel__Altitude_AGL,
		_getString__Altitude_AGL
	},

	{
		Widget_Glider_Ratio,
		_getLabel__Glider_Ratio,
		_getString__Glider_Ratio
	},

	{
		Widget_Vario_Active,
		_getLabel__Vario_Active,
		_getString__Vario_Active
	},
	{
		Widget_Vario_History,
		_getLabel__Vario_History,
		_getString__Vario_History
	},
	{
		Widget_Vario_Bar,
		_getLabel__Vario_Bar,
		_getString__Vario_Bar
	},

	{
		Widget_GPS_Status,
		_getLabel__GPS_Status,
		_getString__GPS_Status
	},
//	Widget_GPS_Speed,
	{
		Widget_GPS_Heading,
		_getLabel__GPS_Heading,
		_getString__GPS_Heading
	},
	{
		Widget_GPS_Heading_G,
		_getLabel__GPS_Heading_G,
		_getString__GPS_Heading_G
	},
	{
		Widget_GPS_Longigute,
		_getLabel__GPS_Longigute,
		_getString__GPS_Longigute
	},
	{
		Widget_GPS_Latitude,
		_getLabel__GPS_Latitude,
		_getString__GPS_Latitude
	},

	//Widget_Bearing,
	//Widget_Compass_Heading,
	//Widget_Compass_North,

	{
		Widget_Battery_Power,
		_getLabel__Battery_Power,
		_getString__Battery_Power
	},
	{
		Widget_Bluetooth_Status,
		_getLabel__Bluetooth_Status,
		_getString__Bluetooth_Status
	},
	{
		Widget_Pressure,
		_getLabel__Pressure,
		_getString__Pressure
	},
	{
		Widget_Temperature,
		_getLabel__Temperature,
		_getString__Temperature
	},

	{
		Widget_Thermal_Assist,
		_getLabel__Thermal_Assist,
		_getString__Thermal_Assist
	},
	//Widget_Thermal_Time
	//Widget_Thermal_Gain

};
