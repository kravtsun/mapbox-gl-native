#include <mbgl/renderer/sources/render_vector_source.hpp>
#include <mbgl/renderer/render_tile.hpp>
#include <mbgl/style/sources/vector_source.hpp>
#include <mbgl/style/sources/vector_source_impl.hpp>
#include <mbgl/tile/vector_tile.hpp>
#include <mbgl/util/constants.cpp>

#include <mbgl/algorithm/generate_clip_ids.hpp>
#include <mbgl/algorithm/generate_clip_ids_impl.hpp>

namespace mbgl {

using namespace style;

RenderVectorSource::RenderVectorSource(style::VectorSource& source_)
    : source(source_) {
}

bool RenderVectorSource::isLoaded() const {
    return tilePyramid.isLoaded();
}

void RenderVectorSource::invalidateTiles() {
    tilePyramid.invalidateTiles();
}

void RenderVectorSource::startRender(algorithm::ClipIDGenerator& generator, const mat4& matrix, const TransformState& transform) {
    generator.update(tilePyramid.getRenderTiles());
    tilePyramid.startRender(matrix, transform);
}

void RenderVectorSource::finishRender(Painter& painter) {
    tilePyramid.finishRender(painter);
}

std::map<UnwrappedTileID, RenderTile>& RenderVectorSource::getRenderTiles() {
    return tilePyramid.getRenderTiles();
}

void RenderVectorSource::updateTiles(const UpdateParameters& parameters) {
    optional<Tileset> tileset = source.impl->getTileset();

    if (!tileset) {
        return;
    }

    if (tileURLTemplates != tileset->tiles) {
        tileURLTemplates = tileset->tiles;
        tilePyramid.invalidateTiles();
    }

    tilePyramid.updateTiles(parameters,
                            SourceType::Vector,
                            util::tileSize,
                            tileset->zoomRange,
                            [&] (const OverscaledTileID& tileID) {
                                return std::make_unique<VectorTile>(tileID, source.impl->id, parameters, *tileset);
                            });
}

void RenderVectorSource::removeTiles() {
    tilePyramid.removeTiles();
}

void RenderVectorSource::reloadTiles() {
    tilePyramid.reloadTiles();
}

std::unordered_map<std::string, std::vector<Feature>>
RenderVectorSource::queryRenderedFeatures(const ScreenLineString& geometry,
                                          const TransformState& transformState,
                                          const RenderedQueryOptions& options) const {
    return tilePyramid.queryRenderedFeatures(geometry, transformState, options);
}

std::vector<Feature> RenderVectorSource::querySourceFeatures(const SourceQueryOptions& options) {
    return tilePyramid.querySourceFeatures(options);
}

void RenderVectorSource::setCacheSize(size_t size) {
    tilePyramid.setCacheSize(size);
}

void RenderVectorSource::onLowMemory() {
    tilePyramid.onLowMemory();
}

void RenderVectorSource::setObserver(TileObserver* observer) {
    tilePyramid.setObserver(observer);
}

void RenderVectorSource::dumpDebugLogs() const {
    tilePyramid.dumpDebugLogs();
}

} // namespace mbgl
