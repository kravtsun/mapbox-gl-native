#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QOpenGLWidget>
#include <QPropertyAnimation>
#include "qmapboxgl.hpp"


class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

class MapWindow : public QOpenGLWidget
{
public:
    MapWindow(const QMapboxGLSettings &, const QString &styleFile);

private:
    // Q{,Open}GLWidget implementation.
    void initializeGL() final;
    void paintGL() final;

    // QWidget implementation.
    void keyPressEvent(QKeyEvent *ev) final;
    void mousePressEvent(QMouseEvent *ev) final;
    void mouseMoveEvent(QMouseEvent *ev) final;
    void wheelEvent(QWheelEvent *ev) final;

    QPropertyAnimation *m_zoomAnimation;

    QPointF m_lastPos;
    QScopedPointer<QMapboxGL> m_map;

    void resetStyle();
    QString m_styleFile;

    QMapboxGLSettings m_settings;
};

#endif // MAPWINDOW_H
