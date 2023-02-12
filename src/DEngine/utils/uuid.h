#pragma once

#include <algorithm>
#include <climits>
#include <cstddef>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

unsigned char RandomChar() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 255);
  return static_cast<unsigned char>(dis(gen));
}

std::string GenerateHex(const unsigned int len) {
  std::stringstream ss;
  for (auto i = 0; i < len; i++) {
    auto rc = RandomChar();
    std::stringstream hexstream;
    hexstream << std::hex << int(rc);
    auto hex = hexstream.str();
    ss << (hex.length() < 2 ? '0' + hex : hex);
  }
  return ss.str();
}

namespace dengine {
namespace utils {
namespace uuids {

struct Uuid {
 public:
  typedef uint8_t* iterator;
  typedef uint8_t const* const_iterator;

  static constexpr std::size_t static_size() noexcept { return 16; }
  std::string to_string() {
    std::stringstream ss;
    for (int i = 0; i < 16; ++i) {
      ss << std::hex << std::setfill('0') << std::setw(2) << (int)data[i];
      if (i == 3 || i == 5 || i == 7 || i == 9) {
        ss << '-';
      }
    }
    return ss.str();
  }

 public:
  iterator begin() noexcept { return data; }
  const_iterator begin() const noexcept { return data; }
  iterator end() noexcept { return data + size(); }
  const_iterator end() const noexcept { return data + size(); }

  constexpr std::size_t size() const noexcept { return static_size(); }

  enum variant_type {
    variant_ncs,        // NCS backward compatibility
    variant_rfc_4122,   // defined in RFC 4122 document
    variant_microsoft,  // Microsoft Corporation backward compatibility
    variant_future      // future definition
  };
  variant_type variant() const noexcept {
    // variant is stored in octet 7
    // which is index 8, since indexes count backwards
    unsigned char octet7 = data[8];  // octet 7 is array index 8
    if ((octet7 & 0x80) == 0x00) {   // 0b0xxxxxxx
      return variant_ncs;
    } else if ((octet7 & 0xC0) == 0x80) {  // 0b10xxxxxx
      return variant_rfc_4122;
    } else if ((octet7 & 0xE0) == 0xC0) {  // 0b110xxxxx
      return variant_microsoft;
    } else {
      // assert( (octet7 & 0xE0) == 0xE0 ) // 0b111xxxx
      return variant_future;
    }
  }

  enum VersionType {
    version_unknown = -1,
    version_time_based = 1,
    version_dce_security = 2,
    version_name_based_md5 = 3,
    version_random_number_based = 4,
    version_name_based_sha1 = 5
  };
  VersionType version() const noexcept {
    // version is stored in octet 9
    // which is index 6, since indexes count backwards
    uint8_t octet9 = data[6];
    if ((octet9 & 0xF0) == 0x10) {
      return version_time_based;
    } else if ((octet9 & 0xF0) == 0x20) {
      return version_dce_security;
    } else if ((octet9 & 0xF0) == 0x30) {
      return version_name_based_md5;
    } else if ((octet9 & 0xF0) == 0x40) {
      return version_random_number_based;
    } else if ((octet9 & 0xF0) == 0x50) {
      return version_name_based_sha1;
    } else {
      return version_unknown;
    }
  }

 public:
  // or should it be array<uint8_t, 16>
  uint8_t data[16];
};

// TODO
bool operator==(Uuid const& lhs, Uuid const& rhs) noexcept;
// TODO
bool operator<(Uuid const& lhs, Uuid const& rhs) noexcept;

inline bool operator!=(Uuid const& lhs, Uuid const& rhs) noexcept {
  return !(lhs == rhs);
}

inline bool operator>(Uuid const& lhs, Uuid const& rhs) noexcept {
  return rhs < lhs;
}
inline bool operator<=(Uuid const& lhs, Uuid const& rhs) noexcept {
  return !(rhs < lhs);
}

inline bool operator>=(Uuid const& lhs, Uuid const& rhs) noexcept {
  return !(lhs < rhs);
}

inline std::size_t hash_value(Uuid const& u) noexcept {
  std::size_t seed = 0;
  for (Uuid::const_iterator i = u.begin(), e = u.end(); i != e; ++i) {
    seed ^=
        static_cast<std::size_t>(*i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }

  return seed;
}

Uuid GetUUID() {
  Uuid u;
  std::string uuid_str = GenerateHex(32);
  // std::stringstream ss(uuid_str);
  for (int i = 0; i < 16; ++i) {
    // the commented approach does not work
    // int x;
    // ss >> std::hex >> x;
    u.data[i] = uuid_str[i];
  }
  return u;
}

}  // namespace uuids
}  // namespace utils
}  // namespace dengine
