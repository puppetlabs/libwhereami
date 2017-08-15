#include <internal/sources/wmi_source.hpp>

namespace lth_windows = leatherman::windows;

namespace whereami { namespace sources {

    smbios_data const* wmi::data()
    {
        if (!data_) {
            if (!wmi_) {
                wmi_.reset(new lth_windows::wmi);
            }
            collect_data_from_wmi();
        }
        return data_.get();
    }

    bool wmi::collect_data_from_wmi()
    {
        auto computersystem_values = wmi_->query(class_computersystem, {
                property_manufacturer,
                property_oemstringarray});
        auto computersystemproduct_values = wmi_->query(class_computersystemproduct, {
                property_name});
        auto baseboard_values = wmi_->query(class_baseboard, {
                property_manufacturer,
                property_product});
        auto bios_values = wmi_->query(class_bios, {
                property_manufacturer});

        if (computersystem_values.empty() && computersystemproduct_values.empty() && baseboard_values.empty()) {
            return false;
        }

        data_.reset(new smbios_data);

        data_->bios_vendor = lth_windows::wmi::get(bios_values, property_manufacturer);
        data_->board_manufacturer = lth_windows::wmi::get(baseboard_values, property_manufacturer);
        data_->board_product_name = lth_windows::wmi::get(baseboard_values, property_product);
        data_->manufacturer = lth_windows::wmi::get(computersystem_values, property_manufacturer);
        data_->product_name = lth_windows::wmi::get(computersystemproduct_values, property_name);

        for (auto& value : computersystem_values.at(0)) {
            if (value.first == property_oemstringarray) {
                data_->oem_strings.emplace_back(value.second);
            }
        }

        return true;
    }

}};  // namespace whereami::sources
