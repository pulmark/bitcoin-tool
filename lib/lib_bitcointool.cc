/*
** Copyright (c) 2017 Markku Pulkkinen.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
**WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
