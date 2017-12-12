/*
** Copyright (c) 2017 Markku Pulkkinen. All rights reserved.
** Contact: markku.j.pulkkinen@gmail.com
**
** This file is part of libwarputil software distribution.
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
