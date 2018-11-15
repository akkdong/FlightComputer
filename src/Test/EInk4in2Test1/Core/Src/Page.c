// Page.c
//

#include "Page.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//

Widget _Page[MAX_PAGE][MAX_WIDGET] =
{
		// Page 0
		{
				// Widget #00
				{
					Widget_Date_Current,
					0,
					0, 0, 60, 16
				},
				// Widget #01
				{
					Widget_Time_Current,
					1,
					60, 0, 60, 16
				},
				// Widget #02
				{
					Widget_Time_Flight,
					0,
					400-60, 0, 60, 16
				},
				// Widget #03
				{
					Widget_Speed_Ground,
					4,
					0, 20, 86, 42
				},
				// Widget #04
				{
					Widget_Speed_Air,
					4,
					86, 20, 86, 42
				},
				// Widget #05
				{
						Widget_Altitude_GPS,
					4,
					172, 20, 86, 42
				},
				// Widget #06
				{
						Widget_Altitude_Baro,
					4,
					258, 20, 86, 42
				},
				// Widget #07
				{
					Widget_Glider_Ratio,
					4,
					0, 62, 86, 42
				},
				// Widget #08
				{
					Widget_Altitude_AGL,
					4,
					86, 62, 86, 42
				},
				// Widget #09
				{
					Widget_Temperature,
					4,
					172, 62, 86, 42
				},
				// Widget #10
				{
						Widget_GPS_Heading,
					4,
					258, 62, 86, 42
				},
				{
					Widget_Empty
				}
		},
		// Page 1
		{
				// Widget #00
				{
					Widget_Empty,
					0,
					0, 0, 0, 0
				},
		},
		// Page 2
		{
				// Widget #00
				{
					Widget_Empty,
					0,
					0, 0, 0, 0
				},
		},
		// Page 3
		{
				// Widget #00
				{
					Widget_Empty,
					0,
					0, 0, 0, 0
				},
		},
		// Page 4
		{
				// Widget #00
				{
					Widget_Empty,
					0,
					0, 0, 0, 0
				},
		}
};



////////////////////////////////////////////////////////////////////////////////////////////////
//

void Page_Draw(int pId, Paint * paint)
{
	Widget * widget = &_Page[pId][0];

	for (int i = 0; i < MAX_WIDGET; i++)
	{
		if (widget[i].cId == Widget_Empty)
			break;

		Widget_Draw(&widget[i], paint);
	}
}
