#pragma once

#include <functional>

namespace de {
namespace components {
struct UpdateHandler {
  // Generic function
  void (*handler)();
};

}  // namespace components
}  // namespace de