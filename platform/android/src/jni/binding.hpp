#pragma once

#include <jni/jni.hpp>

namespace mbgl {
namespace android {

#ifndef NDEBUG
void RegisterNative(void (*)(jni::JNIEnv&));
void RegisterNative(jni::JNIEnv&);
#endif

template <class ClassTag>
struct ClassBinding {
public:
    using Base = ClassBinding<ClassTag>;
    static auto Class(jni::JNIEnv& env) {
#ifndef NDEBUG
        (void)binding; // Leave this here; it forces the generation of the static member.
#endif
        static auto javaClass = jni::Class<ClassTag>::Find(env).NewGlobalRef(env);
        return *javaClass;
    }

private:
#ifndef NDEBUG
    ClassBinding(void (*registerNative)(jni::JNIEnv&)) {
        RegisterNative(registerNative);
    }
    static ClassBinding binding;
#else
    ClassBinding() = default;
#endif
};

#ifndef NDEBUG
template <class ClassTag>
ClassBinding<ClassTag> ClassBinding<ClassTag>::binding{ [](jni::JNIEnv& env) {
    ClassBinding::Class(env);
} };
#endif

template <class ClassTag, class MethodTag, class>
struct MethodBinding;

template <class ClassTag, class MethodTag, class R, class... Args>
struct MethodBinding<ClassTag, MethodTag, R(Args...)> {
public:
    using Base = MethodBinding<ClassTag, MethodTag, R(Args...)>;
    static auto Method(jni::JNIEnv& env) {
#ifndef NDEBUG
        (void)binding; // Leave this here; it forces the generation of the static member.
#endif
        static const auto javaMethod =
            ClassBinding<ClassTag>::Class(env).template GetMethod<R(Args...)>(env,
                                                                              MethodTag::Name());
        return javaMethod;
    }

    static R Call(jni::JNIEnv& env, jni::Object<ClassTag> obj, Args&&... args) {
        return obj.Call(env, Method(env), std::forward<Args>(args)...);
    }

private:
#ifndef NDEBUG
    MethodBinding(void (*registerNative)(jni::JNIEnv&)) {
        RegisterNative(registerNative);
    }
    const static MethodBinding binding;
#else
    MethodBinding() = default;
#endif
};

#ifndef NDEBUG
template <class ClassTag, class MethodTag, class R, class... Args>
const MethodBinding<ClassTag, MethodTag, R(Args...)>
    MethodBinding<ClassTag, MethodTag, R(Args...)>::binding{ [](jni::JNIEnv& env) {
        MethodBinding::Method(env);
    } };
#endif

} // namespace android
} // namespace mbgl
