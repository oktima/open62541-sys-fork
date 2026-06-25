// Status code constants parsed from `statuscodes.h` by `build.rs`. Kept in a separate file so the
// generated bindings stay untouched.
include!(concat!(env!("OUT_DIR"), "/status_codes.rs"));
