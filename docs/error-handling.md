# Error handling

## Standard

Use `std::expected` for every fallible project API:

```cpp
#include <expected>

std::expected<Value, Error> LoadValue();
std::expected<void, Error> Initialize();
```

Always include the standard `<expected>` header; do not use implementation
headers such as `<std/unexpected.h>`. `std::expected` is C++-only. If a C ABI is
added, keep it in a dedicated C header and translate expected errors to C error
codes or output structures at that boundary.

Do not use booleans, magic integers, null pointers, empty values, exceptions, or
logging as substitutes for an explicit error result.

`std::expected` requires C++23. Keep the project and consuming targets configured
for C++23 or later.

## Error type

Use one project-owned `Error` type containing:

- a stable `enum class` error code;
- a human-readable message;
- operation and resource context, such as a file path or renderer stage; and
- the underlying SDL, parser, or system error when available.

Callers must inspect the error code, not parse its message.

## Rules

- Mark returned `std::expected` values `[[nodiscard]]`.
- Check every fallible SDL, GPU, filesystem, parser, and resource operation.
- Capture `SDL_GetError()` immediately after the failed SDL call.
- Propagate errors with added context until a layer can recover or present them.
- Log once at that handling boundary; lower layers return errors without logging.
- Use RAII for owned resources. Failed initialization must release newly acquired
  resources and preserve the previous valid state.
- Cleanup must support partial initialization and be idempotent where practical.
- Use assertions only for programmer invariants. Do not throw across C or SDL
  callback boundaries. Fatal termination belongs at the application boundary.
- Document bounded retries and visible fallbacks.

## Tests

Test error codes, relevant context, and post-failure state. Cover invalid input,
partial initialization, cleanup, retry, and repeated failure. Do not assert exact
upstream error-message text.
