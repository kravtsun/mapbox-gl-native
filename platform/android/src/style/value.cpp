#include "value.hpp"

#include "../java/lang.hpp"
#include "../java/util.hpp"

namespace mbgl {
namespace android {

class ObjectDeleter {
public:
    ObjectDeleter() = default;
    ObjectDeleter(JNIEnv& e) : env(e) {
    }

    void operator()(jni::jobject* p) const {
        if (p) {
            jni::DeleteLocalRef(env, p);
        }
    }

private:
    JNIEnv& env;
};

// Instance

Value::Value(jni::JNIEnv& env_, jni::Object<> value_) : env(env_), value(value_) {
}

Value::~Value() = default;

bool Value::isNull() const {
    return value;
}

bool Value::isArray() const {
    return value.IsInstanceOf(env, java::lang::ObjectArray::Class(env));
}

bool Value::isObject() const {
    return value.IsInstanceOf(env, java::util::Map::Class(env));
}

bool Value::isString() const {
    return value.IsInstanceOf(env, java::lang::String::Class(env));
}

bool Value::isBool() const {
    return value.IsInstanceOf(env, java::lang::Boolean::Class(env));
}

bool Value::isNumber() const {
    return value.IsInstanceOf(env, java::lang::Number::Class(env));
}

std::string Value::toString() const {
    return jni::Make<std::string>(env, jni::String(reinterpret_cast<jni::jstring*>(value.Get())));
}

float Value::toFloat() const {
    return java::lang::Number::FloatValue::Call(env, jni::Object<java::lang::Number>(value.Get()));
}

double Value::toDouble() const {
    return java::lang::Number::DoubleValue::Call(env, jni::Object<java::lang::Number>(value.Get()));
}

long Value::toLong() const {
    return java::lang::Number::LongValue::Call(env, jni::Object<java::lang::Number>(value.Get()));
}

bool Value::toBool() const {
    return java::lang::Boolean::BooleanValue::Call(env,
                                                   jni::Object<java::lang::Boolean>(value.Get()));
}

Value Value::get(const char* key) const {
    return { env, java::util::Map::Get::Call(env, jni::Object<java::util::Map>(value.Get()), key) };
}

int Value::getLength() const {
    return jni::Array<jni::Object<>>(reinterpret_cast<jni::jarray<jni::jobject>*>(value.Get()))
        .Length(env);
}

Value Value::get(const int index) const {
    return { env,
             jni::Array<jni::Object<>>(reinterpret_cast<jni::jarray<jni::jobject>*>(value.Get()))
                 .Get(env, index) };
}

} // namespace android
} // namespace mbgl
