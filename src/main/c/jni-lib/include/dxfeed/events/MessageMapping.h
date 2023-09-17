// SPDX-License-Identifier: MPL-2.0

#ifndef NATIVE_JNI_SDK_MESSAGEMAPPING_H
#define NATIVE_JNI_SDK_MESSAGEMAPPING_H

#include "api/dxfg_events.h"

namespace dxfeed::jni {
  struct ByteReader;
  struct ByteWriter;

  struct MessageMapping {
    static dxfg_message_t* toMessage(ByteReader& reader);
    static void fromMessage(dxfg_message_t* eventType, ByteWriter& writer);
  };
}

#endif //NATIVE_JNI_SDK_MESSAGEMAPPING_H
