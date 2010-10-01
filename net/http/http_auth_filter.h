// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_AUTH_FILTER_H_
#define NET_HTTP_HTTP_AUTH_FILTER_H_

#include <list>
#include <set>
#include <string>

#include "base/string_util.h"
#include "net/http/http_auth.h"
#include "net/proxy/proxy_bypass_rules.h"

class GURL;

namespace net {

// |HttpAuthFilter|s determine whether an authentication scheme should be
// allowed for a particular peer.
class HttpAuthFilter {
 public:
  virtual ~HttpAuthFilter() {}

  // Checks if (|url|, |target|) is supported by the authentication scheme.
  // Only the host of |url| is examined.
  virtual bool IsValid(const GURL& url, HttpAuth::Target target) const = 0;
};

// Whitelist HTTP authentication filter.
// Explicit whitelists of domains are set via SetWhitelist().
//
// Uses the ProxyBypassRules class to do whitelisting for servers.
// All proxies are allowed.
class HttpAuthFilterWhitelist : public HttpAuthFilter {
 public:
  HttpAuthFilterWhitelist();
  virtual ~HttpAuthFilterWhitelist();

  // HttpAuthFilter methods:
  virtual bool IsValid(const GURL& url, HttpAuth::Target target) const;

  // Installs the whitelist.
  // |server_whitelist| is parsed by ProxyBypassRules.
  void SetWhitelist(const std::string& server_whitelist);

  // Adds an individual URL |filter| to the list, of the specified |target|.
  bool AddFilter(const std::string& filter, HttpAuth::Target target);

  // Adds a rule that bypasses all "local" hostnames.
  void AddRuleToBypassLocal();

  const ProxyBypassRules& rules() const { return rules_; }

 private:
  // We are using ProxyBypassRules because they have the functionality that we
  // want, but we are not using it for proxy bypass.
  ProxyBypassRules rules_;

  DISALLOW_COPY_AND_ASSIGN(HttpAuthFilterWhitelist);
};

}   // namespace net

#endif  // NET_HTTP_HTTP_AUTH_FILTER_H_