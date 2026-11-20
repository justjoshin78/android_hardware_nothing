/*
 * SPDX-FileCopyrightText: 2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

// Android 17 blobs (e.g. libprotobuf-cpp-full-6.33.5.so) import
// std::__1::__hash_memory(const void*, size_t), which newer libc++ exports
// from the dylib. Android 16's libc++ hashes inline with
// __murmur2_or_cityhash<size_t>, which is the same algorithm, so forward to it
// to keep hash values identical across the boundary.

#include <cstddef>
#include <string>

_LIBCPP_BEGIN_NAMESPACE_STD

__attribute__((visibility("default"))) size_t __hash_memory(const void* ptr, size_t size) noexcept {
    return __murmur2_or_cityhash<size_t>()(ptr, size);
}

_LIBCPP_END_NAMESPACE_STD
