/*
 * lv_port.cpp
 *
 *  Created on: 2021. 6. 14.
 *      Author: akkdong
 */

#if SUPPORT_LVGL

#include "lv_port.h"
#include "EPD/EPaperFrameBuffer.h"


#define BIT_SET(a,b) 	((a) |= (1U<<(b)))
#define BIT_CLEAR(a,b) 	((a) &= ~(1U<<(b)))

static void set_px_cb(lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
{
	uint16_t byte_index = x + (( y>>3 ) * buf_w);
	uint8_t  bit_index  = y & 0x7;
	// == 0 inverts, so we get blue on black
	if ( color.full == 0 )
	{
		BIT_SET( buf[ byte_index ] , bit_index );
	}
	else
	{
		BIT_CLEAR( buf[ byte_index ] , bit_index );
	}
}

static void flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
	uint8_t row1 = area->y1 >> 3;
	uint8_t row2 = area->y2 >> 3;
	uint8_t *buf = (uint8_t*) color_p;

	for(uint8_t row = row1; row <= row2; row++)
	{
		//oledStartSend( row, area->x1 );
		for(uint16_t x = area->x1; x <= area->x2; x++)
		{
			//oledByteOut(*buf);
			buf++;
		}
		//oledEndSend();
	}

	/*
	 *  IMPORTANT!!!
	 * Inform the graphics library that you are ready with the flushing
	 */
	lv_disp_flush_ready(disp_drv);
}

static void rounder_cb(lv_disp_drv_t * disp_drv, lv_area_t *area)
{
	area->y1 = (area->y1 & (~0x7));
	area->y2 = (area->y2 & (~0x7)) + 7;
}

#define DISP_WIDTH 		(800)
#define DISP_HEIGHT		(600)
#define DISP_BUF_SIZE	(DISP_WIDTH / 8 * DISP_HEIGHT)


void hal_init(void)
{
	// initialzie display buffer
	static lv_disp_draw_buf_t disp_buf;
	static EPaperFrameBuffer buf_1(DISP_WIDTH, DISP_HEIGHT), buf_2(DISP_WIDTH, DISP_HEIGHT);
	//static lv_color_t buf_1[DISP_BUF_SIZE], buf_2[DISP_BUF_SIZE];

	//lv_disp_draw_buf_init(&disp_buf, buf_1.getPtr(), buf_2.getPtr(), DISP_WIDTH * DISP_HEIGHT);


	// initialize & register display driver
	static lv_disp_drv_t disp_drv;

	lv_disp_drv_init(&disp_drv);
	disp_drv.hor_res = DISP_WIDTH;
	disp_drv.ver_res = DISP_HEIGHT;
	disp_drv.draw_buf = &disp_buf;
	disp_drv.full_refresh = 1;
	disp_drv.flush_cb = flush_cb;
	disp_drv.set_px_cb = set_px_cb;
	disp_drv.rounder_cb = rounder_cb;
	lv_disp_drv_register(&disp_drv);
}


void app_init(void)
{
	// ...

    // set mono theme
	//lv_theme_mono_init(NULL, false, &lv_font_montserrat_10);
    //lv_theme_set_current( lv_theme_get_mono());

	lv_obj_t * label1 = lv_label_create(lv_scr_act());
	lv_label_set_text(label1, LV_SYMBOL_OK);
}

#endif // SUPPORT_LVGL

