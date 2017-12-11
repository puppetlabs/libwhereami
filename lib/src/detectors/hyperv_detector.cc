#include <internal/detectors/hyperv_detector.hpp>
#include <internal/vm.hpp>

using namespace std;

namespace whereami { namespace detectors {

   result hyperv(const sources::cpuid_base& cpuid_source, sources::smbios_base& smbios_source)
   {
       result res {vm::hyperv};

       if (cpuid_source.vendor() == "Microsoft Hv" ||
           smbios_source.manufacturer().find("Microsoft") != string::npos) {
           res.validate();
       }

       return res;
   }

}}  // namespace whereami::detectors
