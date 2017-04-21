#include <mbgl/style/layers/symbol_layer_impl.hpp>
#include <mbgl/style/property_evaluation_parameters.hpp>
#include <mbgl/renderer/render_symbol_layer.hpp>
#include <mbgl/layout/symbol_layout.hpp>
#include <mbgl/tile/geometry_tile_data.hpp>

namespace mbgl {
namespace style {

std::unique_ptr<RenderLayer> SymbolLayer::Impl::createRenderLayer() const {
    return std::make_unique<RenderSymbolLayer>(std::make_shared<style::SymbolLayer::Impl>(*this));
}

std::unique_ptr<SymbolLayout> SymbolLayer::Impl::createLayout(const BucketParameters& parameters,
                                                              const std::vector<const RenderLayer*>& group,
                                                              const GeometryTileLayer& layer,
                                                              GlyphDependencies& glyphDependencies,
                                                              IconDependencyMap& iconDependencyMap) const {
    return std::make_unique<SymbolLayout>(parameters,
                                          group,
                                          layer,
                                          iconDependencyMap[spriteAtlas],
                                          (uintptr_t) spriteAtlas,
                                          glyphDependencies);
}

} // namespace style
} // namespace mbgl
