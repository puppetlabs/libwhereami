#pragma once

/**
 * Virtual machine name constants
 */
namespace whereami { namespace vm {

    /**
     * The name for VMWare virtual machines.
     */
    constexpr static char const* vmware {"vmware"};

    /**
     * The name for VirtualBox virtual machines.
     */
    constexpr static char const* virtualbox {"virtualbox"};

    /**
     * The name for Docker containres.
     */
    constexpr static char const* docker {"docker"};

    /**
     * The name for LXC containers.
     */
    constexpr static char const* lxc {"lxc"};

    /**
     * The name for systemd-nspawn containers.
     */
    constexpr static char const* systemd_nspawn {"systemd_nspawn"};

    /**
     * The name for Xen virtual machines.
     */
    constexpr static char const* xen {"xen"};

    /**
     * The name for OpenVZ containers.
     */
    constexpr static char const* openvz {"openvz"};

    /**
     * The name for KVM (QEMU) virtual machines.
     */
    constexpr static char const* kvm {"kvm"};

    /**
     * The name for Microsoft Hyper-V virtual machines.
     */
    constexpr static char const* hyperv {"hyperv"};

    /**
     * The name for Solaris zones
     */
    constexpr static char const* zone {"zone"};

    /**
     * The name for Solaris LDoms
     */
    constexpr static char const* ldom {"ldom"};

}}  // namespace whereami::vm
