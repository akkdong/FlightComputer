// Widget.c
//

#include <stdio.h>
#include <string.h>
#include "Widget.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//

void Widget_Draw(Widget * this, Paint * paint)
{
	WidgetStyle * ws = &_widgetStyles[this->sId];

	if (ws->style & WS_OWNERDRAW)
	{
		Widget_OwnerDraw(this, paint);
	}
	//else if (ws->draw)
	//{
	//	ws->draw(this, paint);
	//}
	else
	{
		// erase background
		Paint_DrawFilledRectangle(paint, this->x, this->y, this->x + this->w - 0, this->y + this->h - 0, ws->bkgndColor);

		// draw frame
		if (ws->style & WS_HAS_BOARDER)
			Paint_DrawRectangle(paint, this->x, this->y, this->x + this->w - 0, this->y + this->h - 0, ws->textColor);

		// draw label
		int x = this->x;
		int y = this->y;
		int w = this->w;
		int h = this->h;

		if (ws->style & WS_HAS_LABEL)
		{
			const char * label = Widget_GetLabel(this->cId);
			sFONT * font = Fonts[ws->lableFont];
			int lx = x + 2;
			int ly = y + 2;

			if (ws->style & WS_LA_RIGHT)
				lx = x + w - (font->Width * strlen((char *)label) + 2);
			else if (ws->style & WS_LA_CENTER)
				lx = x + (w - (font->Width * strlen((char *)label))) / 2;

			Paint_DrawStringAt(paint, lx, ly, label, font, ws->textColor);

			y = ly + font->Height;
			h = h - (font->Height + 2);
		}

		// draw text
		const char * value = Widget_GetString(this->cId);
		sFONT * font = Fonts[ws->textFont];

		if (ws->style & WS_TA_RIGHT)
			x = x + w - (font->Width * strlen((char *)value) + 2);
		else if (ws->style & WS_TA_CENTER)
			x = x + (w - (font->Width * strlen((char *)value))) / 2;

		if (ws->style & WS_TA_TOP)
			y = y + 2;
		else if (ws->style & WS_TA_BOTTOM)
			y = y + h - (font->Height + 2);
		else
			y = y + (h -  font->Height) / 2;

		Paint_DrawStringAt(paint, x, y, value, font, ws->textColor);
	}
}

void Widget_OwnerDraw(Widget * this, Paint * paint)
{
	if (this->cId == Widget_GPS_Heading_G)
	{
		WidgetStyle * ws = &_widgetStyles[this->sId];

		Paint_DrawFilledRectangle(paint, this->x, this->y, this->x + this->w - 0, this->y + this->h - 0, ws->bkgndColor);
		Paint_DrawCircle(paint, this->x + this->w / 2, this->y + this->h / 2, this->w / 2, ws->textColor);
	}
}
