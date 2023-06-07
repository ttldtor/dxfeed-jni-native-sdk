// SPDX-License-Identifier: MPL-2.0

#include <jni.h>
#include <iostream>

#include "javah/com_dxfeed_api_JNIDXFeedEventListener.h"
#include "javah/com_dxfeed_api_JNIPropertyChangeListener.h"
#include "dxfeed/listeners/DxEventListener.hpp"
#include "dxfeed/listeners/DxStateChangeListener.hpp"
#include "dxfeed/utils/NativeEventReader.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/invocation.html#JNJI_OnLoad
// -> register native method in created JNEEnv of VM when JNI lib is loaded
JNIEXPORT
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  jint flag = vm->GetEnv((void**) &env, JNI_VERSION_1_8);
  if (flag == JNI_ERR) {
    std::cerr << "Error getting JNIEnv. Exiting..." << std::endl;
    return flag;
  }
  std::cout << "JNI_OnLoad, env = " << env << ", res = " << flag << std::endl;
  return JNI_VERSION_1_8;
}

JNIEXPORT
void JNI_OnUnload(JavaVM* vm, void* reserved) {
  std::cout << "JNI_OnUnload" << std::endl;
}

JNIEXPORT
void JNICALL Java_com_dxfeed_api_JNIPropertyChangeListener_nOnStateChangeListener(JNIEnv* env, jclass,
                                                                                  jint oldStateValue,
                                                                                  jint newStateValue,
                                                                                  jlong jListener)
{
  auto stateChangeListener = reinterpret_cast<dxfeed::DxStateChangeListener*>(jListener);
  stateChangeListener->callUserFunc(env, oldStateValue, newStateValue);
}

JNIEXPORT
void JNICALL Java_com_dxfeed_api_JNIDXFeedEventListener_nOnEventListener(JNIEnv* env, jclass, jint size,
                                                               jbyteArray jBytes, jdoubleArray jDoubles,
                                                               jbyteArray jEventTypes,
                                                               jlong userCallback)
{
  auto pByteData = (char*) env->GetPrimitiveArrayCritical(jBytes, nullptr);
  auto pDoubleData = (double*) env->GetPrimitiveArrayCritical(jDoubles, nullptr);
  auto pEventTypes = (char*) env->GetPrimitiveArrayCritical(jEventTypes, nullptr);

  const auto& events = dxfeed::jni::NativeEventReader::toEvents(size, pByteData, pDoubleData, pEventTypes);

  env->ReleasePrimitiveArrayCritical(jDoubles, pDoubleData, 0);
  env->ReleasePrimitiveArrayCritical(jBytes, pByteData, 0);
  env->ReleasePrimitiveArrayCritical(jEventTypes, pEventTypes, 0);

  auto pListener = reinterpret_cast<dxfeed::DxEventListener*>(userCallback);
  dxfg_event_type_list list = { size, events.data() };
  pListener->callUserFunc(nullptr, &list); // todo: discuss thread == nullptr?
  for (const auto& event : events) {
    delete event;
  }
}

JNIEXPORT
void JNICALL JavaCritical_com_dxfeed_api_JNIDXFeedEventListener_nOnEventListener(jint size,
                                                                       jint byteLen, jbyte* jBytes,
                                                                       jint doubleLen, jdouble* jDoubles,
                                                                       jint eventTypesLen, jbyte* jEventTypes,
                                                                       jlong userCallback)
{
  auto pByteData = (char*) jBytes;
  auto pDoubleData = (double*) jDoubles;
  auto pEventTypes = (char*) jEventTypes;

  const auto& events = dxfeed::jni::NativeEventReader::toEvents(size, pByteData, pDoubleData, pEventTypes);

  auto pListener = reinterpret_cast<dxfeed::DxEventListener*>(userCallback);
  dxfg_event_type_list list = { size, events.data() };
  pListener->callUserFunc(nullptr, &list); // todo: discuss thread == nullptr?

  for (const auto& event : events) {
    delete[] event;
  }
}

JNIEXPORT
void JNICALL Java_com_dxfeed_api_JNIDXFeedEventListener_nClose(JNIEnv*, jclass, jlong jListener) {
  std::cout << "Java_com_dxfeed_api_JNIDXFeedEventListener_nClose" << std::endl;
  auto eventListener = reinterpret_cast<dxfeed::DxEventListener*>(jListener);
  delete eventListener;
}

JNIEXPORT
void JNICALL Java_com_dxfeed_api_JNIPropertyChangeListener_nClose(JNIEnv *, jclass, jlong jListener) {
  std::cout << "Java_com_dxfeed_api_JNIPropertyChangeListener_nClose" << std::endl;
  auto stateChangeListener = reinterpret_cast<dxfeed::DxStateChangeListener*>(jListener);
  delete stateChangeListener;
}

#ifdef __cplusplus
}
#endif