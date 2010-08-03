#include <QtGui>
#include "cropbag.h"

class MainWin : public QMainWindow {
	
public:
	MainWin(QStringList files);
	
private:
	CropBag *cb;
	QVector<QPixmap> images;
	
protected:
	void keyPressEvent(QKeyEvent *event);
};

MainWin::MainWin(QStringList files) {
	setWindowTitle(tr("Compare images at 100% crop"));
	
	// load and initialize the image pixmaps
	images.resize(files.size());
	for (int i = 0; i < files.size(); i++)
		images[i].load(files[i]);
	
	cb = new CropBag(images);
	setCentralWidget(cb);
	
} 

void MainWin::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_Down:
			cb->scroll(DOWN);
			break;
		case Qt::Key_Up:
			cb->scroll(UP);
			break;
		case Qt::Key_Left:
			cb->scroll(LEFT);
			break;
		case Qt::Key_Right:
			cb->scroll(RIGHT);
			break;
		default:
			event->ignore();
	}
}

int main ( int argc, char* argv[] ) {
	QApplication app(argc, argv);
	QStringList files;
	for (int i = 1; i < argc; i++)
		files << argv[i];
	MainWin mainwin(files);
	mainwin.show();
	return app.exec();
}