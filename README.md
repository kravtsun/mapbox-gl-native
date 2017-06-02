# Mapbox GL Native under Ubuntu 16.04 Qt
## Fork description
This fork is set up for building mapbox-gl-native library and using it with Qt-based application for rendering vector tiles coming from non-mapbox server. Current edits include those required for fluent automatic build.

## USAGE
Run `make run-qt-app` (optionally, with `-j $(nproc)` parameter for speedup).
Optionally one can open QtCreator project at `platform/qt/app` and after specifying path to **qmapboxgl** libraries (current one is `$$PWD/../../../build/qt-linux-x86_64/Debug`) build and run it with your own Qt environment under QtCreator.

Current version of application expects up-and-running vector tiles server set up as follows:
### Install
`npm install tileserver-gl-light`
### Run
```tileserver-gl-light saint-petersburg_russia.mbtiles```

File `saint-petersburg_russia.mbtiles` can be received from [this URL](https://openmaptiles.os.zhdk.cloud.switch.ch/v3.3/extracts/saint-petersburg_russia.mbtiles)

## Prerequisites
* Ubuntu 16.04
* Others can be retrieved with:
```
sudo apt-get install qt5-default cmake make curl libcurl4-openssl-dev npm
```

## Sample usage

```
# set up running vector tiles server:
tileserver-gl-light saint-petersburg_russia.mbtiles

# building qmapboxgl prerequisites:
make -j $(nproc) qt-lib

# building sample app:
cd platform/qt/app-simple && qmake && make

# running app:
LD_LIBRARY_PATH=../../../build/qt-linux-x86_64/Debug ./app-simple --config misc/osm-bright-spb.json --host localhost --port 8080
```
Here field `center` from `misc/osm-bright-spb.json` is used for setting up initial position for map.

## Original description
A library for embedding interactive, customizable vector maps into native applications on multiple platforms. It takes stylesheets that conform to the [Mapbox Style Specification](https://github.com/mapbox/mapbox-gl-style-spec/), applies them to vector tiles that conform to the [Mapbox Vector Tile Specification](https://github.com/mapbox/vector-tile-spec), and renders them using OpenGL. [Mapbox GL JS](https://github.com/mapbox/mapbox-gl-js) is the WebGL-based counterpart, designed for use on the Web.

