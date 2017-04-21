#include <mbgl/renderer/sources/render_geojson_source.hpp>
#include <mbgl/renderer/render_tile.hpp>
#include <mbgl/style/sources/geojson_source.hpp>
#include <mbgl/style/sources/geojson_source_impl.hpp>
#include <mbgl/tile/geojson_tile.hpp>

#include <mbgl/algorithm/generate_clip_ids.hpp>
#include <mbgl/algorithm/generate_clip_ids_impl.hpp>

namespace mbgl {

using namespace style;

RenderGeoJSONSource::RenderGeoJSONSource(style::GeoJSONSource& source_)
    : source(source_) {
}

bool RenderGeoJSONSource::isLoaded() const {
    return tilePyramid.isLoaded();
}

void RenderGeoJSONSource::invalidateTiles() {
    tilePyramid.invalidateTiles();
}

void RenderGeoJSONSource::startRender(algorithm::ClipIDGenerator& generator, const mat4& matrix, const TransformState& transform) {
    generator.update(tilePyramid.getRenderTiles());
    tilePyramid.startRender(matrix, transform);
}

void RenderGeoJSONSource::finishRender(Painter& painter) {
    tilePyramid.finishRender(painter);
}

std::map<UnwrappedTileID, RenderTile>& RenderGeoJSONSource::getRenderTiles() {
    return tilePyramid.getRenderTiles();
}

void RenderGeoJSONSource::updateTiles(const UpdateParameters& parameters) {
    if (!source.impl->loaded) {
        return;
    }

//    if (a != b) {
//        tilePyramid.cache.clear();
//
//        for (auto const& item : tilePyramid.tiles) {
//            static_cast<GeoJSONTile*>(item.second.get())
//                ->updateData(source.impl->getTileData(item.first.canonical));
//        }
//    }

    tilePyramid.updateTiles(parameters,
                            SourceType::GeoJSON,
                            util::tileSize,
                            source.impl->getZoomRange(),
                            [&] (const OverscaledTileID& tileID) {
                                return std::make_unique<GeoJSONTile>(tileID, source.impl->id, parameters,
                                    source.impl->getTileData(tileID.canonical));
                            });
}

void RenderGeoJSONSource::removeTiles() {
    tilePyramid.removeTiles();
}

void RenderGeoJSONSource::reloadTiles() {
    tilePyramid.reloadTiles();
}

std::unordered_map<std::string, std::vector<Feature>>
RenderGeoJSONSource::queryRenderedFeatures(const ScreenLineString& geometry,
                                          const TransformState& transformState,
                                          const RenderedQueryOptions& options) const {
    return tilePyramid.queryRenderedFeatures(geometry, transformState, options);
}

std::vector<Feature> RenderGeoJSONSource::querySourceFeatures(const SourceQueryOptions& options) {
    return tilePyramid.querySourceFeatures(options);
}

void RenderGeoJSONSource::setCacheSize(size_t size) {
    tilePyramid.setCacheSize(size);
}

void RenderGeoJSONSource::onLowMemory() {
    tilePyramid.onLowMemory();
}

void RenderGeoJSONSource::setObserver(TileObserver* observer) {
    tilePyramid.setObserver(observer);
}

void RenderGeoJSONSource::dumpDebugLogs() const {
    tilePyramid.dumpDebugLogs();
}

} // namespace mbgl
