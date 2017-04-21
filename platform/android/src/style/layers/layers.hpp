#pragma once

#include <mbgl/style/style.hpp>
#include <mbgl/style/layer.hpp>

#include "layer.hpp"

#include <jni/jni.hpp>

namespace mbgl {
namespace android {

/**
 * Create a non-owning peer
 */
jni::jobject* createJavaLayerPeer(jni::JNIEnv&, mbgl::style::Style&, mbgl::style::Layer&);

/**
 * Create an owning peer
 */
jni::jobject* createJavaLayerPeer(jni::JNIEnv& env, mbgl::style::Style&, std::unique_ptr<mbgl::style::Layer>);

void registerNativeLayers(jni::JNIEnv&);

}
}
