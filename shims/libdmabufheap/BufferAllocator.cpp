/*
 * SPDX-FileCopyrightText: 2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

// Android 17 blobs (e.g. lib-imsvt.so) import an out-of-line
// BufferAllocator::~BufferAllocator() (_ZN15BufferAllocatorD1Ev).
// On Android 16 the destructor is inline in the header, so libdmabufheap
// does not export it. Provide it here.
//
// The header is included under a renamed class so that its inline destructor
// gets a different mangled name and cannot collide with (or recurse into)
// the symbol we export. Layout is identical, so destroying through the
// renamed type releases the same members.

#include <functional>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <android-base/unique_fd.h>

#define BufferAllocator BufferAllocatorShimLayout
#include <BufferAllocator/BufferAllocator.h>
#undef BufferAllocator

extern "C" void _ZN15BufferAllocatorD1Ev(BufferAllocatorShimLayout* self) {
    self->~BufferAllocatorShimLayout();
}
