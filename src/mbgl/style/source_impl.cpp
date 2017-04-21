#include <mbgl/style/source_impl.hpp>
#include <mbgl/util/logging.hpp>

namespace mbgl {
namespace style {

Source::Impl::Impl(SourceType type_, std::string id_, Source& base_)
    : type(type_),
      id(std::move(id_)),
      base(base_) {
}

void Source::Impl::dumpDebugLogs() const {
    Log::Info(Event::General, "Source::id: %s", base.getID().c_str());
    Log::Info(Event::General, "Source::loaded: %d", loaded);
}

} // namespace style
} // namespace mbgl
