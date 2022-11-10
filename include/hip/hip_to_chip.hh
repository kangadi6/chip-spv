/*
 * Copyright (c) 2021-22 CHIP-SPV developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef HIP_TO_CHIP_HH
#define HIP_TO_CHIP_HH

// Forward Declarations
class CHIPDevice;
class CHIPContext;
class CHIPModule;
class CHIPKernel;
class CHIPBackend;
class CHIPEvent;
class CHIPQueue;
class CHIPTexture;
/* implementation details */
typedef CHIPEvent *hipEvent_t;
typedef CHIPKernel *hipFunction_t;
typedef CHIPModule *hipModule_t;
typedef CHIPQueue *hipStream_t;
// typedef CHIPTexture *hipTextureObject_t;
typedef CHIPContext *hipCtx_t;
// TODO HIP tests assume this is int
// typedef CHIPDevice **hipDevice_t;
typedef int hipDevice_t;
typedef void *hipDeviceptr_t;

typedef int hipMemGenericAllocationHandle_t;

enum hipMemAllocationHandleType{
    HIP_MEM_HANDLE_TYPE_NONE = 0x0,
    HIP_MEM_HANDLE_TYPE_POSIX_FILE_DESCRIPTOR = 0x1,
    HIP_MEM_HANDLE_TYPE_WIN32 = 0x2,
    HIP_MEM_HANDLE_TYPE_WIN32_KMT = 0x4,
    HIP_MEM_HANDLE_TYPE_MAX = 0x7FFFFFFF
};

enum hipMemAllocationType{
    HIP_MEM_ALLOCATION_TYPE_INVALID = 0x0,
    HIP_MEM_ALLOCATION_TYPE_PINNED = 0x1,
    HIP_MEM_ALLOCATION_TYPE_MAX = 0x7FFFFFFF
};

enum hipMemLocationType {
    HIP_MEM_LOCATION_TYPE_INVALID = 0x0,
    HIP_MEM_LOCATION_TYPE_DEVICE = 0x1,
    HIP_MEM_LOCATION_TYPE_MAX = 0x7FFFFFFF
};

enum hipMemAccess_flags {
    HIP_MEM_ACCESS_FLAGS_PROT_NONE = 0x0,
    HIP_MEM_ACCESS_FLAGS_PROT_READ = 0x1,
    HIP_MEM_ACCESS_FLAGS_PROT_READWRITE = 0x3,
    HIP_MEM_ACCESS_FLAGS_PROT_MAX = 0x7FFFFFFF,
};

typedef struct hipMemLocation {
    int  id;
    hipMemLocationType type;
}hipMemLocation;

typedef struct hipMemAllocationProp {
    unsigned char  compressionType;
    struct hipMemLocation location;
    hipMemAllocationHandleType 	requestedHandleTypes;
    hipMemAllocationType type;
    unsigned short  usage;
    void * win32HandleMetaData;
} hipMemAllocationProp_t;

typedef struct hipMemAccessDesc_t {
    hipMemAccess_flags flags;
    struct hipMemLocation location;
} hipMemAccessDesc_t;

#endif
