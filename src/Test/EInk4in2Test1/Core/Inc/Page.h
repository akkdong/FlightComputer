// Page.h
//

#ifndef __PAGE_H__
#define __PAGE_H__

#include "Widget.h"

#define MAX_PAGE		5
#define MAX_WIDGET		16


////////////////////////////////////////////////////////////////////////////////////////////////
//

extern Widget _Page[MAX_PAGE][MAX_WIDGET];



////////////////////////////////////////////////////////////////////////////////////////////////
//

void Page_Draw(int page, Paint * paint);


// Canvas (Display)
// Paint
// Page
//   Widget
//     Region : position, size
//     Stock: font, color, label, text(?), update period(interval, dirty only, every time)
//     Drawing Style: border, background,
//     Style  : font, color, boarder(rect, bottom, right-bottom, ...), label, text, alignment
//     Drawing method
// Content
//
// Content: cId  <--> Drawing method(function)

#endif  // __PAGE_H__
