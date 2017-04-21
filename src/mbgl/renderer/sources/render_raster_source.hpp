#pragma once

#include <mbgl/renderer/render_source.hpp>
#include <mbgl/renderer/tile_pyramid.hpp>

namespace mbgl {

namespace style {
class RasterSource;
} // namespace style

class RenderRasterSource : public RenderSource {
public:
    RenderRasterSource(style::RasterSource&);

    bool isLoaded() const final;

    // Called when the camera has changed. May load new tiles, unload obsolete tiles, or
    // trigger re-placement of existing complete tiles.
    void updateTiles(const style::UpdateParameters&) final;

    // Removes all tiles (by putting them into the cache).
    void removeTiles() final;

    // Remove all tiles and clear the cache.
    void invalidateTiles() final;

    // Request that all loaded tiles re-run the layout operation on the existing source
    // data with fresh style information.
    void reloadTiles() final;

    void startRender(algorithm::ClipIDGenerator&,
                             const mat4& projMatrix,
                             const TransformState&) final;
    void finishRender(Painter&) final;

    std::map<UnwrappedTileID, RenderTile>& getRenderTiles() final;

    std::unordered_map<std::string, std::vector<Feature>>
    queryRenderedFeatures(const ScreenLineString& geometry,
                          const TransformState& transformState,
                          const RenderedQueryOptions& options) const final;

    std::vector<Feature>
    querySourceFeatures(const style::SourceQueryOptions&) final;

    void setCacheSize(size_t) final;
    void onLowMemory() final;

    void setObserver(TileObserver*) final;
    void dumpDebugLogs() const final;

private:
    TilePyramid tilePyramid;
    style::RasterSource& source;
    optional<std::vector<std::string>> tileURLTemplates;
};

} // namespace mbgl
