## Support status

This is a (non-exhaustive) list of HIP features currently (un)supported by CHIP-SPV.

For a more detailed matrix of supported functions and features, see the files
Host_API_support_matrix.md and Device_API_support_matrix.md.

For an even more detailed per-function support status, see the files
Host_API_functions.md and Device_API_functions.md.

CUDA features not present in HIP are unsupported unless explicitly stated otherwise.

### Host side

#### Unsupported / unimplemented APIs

* hipGraph API

* hipIpc API (hipIpcGetMemHandle etc)

* hipModuleOccupancy API

* texture reference API (hipTexRef, (DEPRECATED in CUDA)

* surface reference API (DEPRECATED in CUDA)

* surface object API (hipCreateSurfaceObject, hipDestroySurfaceObject)

* peer access (hipMemcpyPeer, hipMemcpyPeerAsync,
  hipDeviceCanAccessPeer, hipDeviceEnablePeerAccess,
  hipDeviceDisablePeerAccess, etc)

* hipMemRangeGetAttribute

* some config APIs (hipDeviceSetCacheConfig, hipDeviceGetCacheConfig
  hipDeviceSetSharedMemConfig, hipDeviceGetSharedMemConfig,
  hipSetDeviceFlags, hipGetDeviceFlags, hipFuncSetCacheConfig)

* primary context API (hipDevicePrimaryCtxRelease,
  hipDevicePrimaryCtxRetain,  hipDevicePrimaryCtxSetFlags)

* few memory APIs (hipMemPrefetchAsync, hipMemAdvise)

* few module APIs (hipModuleLoadData, hipModuleUnload, hipModuleLaunchKernel)

#### partially supported

* Texture Objects of 1D/2D type are supported; 3D, LOD, Grad,
  Cubemap, Gather and Mipmapped textures are not supported

* hiprtc: Referring global device variables, constants and texture
  references in the name expressions are not supported.

* hipFuncGetAttributes - not all attributes are supported, depends on backend

* hipDeviceGetLimit - only some limits are supported

-------------------------------------------------------------------


### Device side

#### Unsupported / unavailable

* _syncwarp(), __activemask(), threadfence_system(), warpSize variable

* clock(), clock64()

* Cooperative Groups Functions

* Warp Matrix Functions

* Independent Thread Scheduling

* Profiler Counter Function

* Address Space Predicate Functions

* Address Space Conversion Functions

* Device-Side Dynamic Global Memory Allocation

* In-Line Assembly

* __trap(), __brkpt(), assert()

* surface functions

#### Partially supported

* math library: almost all single/double functions are available,
  half/half2 functions are available but untested

* functions that specify rounding (e.g. __fdiv_rd), except conversion functions (as rounding cannot be selected in OpenCL)

* device intrinsics are mapped to OpenCL's native_* functions where possible, otherwise are unsupported / emulated

* Warp functions (__all, __any, __ballot): only the non-sync versions are supported

* Shuffle functions (__shfl_{up,down,xor}): only the non-sync versions are supported

* abort()

* texture functions: only with certain image types

* atomic functions: supported but atomics on float/double is emulated using CAS loop

-------------------------------------------------------------------

### Known issues

* warpSize might depend on the kernel instead of being a device constant

* hiprtc: Valid name expressions with a function pointer cast
  (e.g. '(void(*)(float *))akernel') fails with misleading
  messages. For example: "error: address of overloaded function
  'akernel' does not match required type ...". This issue prevents
  disambiguation of overloaded kernels.

* hiprtc: quoted strings are not preserved due to the way the hipcc
  handles arguments currently.  E.g. -DGREETING="Hello, World!" is
  treated as two argument ('-DGREETING=Hello,' and 'World!').
