#include <mbgl/style/layers/fill_extrusion_layer_impl.hpp>
#include <mbgl/renderer/render_fill_extrusion_layer.hpp>

namespace mbgl {
namespace style {

std::unique_ptr<RenderLayer> FillExtrusionLayer::Impl::createRenderLayer() const {
    return std::make_unique<RenderFillExtrusionLayer>(shared_from_this());
}

} // namespace style
} // namespace mbgl
