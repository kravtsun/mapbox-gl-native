#pragma once

#include "lang.hpp"

#include <mbgl/util/noncopyable.hpp>

namespace mbgl {
namespace android {
namespace java {
namespace util {

struct List : public ClassBinding<List> {
    static constexpr auto Name() { return "java/util/List"; }

    struct ToArray : public MethodBinding<List, ToArray, jni::Array<jni::Object<>>(void)> {
        static constexpr auto Name() { return "toArray"; }
        template <class T = jni::ObjectTag, class... Args>
        static auto Call(Args&&... args) {
            return (jni::Array<jni::Object<T>>)Base::Call(std::forward<Args>(args)...);
        }
    };
};

struct Map : public ClassBinding<Map> {
    static constexpr auto Name() { return "java/util/Map"; }

    struct Entry : public ClassBinding<Entry> {
        static constexpr auto Name() { return "java/util/Map$Entry"; };

        struct GetKey : public MethodBinding<Entry, GetKey, jni::Object<>(void)> {
            static constexpr auto Name() { return "getKey"; }
            template <class T = jni::ObjectTag, class... Args>
            static auto Call(Args&&... args) {
                return (jni::Object<T>)Base::Call(std::forward<Args>(args)...);
            }
        };

        struct GetValue : public MethodBinding<Entry, GetValue, jni::Object<>(void)> {
            static constexpr auto Name() { return "getValue"; }
            template <class T = jni::ObjectTag, class... Args>
            static auto Call(Args&&... args) {
                return (jni::Object<T>)Base::Call(std::forward<Args>(args)...);
            }
        };
    };

    struct Get : public MethodBinding<Map, Get, jni::Object<>(jni::Object<>)> {
        static constexpr auto Name() { return "get"; }
        static jni::Object<> Call(jni::JNIEnv& env, jni::Object<Map> obj, const char* key) {
            return Base::Call(env, obj,
                              jni::Cast(env, jni::Make<jni::String>(env, std::string(key)),
                                        java::lang::Object::Class(env)));
        }
    };
};

struct Set : public ClassBinding<Set> {
    static constexpr auto Name() { return "java/util/Set"; }

    struct ToArray : public MethodBinding<Set, ToArray, jni::Array<jni::Object<>>(void)> {
        static constexpr auto Name() { return "toArray"; }
        template <class T = jni::ObjectTag, class... Args>
        static auto Call(Args&&... args) {
            return (jni::Array<jni::Object<T>>)Base::Call(std::forward<Args>(args)...);
        }
    };
};

} // namespace util
} // namespace java
} // namespace android
} // namespace mbgl