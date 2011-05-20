// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/prefs/proxy_prefs.h"

#include "base/basictypes.h"
#include "base/logging.h"

namespace {

// These names are exposed to the proxy extension API. They must be in sync
// with the constants of ProxyPrefs.
const char* kProxyModeNames[] = { "direct",
                                  "auto_detect",
                                  "pac_script",
                                  "fixed_servers",
                                  "system" };

}  // namespace

namespace ProxyPrefs {

COMPILE_ASSERT(arraysize(kProxyModeNames) == kModeCount,
               kProxyModeNames_must_have_size_of_NUM_MODES);

bool IntToProxyMode(int in_value, ProxyMode* out_value) {
  DCHECK(out_value);
  if (in_value < 0 || in_value >= kModeCount)
    return false;
  *out_value = static_cast<ProxyMode>(in_value);
  return true;
}

// static
bool StringToProxyMode(const std::string& in_value, ProxyMode* out_value) {
  DCHECK(out_value);
  for (int i = 0; i < kModeCount; i++) {
    if (in_value == kProxyModeNames[i])
      return IntToProxyMode(i, out_value);
  }
  return false;
}

}  // namespace