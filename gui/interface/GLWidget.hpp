/*
 * Header file for OpenGL QT widget.
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include <tracer/interface/Pathtracer.hpp>

class GLWidget : public QGLWidget {
	Q_OBJECT
public:
	explicit GLWidget(QWidget * parent = 0);
	
public:
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);

	void wheelEvent(QWheelEvent* event);

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	
protected:
	tracer::Pathtracer::Image m_rendering;
	tracer::Pathtracer m_tracer;
	
	tracer::Ray m_debugRay;
	
protected:
	unsigned m_textureID;
	unsigned m_width, m_height;
	
	bool m_enableGPU;
	
public:
	static int f2i(float x);
	
signals:

public slots:
	void enableCPUDevice() { m_enableGPU = false; }
	void enableGPUDevice() { m_enableGPU = false; }
	void setPathtracerSamples(int samples) { m_tracer.setSamples(samples); }

	void debugRayOriginX(double x) { m_debugRay.org.x = x; }
	void debugRayOriginY(double y) { m_debugRay.org.y = y; }
	void debugRayOriginZ(double z) { m_debugRay.org.z = z; }
	
	void debugRayDirectionX(double x) { m_debugRay.dir.x = x; }
	void debugRayDirectionY(double y) { m_debugRay.dir.y = y; }
	void debugRayDirectionZ(double z) { m_debugRay.dir.z = z; }
	
	void loadScene();
	void saveImage();
	void pathtrace();
	void traceDebugRay();
};

#endif // GLWIDGET_H
