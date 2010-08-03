#ifndef CROPBAG_H
#define CROPBAG_H

#include <QtGui>

enum direction {UP, DOWN, LEFT, RIGHT};

class CropBag : public QWidget {
	Q_OBJECT
	
public:
	CropBag(QVector<QPixmap> &initphotos, QSize initsize = QSize(400, 400));
	virtual QSize sizeHint() const;

public slots:
	void scroll(direction dir);  // scroll all photos in specified direction

protected:
	QVector<QPixmap> photos;  // all the image data
	QSize slicesize;   // the size of each image displayed at a time
	int gridx, gridy;  // we display image slices in a gridx by gridy grid
	QRect position;  // where we are in the parent pictures
	
	void setGridSize(int num);  // figure out optimal grid size
	QRect canvasPos(int num);   // where any given photo is on the canvas
	void paintEvent(QPaintEvent *event);
};	

#endif
