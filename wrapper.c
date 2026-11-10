#include "wrapper.h"

// open62541's own `vsnprintf()` (`deps/mp_printf.c`), compiled into the library
// but declared only in an internal header.
int mp_vsnprintf(char *s, size_t count, const char *format, va_list arg);

// Wrapper for `vsnprintf()` with the same behavior on every platform.
//
// Formats with open62541's `mp_vsnprintf()` instead of the C library's: the
// library's log messages use its `%S`/`%N`/`%Q` extensions (`UA_String`,
// `UA_NodeId`, `UA_QualifiedName` passed by value), which a standard
// `vsnprintf()` misreads. It also keeps freestanding targets from needing a
// `vsnprintf()` at all.
//
// Other than the standard `vsnprintf()`, this function does not consume the
// passed `va_list` argument! The caller is responsible for calling
// `vsnprintf_va_end()` on the `va_list` argument eventually.
int RS_vsnprintf_va_copy(
    char *buffer,
    size_t count,
    const char *format,
    va_list args)
{
  va_list args_copied;
  va_copy(args_copied, args);
  int result = mp_vsnprintf(buffer, count, format, args_copied);
  va_end(args_copied);

  return result;
}

void RS_vsnprintf_va_end(va_list args)
{
  va_end(args);
}

// bindgen does not support non-trivial `#define` used for pointer constant. Use
// statically defined constant as workaround for now.
//
// See https://github.com/rust-lang/rust-bindgen/issues/2426
const void *const RS_UA_EMPTY_ARRAY_SENTINEL = UA_EMPTY_ARRAY_SENTINEL;
