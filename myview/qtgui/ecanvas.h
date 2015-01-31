/*
 * ecanvas.h
 *
 *  Created on: Oct 30, 2008
 *      Author: jin
 */

#ifndef ECANVAS_H_
#define ECANVAS_H_

#include <iostream.h>
class ECanvas: public QWidget
{
public:
	ECanvas(){

	}

protected:
	void mousePressEvent ( QMouseEvent * e )  {
		cerr<<"hello"<<endl;
	}
};
#endif /* ECANVAS_H_ */
