// connect to some vector tiles source.
// retrieve a bunch of tiles and save it to png.

#include <iostream>
#include <QApplication>
#include <QOpenGLWidget>
#include <QPainter>
#include <QFileDialog>
#include <QKeyEvent>

#include "qmapboxgl.hpp"
using namespace std;

struct MapWindow : public QOpenGLWidget {
public:
    MapWindow(const QMapboxGLSettings &settings)
        : m_settings(settings)
    {
    }

    // Q{,Open}GLWidget implementation.
    void initializeGL() override {
        m_map.reset(new QMapboxGL(nullptr, m_settings, size(), devicePixelRatio()));
        connect(m_map.data(), SIGNAL(needsRendering()), this, SLOT(update()));

        // Set default location to Saint-Petersburg.
        m_map->setCoordinateZoom(QMapbox::Coordinate(59.9505, 30.1705), 10);

        QString styleUrl = "http://localhost:8080/styles/klokantech-basic.json";
        m_map->setStyleUrl(styleUrl);
    }

    void paintGL() override {
        m_map->resize(size(), size() * devicePixelRatio());
#if QT_VERSION >= 0x050400
        // When we're using QOpenGLWidget, we need to tell Mapbox GL about the framebuffer we're using.
        m_map->setFramebufferObject(defaultFramebufferObject());
#endif
        m_map->render();
    }

    void keyPressEvent(QKeyEvent *ev) override {
        QString file;
        switch(ev->key()) {
        case Qt::Key_S:
            //            grabFramebuffer().save("tmp.png");

            //            QImage img(size(), QImage::Format_RGB32);
            //            QPainter painter(&img);
            //            render(&painter);
            //            img.save("file.png");

            file = QFileDialog::getSaveFileName(this,
                                                "Save as...",
                                                "name",
                                                "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
            grab().save(file);
            break;
        case Qt::Key_Q:
            QOpenGLWidget::close();
            break;
        }
    }

private:
    QScopedPointer<QMapboxGL> m_map;
    QMapboxGLSettings m_settings;
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QMapboxGLSettings settings;
    settings.setCacheDatabasePath("/tmp/mbgl-cache.db");
    settings.setCacheDatabaseMaximumSize(20 * 1024 * 1024);
    settings.setApiBaseUrl("http://localhost:8080");

    MapWindow window(settings);
    window.resize(800, 600);
    window.show();

    //    app.exit(0);
    return app.exec();
}

