#define LOG_TAG "Carsenze"

#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include "carsenze.h"

namespace aidl {
    namespace android {
        namespace hardware {
            namespace carsenze {

//String getMemoryStats();
                ndk::ScopedAStatus Carsenze::getMemoryStats(std::string* _aidl_return) {
                    *_aidl_return =  "Memory = 1024 MB";
                    return ndk::ScopedAStatus::ok();
                }
//String getCpuStats();
                ndk::ScopedAStatus Carsenze::getCpuStats(std::string* _aidl_return) {
                    *_aidl_return =  "CPU = 74.32 %";
                    return ndk::ScopedAStatus::ok();
                }
//String getNetworkStats();
                ndk::ScopedAStatus Carsenze::getCpuStats(std::string* _aidl_return) {
                    *_aidl_return =  "Network = 10 Mb/s";
                    return ndk::ScopedAStatus::ok();
                }
}  // namespace carsenze
}  // namespace hardware
}  // namespace android
}  // namespace aidl
