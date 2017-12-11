# Change Log

## [0.1.3] - 2017-00-00

This is a new entry from the 0.1.x branch which should be included in the master changelog after an automatic mergeup.

## [0.1.2] - 2017-09-20

### Additions

- Included detectors for Xen and systemd-nspawn.
- Added a new entry here in the 0.1.x branch; It should appear in the correct place in the master branch after an automatic mergeup.

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
