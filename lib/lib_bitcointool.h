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
#ifndef LIB_BITCOINTOOL_H
#define LIB_BITCOINTOOL_H

#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

///
/// \brief LibBitcoinTool class - a simple wrapper for bitcoin-tool functions
///
class LibBitcoinTool {
 public:
  LibBitcoinTool();

  ///
  /// \brief runs bitcoin-tool command with given arguments
  /// \param argc - argument count
  /// \param argv - argument vector
  /// \return  0 success, otherwise error code
  ///
  int run(int argc, const char* argv[]);

  ///
  /// \brief updates map containing crypto currency attribute <key:value> pairs
  /// \param buf - data buffer
  /// \param len - data buffer length
  /// \return
  ///
  int updateKeys(const char* buf, size_t len);

  ///
  /// \brief retrieves value of given crypto currency format
  /// \param format - address | public key | private key id & encoding format
  /// \param value - format value
  /// \return true if found, false otherwise
  ///
  bool getValue(const std::string& key, std::vector<uint8_t>& value) const;

 private:
  /// map for crypto currency address | public | private key id, value
  std::map<std::string, std::vector<uint8_t> > keys_;
  std::string format_;
  int state_;
};

#endif  // LIB_BITCOINTOOL_H
