#include <mbgl/style/sources/vector_source_impl.hpp>
#include <mbgl/util/constants.hpp>

namespace mbgl {
namespace style {

VectorSource::Impl::Impl(std::string id_, Source& base_, variant<std::string, Tileset> urlOrTileset_)
    : TileSourceImpl(SourceType::Vector, std::move(id_), base_, std::move(urlOrTileset_), util::tileSize) {
}

} // namespace style
} // namespace mbgl
