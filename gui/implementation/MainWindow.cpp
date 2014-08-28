/*
 * Implementation file for QT main window.
 */

#include <gui/interface/MainWindow.hpp>
#include <gui/interface/GLWidget.hpp>

#include <QCheckBox>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDockWidget>
#include <QGridLayout>
#include <QSignalMapper>
#include <QPushButton>
#include <QKeyEvent>

MainWindow::MainWindow(QMainWindow * parent) : QMainWindow(parent)
{
	setupUi();
	
	connect(uiLoadSceneButton, SIGNAL(clicked()), glWidget, SLOT(loadScene()));
	connect(uiSaveImageButton, SIGNAL(clicked()), glWidget, SLOT(saveImage()));
	connect(uiSamples, SIGNAL(valueChanged(int)), glWidget, SLOT(setPathtracerSamples(int)));
	connect(uiPathtraceButton, SIGNAL(clicked()), glWidget, SLOT(pathtrace()));
	
	connect(uiDebugRay[0], SIGNAL(valueChanged(double)), glWidget, SLOT(debugRayOriginX(double)));
	connect(uiDebugRay[1], SIGNAL(valueChanged(double)), glWidget, SLOT(debugRayOriginY(double)));
	connect(uiDebugRay[2], SIGNAL(valueChanged(double)), glWidget, SLOT(debugRayOriginZ(double)));
	
	connect(uiDebugRay[3], SIGNAL(valueChanged(double)), glWidget, SLOT(debugRayDirectionX(double)));
	connect(uiDebugRay[4], SIGNAL(valueChanged(double)), glWidget, SLOT(debugRayDirectionY(double)));
	connect(uiDebugRay[5], SIGNAL(valueChanged(double)), glWidget, SLOT(debugRayDirectionZ(double)));
	
	connect(uiTraceDebugRay, SIGNAL(clicked()), glWidget, SLOT(traceDebugRay()));

	// default settings
	uiSamples->setValue(64);
	uiSamples->setSingleStep(1);
	
	for (unsigned i = 0; i < 6; i++) {
		uiDebugRay[i]->setValue(0.0);
	}
}

MainWindow::~MainWindow() {

}

void MainWindow::setupUi()
{
	glWidget = new GLWidget();

	setCentralWidget(glWidget);
	
	resize(700, 250);

	setFocusPolicy(Qt::NoFocus);
	setContextMenuPolicy(Qt::ActionsContextMenu);
	setAutoFillBackground(true);

	QGridLayout * layout = new QGridLayout();

	unsigned row = 0;

	uiLoadSceneButton = new QPushButton("Load Scene");
	layout->addWidget(uiLoadSceneButton, row++, 0, 1, 3, Qt::AlignTop);
	
	uiSaveImageButton = new QPushButton("Save Image");
	layout->addWidget(uiSaveImageButton, row++, 0, 1, 3, Qt::AlignTop);
	
	uiSamplesLabel = new QLabel("Samples per pixel");
	layout->addWidget(uiSamplesLabel, row, 0, 1, 2, Qt::AlignTop);
	uiSamples = new QSpinBox();
	uiSamples->setMinimum(1);
	uiSamples->setMaximum(100000);
	layout->addWidget(uiSamples, row++, 2, 1, 1, Qt::AlignTop);
	
// 	uiSamplesLabel = new QLabel("Resolution");
// 	layout->addWidget(uiSamplesLabel, row, 0, 1, 2, Qt::AlignTop);
// 	uiResolution[0] = new QSpinBox();
// 	uiResolution[0]->setMinimum(128);
// 	uiResolution[0]->setMaximum(100000);
// 	layout->addWidget(uiResolution[0], row, 2, 1, 1, Qt::AlignTop);
// 	uiResolution[1] = new QSpinBox();
// 	uiResolution[1]->setMinimum(128);
// 	uiResolution[1]->setMaximum(100000);
// 	layout->addWidget(uiResolution[1], row++, 3, 1, 1, Qt::AlignTop);
	
	uiPathtraceButton = new QPushButton("Render");
	layout->addWidget(uiPathtraceButton, row++, 0, 1, 3, Qt::AlignTop);
	
	uiDebugRayLabel = new QLabel("Debug: Ray");
	layout->addWidget(uiDebugRayLabel, row++, 0, 1, 3, Qt::AlignTop);
	for (unsigned i = 0; i < 3; i++) {
		uiDebugRay[i] = new QDoubleSpinBox();
		uiDebugRay[i]->setMinimum(-10000.0);
		uiDebugRay[i]->setMaximum(10000.0);
		layout->addWidget(uiDebugRay[i], row, i, 1, 1, Qt::AlignTop);
	}
	row++;
	for (unsigned i = 0; i < 3; i++) {
		uiDebugRay[3+i] = new QDoubleSpinBox();
		uiDebugRay[3+i]->setMinimum(-10000.0);
		uiDebugRay[3+i]->setMaximum(10000.0);
		layout->addWidget(uiDebugRay[3+i], row, i, 1, 1, Qt::AlignTop);
	}
	row++;
	
	uiTraceDebugRay = new QPushButton("Trace Debug Ray");
	layout->addWidget(uiTraceDebugRay, row++, 0, 1, 3, Qt::AlignTop);

	uiDock = new QDockWidget();
	QWidget * tmpWidget = new QWidget();
	uiDock->setWidget(tmpWidget);
	tmpWidget->setLayout(layout);
	addDockWidget(Qt::RightDockWidgetArea, uiDock);
}

/////////////////////////////////////////////////////////////////////////

void MainWindow::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
		case Qt::Key_Escape:
			close();
			break;
		default: break;
	}
}




