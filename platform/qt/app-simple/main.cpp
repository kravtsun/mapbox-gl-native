// connect to some vector tiles source.
// retrieve a bunch of tiles and save it to png.

#include <iostream>
#include <QApplication>
#include <QCommandLineParser>
#include <QtDebug>
#include "mapwindow.h"

using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("qmapboxgl-app-simple");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

//    QCommandLineOption renderConfigOption{"config",
//                                          QCoreApplication::translate("main", "Configuration file for rendering."),
//                                          "config",
//                                          "osm-bright.json"};

    QCommandLineOption tilesHost{"host",
                                 QCoreApplication::translate("main", "host of vector tiles."),
                                 "host",
                                 "localhost"};

    QCommandLineOption tilesPort{{"p", "port"},
                                 QCoreApplication::translate("main", "port of vector tiles."),
                                 "port",
                                 "8080"};

    QCommandLineOption styleFile{"config",
                                 QCoreApplication::translate("main", "style file for rendering."),
                                 "config",
                                 "osm-bright.json"};

    parser.addOptions({tilesHost, tilesPort, styleFile});
    qDebug() << QCoreApplication::arguments();
    parser.process(QCoreApplication::arguments());
//    qDebug() << parser.value("config");
//    exit(0);

    QMapboxGLSettings settings;
//    settings.setCacheDatabasePath("/tmp/mbgl-cache.db");
//    settings.setCacheDatabaseMaximumSize(20 * 1024 * 1024);
    const QString apiBaseUrl = "http://" + parser.value(tilesHost) + ":" + parser.value(tilesPort);
    settings.setApiBaseUrl(apiBaseUrl);

    MapWindow window(settings, parser.value(styleFile));
    window.resize(800, 600);
    window.show();

    return app.exec();
}

