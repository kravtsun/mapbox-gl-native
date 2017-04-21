#include <mbgl/style/sources/raster_source_impl.hpp>

namespace mbgl {
namespace style {

RasterSource::Impl::Impl(std::string id_, Source& base_,
                         variant<std::string, Tileset> urlOrTileset_,
                         uint16_t tileSize_)
    : TileSourceImpl(SourceType::Raster, std::move(id_), base_, std::move(urlOrTileset_), tileSize_) {
}

} // namespace style
} // namespace mbgl
