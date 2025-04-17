Non-Optional shared_ptr
-----------------------

C++ `std::shared_ptr` is not null-safe, it can always be `nullptr`. If you wrap it in a `std::optional`, you
just end up adding a third state. `std::optional` also doesn't enforce checking whether an optional contains
a value, it just presents a runtime-error if you call `value()` without first checking.

This class is a thin, zero-overhead wrapper around a `std::shared_ptr` and can only be constructed with a
non-null pointer. That way, you can guarantee, at the type level, that certain shared pointers are never
`nullptr`.

Also provided are convenience wrappers for `std::make_shared` that allow directly creating a
`nonoptional_shared_ptr`, and an `optional_shared_ptr` class that can be used to tag shared pointers
that have been reviewed and are intentionally optional.

See `main.cpp` for usage examples.
