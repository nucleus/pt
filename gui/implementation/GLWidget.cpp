/*
 * Implementation file for OpenGL QT widget.
 */

#include <gui/interface/GLWidget.hpp>

#include <GL/glu.h>
#include <sys/time.h>
#include <qnumeric.h>
#include <QMouseEvent>
#include <QFileDialog>
#include <iostream>
#include <fstream>

#ifdef REPORT_LEVEL
#undef REPORT_LEVEL
#endif

#define REPORT_LEVEL 1
#include <util/interface/Debug.hpp>

/////////////////////////////////////////////////////////////////////////

int GLWidget::f2i(float x) {
	return (int)(x * 255.0f + 0.5f);
}

/////////////////////////////////////////////////////////////////////////

GLWidget::GLWidget(QWidget * parent): m_tracer(m_rendering), m_textureID(0) {
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);
}

/////////////////////////////////////////////////////////////////////////

void GLWidget::initializeGL() {
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glMatrixMode(GL_MODELVIEW);

	setAutoBufferSwap(true);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glGenTextures(1, &m_textureID);
}

void GLWidget::resizeGL(int w, int h) {
	m_width = w & ~1;
	m_height = h & ~1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, m_width, m_height);
	gluOrtho2D(0, m_width, 0, m_height);

	updateGL();
}

void GLWidget::paintGL() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
  
	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 0.0); glVertex3d(-1.0, -1.0, 0.0);
		glTexCoord2d(1.0, 0.0); glVertex3d(1.0, -1.0, 0.0);
		glTexCoord2d(1.0, 1.0); glVertex3d(1.0, 1.0, 0.0);
		glTexCoord2d(0.0, 1.0); glVertex3d(-1.0, 1.0, 0.0);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
}

/////////////////////////////////////////////////////////////////////////

void GLWidget::mouseMoveEvent(QMouseEvent * event) {
	
}

void GLWidget::mousePressEvent(QMouseEvent * event) {
	
}

void GLWidget::wheelEvent(QWheelEvent* event) {
	
}

/////////////////////////////////////////////////////////////////////////

void GLWidget::loadScene() {
	report("GLWidget::loadScene()");
	QString qfile = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
	std::string filename = qfile.toAscii().data();

	// READ MODEL HERE
    
    updateGL();
}

void GLWidget::saveImage() {
	report("GLWidget::saveImage()");
	QString qfile = QFileDialog::getSaveFileName(this, tr("Open File"), "", tr("Files (*.*)"));
	std::string filename = qfile.toAscii().data();
	std::ofstream out(filename.c_str());
	if (!out.good()) { reportE("Could not open output image file"); return; }
	out << "P3\n" << m_width << " " << m_height << "\n255\n";
	for (unsigned y = 0; y < m_height; y++) {
		for (unsigned x = 0; x < m_width; x++) {
			unsigned idx = (m_height-y-1)*m_width + x;
			out << f2i(m_rendering[idx].r) << " " << f2i(m_rendering[idx].g) << " " << f2i(m_rendering[idx].b) << " ";
		}
	}
	out.close();
}

void GLWidget::pathtrace() {
	report("GLWidget::pathtrace()");
  
	// RENDER IMAGE
	m_tracer.render(m_width, m_height);
	
	// DISPLAY OUTPUT
	// bind texture
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// set modulation
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// texture filtering and repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
	// upload texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_FLOAT, &m_rendering[0]);  
	
	updateGL();
}

void GLWidget::traceDebugRay() {
	report("GLWidget::traceDebugRay()");
	m_debugRay = tracer::Ray(m_debugRay.org, glm::normalize(m_debugRay.dir - m_debugRay.org));
	m_tracer.trace(m_debugRay);
}