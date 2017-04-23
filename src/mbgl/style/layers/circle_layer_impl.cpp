#include <mbgl/style/layers/circle_layer_impl.hpp>
#include <mbgl/renderer/render_circle_layer.hpp>

namespace mbgl {
namespace style {

std::unique_ptr<RenderLayer> CircleLayer::Impl::createRenderLayer() const {
    return std::make_unique<RenderCircleLayer>(shared_from_this());
}

} // namespace style
} // namespace mbgl
