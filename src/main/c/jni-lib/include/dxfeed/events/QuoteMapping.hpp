// Copyright © 2023 Devexperts LLC. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
// If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NATIVE_JNI_SDK_QUOTEMAPPING_HPP
#define NATIVE_JNI_SDK_QUOTEMAPPING_HPP

#include "api/dxfg_events.h"

namespace dxfeed::jni {
  struct ByteReader;
  struct ByteWriter;

  struct QuoteMapping {
    static dxfg_quote_t* toQuote(ByteReader& reader);
    static void fromQuote(dxfg_quote_t* eventType, ByteWriter& writer);
  };
}

#endif //NATIVE_JNI_SDK_QUOTEMAPPING_HPP
