#pragma once

#include "../jni/binding.hpp"

namespace mbgl {
namespace android {
namespace java {
namespace lang {

struct Object : public ClassBinding<jni::ObjectTag> {
};

struct ObjectArray : public ClassBinding<ObjectArray> {
    static constexpr auto Name() { return "[Ljava/lang/Object;"; }
};

struct Float : public ClassBinding<Float> {
    static constexpr auto Name() { return "java/lang/Float"; }
};

struct Number : public ClassBinding<Number> {
    static constexpr auto Name() { return "java/lang/Number"; }

    struct FloatValue : public MethodBinding<Number, FloatValue, jni::jfloat(void)> {
        static constexpr auto Name() { return "floatValue"; }
    };

    struct DoubleValue : public MethodBinding<Number, DoubleValue, jni::jdouble(void)> {
        static constexpr auto Name() { return "doubleValue"; }
    };

    struct LongValue : public MethodBinding<Number, LongValue, jni::jlong(void)> {
        static constexpr auto Name() { return "longValue"; }
    };
};

struct Boolean : public ClassBinding<Boolean> {
    static constexpr auto Name() { return "java/lang/Boolean"; }

    struct BooleanValue : public MethodBinding<Boolean, BooleanValue, jni::jboolean(void)> {
        static constexpr auto Name() { return "booleanValue"; }
    };
};

struct String : public ClassBinding<jni::StringTag> {
};

} // namespace lang
} // namespace java
} // namespace android
} // namespace mbgl
