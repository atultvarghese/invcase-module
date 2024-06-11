
#pragma once

#include <aidl/android/hardware/carsenze/BnCarsenze.h>

namespace aidl {
    namespace android {
        namespace hardware {
            namespace carsenze {

                class Carsenze : public BnCarsenze {
                public:
                    //String getMemoryStats();
                    ndk::ScopedAStatus getMemoryStats(std::string* _aidl_return);
                    //String getCpuStats();
                    ndk::ScopedAStatus getCpuStats(std::string* _aidl_return);
                    //String getNetworkStats();
                    ndk::ScopedAStatus getNetworkStats(std::string* _aidl_return);
                };

            }  // namespace carsenze
        }  // namespace hardware
    }  // namespace android
}  // namespace aidl
