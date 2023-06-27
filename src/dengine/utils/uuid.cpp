#include "uuid.h"
#include <algorithm>
#include <climits>
#include <cstddef>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

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

constexpr std::size_t de::utils::uuids::Uuid::static_size() noexcept {
  return 16;
}

std::string de::utils::uuids::Uuid::to_string() {
  std::stringstream ss;
  for (int i = 0; i < 16; ++i) {
    ss << std::hex << std::setfill('0') << std::setw(2) << (int)data[i];
    if (i == 3 || i == 5 || i == 7 || i == 9) {
      ss << '-';
    }
  }
  return ss.str();
}

de::utils::uuids::Uuid::iterator de::utils::uuids::Uuid::begin() noexcept {
  return data;
}
de::utils::uuids::Uuid::const_iterator de::utils::uuids::Uuid::begin()
    const noexcept {
  return data;
}
de::utils::uuids::Uuid::iterator de::utils::uuids::Uuid::end() noexcept {
  return data + size();
}
de::utils::uuids::Uuid::const_iterator de::utils::uuids::Uuid::end()
    const noexcept {
  return data + size();
}

constexpr std::size_t de::utils::uuids::Uuid::size() const noexcept {
  return static_size();
}

de::utils::uuids::Uuid::variant_type de::utils::uuids::Uuid::variant()
    const noexcept {
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

de::utils::uuids::Uuid::VersionType de::utils::uuids::Uuid::version()
    const noexcept {
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

inline bool operator!=(de::utils::uuids::Uuid const& lhs,
                       de::utils::uuids::Uuid const& rhs) noexcept {
  return !(lhs == rhs);
}

inline bool operator>(de::utils::uuids::Uuid const& lhs,
                      de::utils::uuids::Uuid const& rhs) noexcept {
  return rhs < lhs;
}
inline bool operator<=(de::utils::uuids::Uuid const& lhs,
                       de::utils::uuids::Uuid const& rhs) noexcept {
  return !(rhs < lhs);
}

inline bool operator>=(de::utils::uuids::Uuid const& lhs,
                       de::utils::uuids::Uuid const& rhs) noexcept {
  return !(lhs < rhs);
}

inline std::size_t de::utils::uuids::hash_value(
    de::utils::uuids::Uuid const& u) noexcept {
  std::size_t seed = 0;
  for (Uuid::const_iterator i = u.begin(), e = u.end(); i != e; ++i) {
    seed ^=
        static_cast<std::size_t>(*i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }

  return seed;
}

de::utils::uuids::Uuid de::utils::uuids::GetUUID() {
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
