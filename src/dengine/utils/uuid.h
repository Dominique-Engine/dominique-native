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
#include <iomanip>

unsigned char RandomChar();

std::string GenerateHex(const unsigned int len);

namespace de {
namespace utils {
namespace uuids {

struct Uuid {
 public:
  typedef uint8_t* iterator;
  typedef uint8_t const* const_iterator;

  static constexpr std::size_t static_size() noexcept;

  std::string to_string();

 public:
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  constexpr std::size_t size() const noexcept;

  enum variant_type {
    variant_ncs,        // NCS backward compatibility
    variant_rfc_4122,   // defined in RFC 4122 document
    variant_microsoft,  // Microsoft Corporation backward compatibility
    variant_future      // future definition
  };
  variant_type variant() const noexcept;

  enum VersionType {
    version_unknown = -1,
    version_time_based = 1,
    version_dce_security = 2,
    version_name_based_md5 = 3,
    version_random_number_based = 4,
    version_name_based_sha1 = 5
  };
  VersionType version() const noexcept;

 public:
  // or should it be array<uint8_t, 16>
  uint8_t data[16];
};

// TODO
bool operator==(Uuid const& lhs, Uuid const& rhs) noexcept;
// TODO
bool operator<(Uuid const& lhs, Uuid const& rhs) noexcept;

inline bool operator!=(Uuid const& lhs, Uuid const& rhs) noexcept;

inline bool operator>(Uuid const& lhs, Uuid const& rhs) noexcept;

inline bool operator<=(Uuid const& lhs, Uuid const& rhs) noexcept;

inline bool operator>=(Uuid const& lhs, Uuid const& rhs) noexcept;

inline std::size_t hash_value(Uuid const& u) noexcept;

Uuid GetUUID();

}  // namespace uuids
}  // namespace utils
}  // namespace de
