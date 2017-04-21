#pragma once

#include <mbgl/renderer/render_layer.hpp>
#include <mbgl/style/layers/custom_layer.hpp>

namespace mbgl {

class RenderCustomLayer: public RenderLayer {
public:

    RenderCustomLayer(std::shared_ptr<style::CustomLayer::Impl>);
    ~RenderCustomLayer() final = default;

    std::unique_ptr<RenderLayer> clone() const override;

    void cascade(const style::CascadeParameters&) final {}
    bool evaluate(const style::PropertyEvaluationParameters&) final;

    std::unique_ptr<Bucket> createBucket(const BucketParameters&, const std::vector<const RenderLayer*>&) const final;

    style::CustomLayer::Impl* impl;
};

template <>
inline bool RenderLayer::is<RenderCustomLayer>() const {
    return type == style::LayerType::Custom;
}

}
