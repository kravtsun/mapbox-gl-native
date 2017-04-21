#include <mbgl/renderer/render_fill_extrusion_layer.hpp>
#include <mbgl/renderer/bucket.hpp>
#include <mbgl/style/layers/fill_extrusion_layer_impl.hpp>

namespace mbgl {

RenderFillExtrusionLayer::RenderFillExtrusionLayer(std::shared_ptr<style::FillExtrusionLayer::Impl> impl)
        : RenderLayer(style::LayerType::FillExtrusion, std::move(impl)) {
          //impl(static_cast<mbgl::style::FillExtrusionLayer::Impl *>(baseImpl.get())) {
}

std::unique_ptr<RenderLayer> RenderFillExtrusionLayer::clone() const {
    return std::make_unique<RenderFillExtrusionLayer>(*this);
}

std::unique_ptr<Bucket> RenderFillExtrusionLayer::createBucket(const BucketParameters&, const std::vector<const RenderLayer*>&) const {
    return nullptr;
}

void RenderFillExtrusionLayer::cascade(const style::CascadeParameters&) {
}

bool RenderFillExtrusionLayer::evaluate(const style::PropertyEvaluationParameters&) {
    return false;
}

}
