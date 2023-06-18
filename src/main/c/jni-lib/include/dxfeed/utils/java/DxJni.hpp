// SPDX-License-Identifier: MPL-2.0

#ifndef NATIVE_JNI_SDK_DXFEEDJNICLASS_H
#define NATIVE_JNI_SDK_DXFEEDJNICLASS_H

#include <jni.h>
#include "javah/com_dxfeed_api_DxSubscriptionJni.h"
#include "javah/com_dxfeed_api_DxEndpointJni.h"

namespace dxfeed::jni {
  struct DxJni {
    _jclass* const dxEndpointJniClass_;
    _jclass* const dxFeedJniClass_;
    _jclass* const dxSubscriptionJniClass_;
    _jclass* const dxSymbolJniClass_;

    static DxJni* initDxJni(JNIEnv* env);

  private:
    explicit DxJni(JNIEnv* env);
  };

  static JNINativeMethod nDxEndpoint[] = {
    {"nOnStateChangeListener", "(IIJJ)V", (void*) &Java_com_dxfeed_api_DxEndpointJni_nOnStateChangeListener},};

  static JNINativeMethod nDxSubscription[] = {
    {"nOnEventListener", "(I[B[D[BJJ)V", (void*) &Java_com_dxfeed_api_DxSubscriptionJni_nOnEventListener}};
}

#endif //NATIVE_JNI_SDK_DXFEEDJNICLASS_H