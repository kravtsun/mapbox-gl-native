#include <mbgl/annotation/annotation_source.hpp>
#include <mbgl/annotation/annotation_manager.hpp>

namespace mbgl {

using namespace style;

AnnotationSource::AnnotationSource()
    : Source(SourceType::Annotations, std::make_unique<Impl>(*this)) {
}

AnnotationSource::Impl::Impl(Source& base_)
    : Source::Impl(SourceType::Annotations, AnnotationManager::SourceID, base_) {
}

void AnnotationSource::Impl::loadDescription(FileSource&) {
    loaded = true;
}

} // namespace mbgl
