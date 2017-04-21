#pragma once

#include <mbgl/style/source_impl.hpp>
#include <mbgl/style/sources/geojson_source.hpp>
#include <mbgl/util/variant.hpp>

namespace mbgl {

class AsyncRequest;
class CanonicalTileID;

namespace style {

class GeoJSONSource::Impl : public Source::Impl {
public:
    Impl(std::string id, Source&, const GeoJSONOptions);
    ~Impl() final;

    void setURL(std::string);
    optional<std::string> getURL() const;
    Range<uint8_t> getZoomRange() const;

    void setGeoJSON(const GeoJSON&);

    mapbox::geometry::feature_collection<int16_t> getTileData(const CanonicalTileID&) const;

    void loadDescription(FileSource&) final;

private:
    void _setGeoJSON(const GeoJSON&);

    GeoJSONOptions options;
    optional<std::string> url;
    std::unique_ptr<AsyncRequest> req;
    variant<GeoJSONVTPointer, SuperclusterPointer> geoJSONOrSupercluster;
};

} // namespace style
} // namespace mbgl
