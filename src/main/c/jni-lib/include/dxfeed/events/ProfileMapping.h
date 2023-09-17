// SPDX-License-Identifier: MPL-2.0

#ifndef NATIVE_JNI_SDK_PROFILEMAPPING_H
#define NATIVE_JNI_SDK_PROFILEMAPPING_H

#include "api/dxfg_events.h"

namespace dxfeed::jni {
  struct ByteWriter;

  struct ProfileMapping {
    static dxfg_profile_t* toProfile(const char** pByteData, const double** pDoubleData);
    static void fromProfile(dxfg_profile_t* eventType, ByteWriter& writer);
  };
}

#endif //NATIVE_JNI_SDK_PROFILEMAPPING_H
