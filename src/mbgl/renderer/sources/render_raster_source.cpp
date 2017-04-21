#include <mbgl/renderer/sources/render_raster_source.hpp>
#include <mbgl/renderer/render_tile.hpp>
#include <mbgl/style/sources/raster_source.hpp>
#include <mbgl/style/sources/raster_source_impl.hpp>
#include <mbgl/tile/raster_tile.hpp>

namespace mbgl {

using namespace style;

RenderRasterSource::RenderRasterSource(style::RasterSource& source_)
    : source(source_) {
}

bool RenderRasterSource::isLoaded() const {
    return tilePyramid.isLoaded();
}

void RenderRasterSource::invalidateTiles() {
    tilePyramid.invalidateTiles();
}

void RenderRasterSource::startRender(algorithm::ClipIDGenerator&, const mat4& matrix, const TransformState& transform) {
    tilePyramid.startRender(matrix, transform);
}

void RenderRasterSource::finishRender(Painter& painter) {
    tilePyramid.finishRender(painter);
}

std::map<UnwrappedTileID, RenderTile>& RenderRasterSource::getRenderTiles() {
    return tilePyramid.getRenderTiles();
}

void RenderRasterSource::updateTiles(const UpdateParameters& parameters) {
    optional<Tileset> tileset = source.impl->getTileset();

    if (!tileset) {
        return;
    }

    if (tileURLTemplates != tileset->tiles) {
        tileURLTemplates = tileset->tiles;
        tilePyramid.invalidateTiles();
    }

    tilePyramid.updateTiles(parameters,
                            SourceType::Raster,
                            source.impl->getTileSize(),
                            tileset->zoomRange,
                            [&] (const OverscaledTileID& tileID) {
                                return std::make_unique<RasterTile>(tileID, parameters, *tileset);
                            });
}

void RenderRasterSource::removeTiles() {
    tilePyramid.removeTiles();
}

void RenderRasterSource::reloadTiles() {
    tilePyramid.reloadTiles();
}

std::unordered_map<std::string, std::vector<Feature>>
RenderRasterSource::queryRenderedFeatures(const ScreenLineString&,
                                          const TransformState&,
                                          const RenderedQueryOptions&) const {
    return {};
}

std::vector<Feature> RenderRasterSource::querySourceFeatures(const SourceQueryOptions&) {
    return {};
}

void RenderRasterSource::setCacheSize(size_t size) {
    tilePyramid.setCacheSize(size);
}

void RenderRasterSource::onLowMemory() {
    tilePyramid.onLowMemory();
}

void RenderRasterSource::setObserver(TileObserver* observer) {
    tilePyramid.setObserver(observer);
}

void RenderRasterSource::dumpDebugLogs() const {
    tilePyramid.dumpDebugLogs();
}

} // namespace mbgl
