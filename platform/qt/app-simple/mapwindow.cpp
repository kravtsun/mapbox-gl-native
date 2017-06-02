#include "mapwindow.h"

#include <QApplication>
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QIcon>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QString>
#include <QFileDialog>

#include <QtDebug>

#include <QCheckBox>
#include <QPushButton>
#include <QScrollArea>
#include <QPair>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <algorithm>
#include <functional>

#if QT_VERSION >= 0x050000
#include <QWindow>
#endif

MapWindow::MapWindow(const QMapboxGLSettings &settings, const QString &styleFile)
    : m_styleFile(styleFile)
    , m_settings(settings)
{
    setWindowIcon(QIcon(":icon.png"));
//    QWidget *checkboxWindow = new QWidget(static_cast<QWidget *>(this));
    QWidget *checkboxWindow = new QWidget;
//    checkboxWindow->resize(640, 480);
    m_checkbox_layout = new QGridLayout;
    checkboxWindow->setLayout(m_checkbox_layout);

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->resize(400, 800);
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(checkboxWindow);
    scrollArea->setWindowTitle("Layers");
    scrollArea->show();
}

void MapWindow::keyPressEvent(QKeyEvent *ev) {
    QString file;
    QString layer = "place-other";
    static bool visibility = false;

    switch(ev->key()) {
    case Qt::Key_S:
        //            grabFramebuffer().save("tmp.png");

        //            QImage img(size(), QImage::Format_RGB32);
        //            QPainter painter(&img);
        //            render(&painter);
        //            img.save("file.png");

        file = QFileDialog::getSaveFileName(this,
                                            "Save as...",
                                            "name.png",
                                            "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");

        grab().save(file);
        break;
    case Qt::Key_L:
        toggleLayer(layer, !visibility);
        visibility = !visibility;
        break;
    case Qt::Key_Q:
        QOpenGLWidget::close();
        break;
    }
}

void MapWindow::mousePressEvent(QMouseEvent *ev)
{
#if QT_VERSION < 0x050000
    m_lastPos = ev->posF();
#else
    m_lastPos = ev->localPos();
#endif

    if (ev->type() == QEvent::MouseButtonDblClick) {
        if (ev->buttons() == Qt::LeftButton) {
            m_map->scaleBy(2.0, m_lastPos);
        } else if (ev->buttons() == Qt::RightButton) {
            m_map->scaleBy(0.5, m_lastPos);
        }
    }

    ev->accept();
}

void MapWindow::mouseMoveEvent(QMouseEvent *ev)
{
#if QT_VERSION < 0x050000
    QPointF delta = ev->posF() - m_lastPos;
#else
    QPointF delta = ev->localPos() - m_lastPos;
#endif

    if (!delta.isNull()) {
        if (ev->buttons() == Qt::LeftButton && ev->modifiers() & Qt::ShiftModifier) {
            m_map->setPitch(m_map->pitch() - delta.y());
        } else if (ev->buttons() == Qt::LeftButton) {
            m_map->moveBy(delta);
        } else if (ev->buttons() == Qt::RightButton) {
#if QT_VERSION < 0x050000
            m_map->rotateBy(m_lastPos, ev->posF());
#else
            m_map->rotateBy(m_lastPos, ev->localPos());
#endif
        }
    }

#if QT_VERSION < 0x050000
    m_lastPos = ev->posF();
#else
    m_lastPos = ev->localPos();
#endif
    ev->accept();
}

void MapWindow::wheelEvent(QWheelEvent *ev)
{
    if (ev->orientation() == Qt::Horizontal) {
        return;
    }

    float factor = ev->delta() / 1200.;
    if (ev->delta() < 0) {
        factor = factor > -1 ? factor : 1 / factor;
    }

    m_map->scaleBy(1 + factor, ev->pos());
    ev->accept();
}

void MapWindow::toggleLayer(QString layer, bool state) {
//    QString layer = "place-other";
    if (m_map->layerExists(layer)) {
//        m_map->removeLayer(layer);
        m_map->setLayoutProperty(layer, "visibility", state ? "visible" : "none");
    }
//    resetStyle();
}

void MapWindow::resetStyle()
{
    QString stylePath = QDir(QDir::currentPath()).absoluteFilePath(m_styleFile);
    QString styleUrl = QUrl::fromLocalFile(stylePath).toString();
    qDebug() << "Setting style: " << styleUrl;
    m_map->setStyleUrl(styleUrl);

    QFile styleJsonFile(stylePath);
    styleJsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    Q_ASSERT(styleJsonFile.isOpen());
    QJsonDocument styleJson = QJsonDocument::fromJson(styleJsonFile.readAll());
    QJsonObject styleObject = styleJson.object();
    QJsonArray layersArray = styleObject.value("layers").toArray();

    if (styleObject.contains("center")) {
        auto centerArray = styleObject.value("center").toArray();
        QMapbox::Coordinate centerCoordinates = qMakePair(centerArray.at(0).toDouble(), centerArray.at(1).toDouble());
//        qDebug() << center;
        m_map->setCoordinate(centerCoordinates);
    }

    auto toLayerId = [](const QJsonValue &value) {
        return value.toObject().value("id").toString();
    };
    std::transform(layersArray.begin(), layersArray.end(), std::back_inserter(m_layers), toLayerId);

    for (auto const &layer : m_layers) {
        QCheckBox *checkbox = new QCheckBox(this);
        checkbox->setCheckState(Qt::CheckState::Checked);
        checkbox->setText(layer);
        using namespace std::placeholders;
        auto b = std::bind(&MapWindow::toggleLayer, this, layer, _1);
        connect(checkbox, &QCheckBox::toggled, b);
        m_checkbox_layout->addWidget(checkbox);
    }

//    m_map.reset(new QMapboxGL(nullptr, m_settings, size(), devicePixelRatio()));
//    m_map->needsRendering();
//    m_map->mapChanged(QMapboxGL::MapChangeSourceDidChange);
}

void MapWindow::initializeGL() {
    m_map.reset(new QMapboxGL(nullptr, m_settings, size(), devicePixelRatio()));
    connect(m_map.data(), SIGNAL(needsRendering()), this, SLOT(update()));

    // lat,long.
    QMapbox::Coordinate spbCoordinates{59.9505, 30.3505};
//    QMapbox::Coordinate taganrogCoordinates{47.2396, 38.8799};

//    m_map->setCoordinateZoom(QMapbox::Coordinate(8.5693359375,47.39804691303085), 13);
    m_map->setCoordinateZoom(spbCoordinates, 11);
    resetStyle();

    m_zoomAnimation = new QPropertyAnimation(m_map.data(), "zoom");
//    connect(m_zoomAnimation, SIGNAL(finished()), this, SLOT(animationFinished()));
//    connect(m_zoomAnimation, SIGNAL(valueChanged(const QVariant&)), this, SLOT(animationValueChanged()));
}

void MapWindow::paintGL() {
    m_map->resize(size(), size() * devicePixelRatio());
#if QT_VERSION >= 0x050400
    // When we're using QOpenGLWidget, we need to tell Mapbox GL about the framebuffer we're using.
    m_map->setFramebufferObject(defaultFramebufferObject());
#endif
    m_map->render();
}
