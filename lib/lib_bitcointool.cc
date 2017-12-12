/*
** Copyright (c) 2017 Markku Pulkkinen. All rights reserved.
** Contact: markku.j.pulkkinen@gmail.com
**
** This file is part of warpwalletutil software distribution.
**
** This software is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This software is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this software.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "lib_bitcointool.h"

// This is ugly but allows using bitcoin-tool from library with minimal changes
#include "../main.c"

// Magic glue for redirection
namespace {
std::function<int(const char*, size_t)> callback;
extern "C" int redirector(const char* buf, size_t len) {
  return (callback(buf, len));
}
}

LibBitcoinTool::LibBitcoinTool() {
  // bind callback to our updateKeys() member fn
  using namespace std::placeholders;
  callback = std::bind(&LibBitcoinTool::updateKeys, this, _1, _2);
}

int LibBitcoinTool::updateKeys(const char* buf, size_t len) {
  // The <format:value> pairs are collected into map for easy access
  // of values by using format id string as key.
  if (state_ % 2 == 0) {
    format_ = std::string(buf, len);
  } else {
    // add new value for previously received format id into map
    std::vector<uint8_t> v;
    v.assign(buf, buf + len);
    v.resize(len);
    keys_.insert({format_, v});
  }
  state_++;

  return len;
}

bool LibBitcoinTool::getValue(const std::string& format,
                              std::vector<uint8_t>& value) const {
  if (keys_.count(format) == 1) {
    value = keys_.at(format);
    return true;
  }
  return false;
}

int LibBitcoinTool::run(int argc, const char* argv[]) {
  // reset result map and state counter
  keys_.clear();
  state_ = 0;

  BitcoinTool* bat = BitcoinTool_create();

  int result = 0;
  if (!bat->parseOptions(bat, argc, argv)) {
    bat->destroy(bat);
    return (-1);
  }
  bat->redirect = &redirector;
  result = bat->run(bat);
  bat->redirect = NULL;

  bat->destroy(bat);
  return (result ? 0 : -2);
};
