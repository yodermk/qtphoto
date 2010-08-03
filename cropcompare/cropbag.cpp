#include <iostream>
#include "cropbag.h"

CropBag::CropBag ( QVector<QPixmap> &initphotos, QSize initsize ) :
	photos(initphotos), slicesize(initsize) {
	
	setGridSize(photos.size());
	position = QRect(QPoint(0,0), slicesize);
}	
	
void CropBag::setGridSize(int num) {
	/* calculate optimal size of grid for the number of photos */
	
	// right now it's simplistic
	if (num < 6) {
		gridx = num;
		gridy = 1;
	} else {
		gridx = 5;
		gridy = num % 5 + 1;
	}
	
	// set widget size
	resize(gridx*slicesize.width(), gridy*slicesize.height());
}

void CropBag::scroll(direction dir) {
	switch(dir) {
		case DOWN:
			position.translate(0, 20);
			break;
		case UP:
			position.translate(0, -20);
			break;
		case LEFT:
			position.translate(-20, 0);
			break;
		case RIGHT:
			position.translate(20, 0);
	}
	update();
}

QRect CropBag::canvasPos(int num) {
	int row = num / gridx;
	int col = num % gridx;
	return QRect(QPoint(col*slicesize.width(), row*slicesize.height()), slicesize); 
}

QSize CropBag::sizeHint() const {
	return QSize(gridx*slicesize.width(), gridy*slicesize.height());
}

void CropBag::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	for (int n = 0; n<photos.size(); n++)
		painter.drawPixmap(canvasPos(n), photos[n], position);
}
