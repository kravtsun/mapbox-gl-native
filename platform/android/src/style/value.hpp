#pragma once

#include <jni/jni.hpp>

#include <string>

namespace mbgl {
namespace android {

class Value {
public:
    Value(jni::JNIEnv&, jni::Object<>);
    virtual ~Value();

    bool isNull() const;
    bool isArray() const;
    bool isObject() const;
    bool isString() const;
    bool isBool() const;
    bool isNumber() const;

    std::string toString() const;
    float toFloat() const;
    double toDouble() const;
    long toLong() const;
    bool toBool() const;
    Value get(const char* key) const;
    int getLength() const;
    Value get(const int index ) const;

    jni::JNIEnv& env;
    jni::Object<> value;
};

} // namespace android
} // namespace mbgl
