/*
 * Implementation of main function to launch CG2EX2 QT application.
 */

#include <QApplication>

#include <gui/interface/MainWindow.hpp>

int main(int argc, char * argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

