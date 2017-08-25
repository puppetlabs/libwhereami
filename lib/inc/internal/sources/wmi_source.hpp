#pragma once

#include "./smbios_base.hpp"
#include <leatherman/windows/wmi.hpp>

namespace whereami { namespace sources {

    /**
     * SMBIOS source for Windows, using WMI
     */
    class wmi : public smbios_base
    {
    public:
        /**
         * The Computer System WMI class name
         */
        constexpr static char const* class_computersystem = "Win32_ComputerSystem";
        /**
         * The Computer System Product WMI class name
         */
        constexpr static char const* class_computersystemproduct = "Win32_ComputerSystemProduct";
        /**
         * The BIOS WMI class name
         */
        constexpr static char const* class_bios = "Win32_Bios";
        /**
         * The Base Board WMI class name
         */
        constexpr static char const* class_baseboard = "Win32_BaseBoard";
        /**
         * The Product WMI property name
         */
        constexpr static char const* property_product = "Product";
        /**
         * The OEM String Array WMI property name
         */
        constexpr static char const* property_oemstringarray = "OEMStringArray";
        /**
         * The Name WMI property name
         */
        constexpr static char const* property_name = "Name";
        /**
         * The Manufactuerer WMI property name
         */
        constexpr static char const* property_manufacturer = "Manufacturer";

    protected:
        /**
         * Collect data if it hasn't been collected yet, and return a pointer to the SMBIOS data object
         * @return A pointer to the collected SMBIOS data
         */
        virtual smbios_data const* data();
        /**
         * Attempt to collect data from WMI
         * @return Whether data was collected
         */
        virtual bool collect_data_from_wmi();
        /**
         * WMI connection object
         */
        std::unique_ptr<leatherman::windows::wmi> wmi_;
    };

}}  // namespace whereami::sources
