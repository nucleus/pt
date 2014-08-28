/*
 * Header file for QT main window.
 */

#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QMainWindow * parent = 0);
	~MainWindow();
private:
	void setupUi();

	class GLWidget * glWidget;
	class QDockWidget * uiDock;
	
	class QPushButton* uiLoadSceneButton;
	class QPushButton* uiSaveImageButton;
	
	class QLabel* uiSamplesLabel;
	class QSpinBox* uiSamples;
	
// 	class QLabel* uiResolutionLabel;
// 	class QSpinBox* uiResolution[2];
	
	class QPushButton* uiPathtraceButton;
	
	class QLabel* uiDebugRayLabel;
	class QDoubleSpinBox* uiDebugRay[6];
	
	class QPushButton* uiTraceDebugRay;

public:
	void keyPressEvent(QKeyEvent *event);
	
private slots:
};

#endif
