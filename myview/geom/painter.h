/*
 * painter.h
 *
 *  Created on: Sep 19, 2008
 *      Author: jin
 */

#ifndef PAINTER_H_
#define PAINTER_H

#include "type.h"
class Painter {
public:
	virtual void drawRect( TLoc x, TLoc y, TSize w, TSize h )=0;
};

#endif /* PAINTER_H_ */
