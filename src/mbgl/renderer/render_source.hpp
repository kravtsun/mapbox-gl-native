#pragma once

#include <mbgl/style/query.hpp>
#include <mbgl/tile/tile_id.hpp>
#include <mbgl/util/mat4.hpp>
#include <mbgl/util/geo.hpp>
#include <mbgl/util/feature.hpp>

#include <unordered_map>
#include <vector>
#include <map>
#include <memory>

namespace mbgl {

class Painter;
class TransformState;
class RenderTile;
class RenderedQueryOptions;
class Tile;
class TileObserver;

namespace algorithm {
class ClipIDGenerator;
} // namespace algorithm

namespace style {
class UpdateParameters;
} // namespace style

class RenderSource {
public:
    virtual ~RenderSource() = default;

    virtual bool isLoaded() const = 0;

    // Called when the camera has changed. May load new tiles, unload obsolete tiles, or
    // trigger re-placement of existing complete tiles.
    virtual void updateTiles(const style::UpdateParameters&) = 0;

    // Removes all tiles (by putting them into the cache).
    virtual void removeTiles() = 0;

    // Remove all tiles and clear the cache.
    virtual void invalidateTiles() = 0;

    // Request that all loaded tiles re-run the layout operation on the existing source
    // data with fresh style information.
    virtual void reloadTiles() = 0;

    virtual void startRender(algorithm::ClipIDGenerator&,
                             const mat4& projMatrix,
                             const TransformState&) = 0;
    virtual void finishRender(Painter&) = 0;

    virtual std::map<UnwrappedTileID, RenderTile>& getRenderTiles() = 0;

    virtual std::unordered_map<std::string, std::vector<Feature>>
    queryRenderedFeatures(const ScreenLineString& geometry,
                          const TransformState& transformState,
                          const RenderedQueryOptions& options) const = 0;

    virtual std::vector<Feature>
    querySourceFeatures(const style::SourceQueryOptions&) = 0;

    virtual void setCacheSize(size_t) = 0;
    virtual void onLowMemory() = 0;

    virtual void setObserver(TileObserver*) = 0;
    virtual void dumpDebugLogs() const = 0;

    bool enabled = false;
};

} // namespace mbgl
