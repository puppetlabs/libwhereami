# Change Log

## [0.1.2] - 2017-09-20

### Additions

- Included detectors for Xen and systemd-nspawn.

### Fixes

- Fixed segfault when WMI is available but reports no data for some queries.

## [0.1.1] - 2017-09-08

### Fixes

- Fixed segfault while attempting to collect data from `dmidecode` when it returns empty output.
- Fixed segfaults in CPUID instruction calls on MacOS 10.11+ and static 32-bit environments.

## [0.1.0] - 2017-08-30

Initial release of libwhereami; Supported platforms are Linux, Windows, and MacOS.

- Data sources for WMI, DMI, CPUID, cgroups, system_profiler
- Detectors for Docker, Hyper-V, KVM, LXC, OpenVZ, VirtualBox, VMWare
