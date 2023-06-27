// SPDX-License-Identifier: MPL-2.0

#include "api/graal_isolate.h"
#include "dxfeed/utils/JNIUtils.hpp"

int graal_create_isolate(graal_create_isolate_params_t* params, graal_isolate_t **isolate, graal_isolatethread_t **thread) {
  if (dxfeed::jni::internal::javaVM == nullptr) {
    auto javaHome = dxfeed::jni::getJavaHome(dxfeed::r_cast<dxfeed::jni::VMOptions*>(params));
    // todo: get VmArgs and VmArgCount from params;
    dxfeed::jni::VMOptions options = { javaHome, nullptr, 0 };
    dxfeed::jni::internal::initJavaVM(&options);
    *isolate = (void*) dxfeed::jni::internal::javaVM;
    *thread = dxfeed::jni::internal::jniEnv;
  }
  return (*isolate != nullptr && *thread != nullptr) ? JNI_OK : -1;
}


graal_isolatethread_t* graal_get_current_thread(graal_isolate_t* isolate) {
  auto vmInstance = dxfeed::r_cast<dxfeed::jni::internal::vm::JavaVmInstance*>(isolate);
  return vmInstance->getCurrenThread();
}

// https://github.com/oracle/graal/blob/8be56121aa31e7448b4adb0224ab2ac44095ed9b/compiler/src/jdk.internal.vm.compiler/src/org/graalvm/libgraal/LibGraal.java#L253
int graal_attach_thread(graal_isolate_t* isolate, graal_isolatethread_t** env) {
  auto vmInstance = dxfeed::r_cast<dxfeed::jni::internal::vm::JavaVmInstance*>(isolate);
  vmInstance->attachCurrentThread(env);
  return JNI_OK;
}

// https://github.com/oracle/graal/blob/8be56121aa31e7448b4adb0224ab2ac44095ed9b/compiler/src/jdk.internal.vm.compiler/src/org/graalvm/libgraal/LibGraal.java#L283
// jint DetachCurrentThread()
int graal_detach_thread(graal_isolatethread_t* ) {
  dxfeed::jni::internal::javaVM->detachCurrentThread();
  return JNI_OK;
}