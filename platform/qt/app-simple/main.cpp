// connect to some vector tiles source.
// retrieve a bunch of tiles and save it to png.

#include <iostream>
#include <QApplication>
#include "mapwindow.h"

using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QMapboxGLSettings settings;
//    settings.setCacheDatabasePath("/tmp/mbgl-cache.db");
//    settings.setCacheDatabaseMaximumSize(20 * 1024 * 1024);
    settings.setApiBaseUrl("http://localhost:8080");

    MapWindow window(settings);
    window.resize(800, 600);
    window.show();

    return app.exec();
}

