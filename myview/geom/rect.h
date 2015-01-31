/*
 * rect.h
 *
 *  Created on: Sep 19, 2008
 *      Author: jin
 */

#ifndef RECT_H_
#define RECT_H_

#include "painter.h"
#include "type.h"


class Shape {
public:
	virtual void draw( Painter * p )=0;
};
class Rect {
	TLoc x;
	TLoc y;
	TSize width;
	TSize height;
public:
	void draw( Painter *p ){
		p->drawRect(x, y, width, height );
	}
};

#endif /* RECT_H_ */
