# libwhereami

libwhereami is a C++11 library that detects virtualization environments from inside virtual machines.

## Supported platforms

- Linux
- Windows
- Mac OS
- Solaris
- AIX

## Detected environments and reported metadata

Not all metadata is consistently available on all platforms.

- Docker
  - id : string
- Hyper-V
- KVM
  - openstack : bool
  - google : bool
- LXC
  - name : string
- OpenVZ
  - id : int
  - host : bool
  - cloudlinux : bool
- systemd-nspawn
  - name : string
- LDom
  - chassis_serial : string
  - control_domain : string
  - domain_name : string
  - domain_uuid : string
  - role_control : bool
  - role_io : bool
  - role_root : bool
  - role_service : bool
- LPAR
  - partition_name : string
  - partition_number : int
- VirtualBox
  - version : string (requires root)
  - revision : string (requires root)
- VMware
  - version : string (requires root)
- WPAR
  - key : int
  - configured_id : int
- Xen
  - context : string ("hvm" or "pv")
  - privileged : bool
- Zone
  - brand : string
  - id : int
  - ip_type : string
  - name : string
  - uuid : string

## Example usage

```cpp
#include <whereami/whereami.hpp>
#include <iostream>

// Attempt to detect whether this machine is a VM;
// Gather any available metadata about the detected hypervisor(s).
auto results = whereami::hypervisors();

for (auto const& result : results) {
    // Print the name of the hypervisor
    std::cout << result.name() << std::endl;
    // Print each value in the metadata map, too
    for (auto const& metadata : result.metadata()) {
        std::cout << "- " << metadata.first
                  << ": " << metadata.second << std::endl;
    }
}
```

## Build Requirements

- Linux, Windows, Mac OS, Solaris, or AIX
- GCC >= 4.8 or Clang >= 3.4 (with libc++)
- CMake >= 3.2.2
- Boost libraries >= 1.54
- [Leatherman](https://github.com/puppetlabs/leatherman)

## Pre-Build

Prepare the CMake build directory:

```
mkdir build-release
cd build-release
cmake ..
```

Optionally, also prepare the debug environment:
```
mkdir build-debug
cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

## Build

1. Enter your build directory (i.e. `cd build-release` or `cd build-debug`).
2. Run `make`.
3. Install with `make install`.

## Testing

You can run the tests from inside your build directory with `make libwhereami_test`.
