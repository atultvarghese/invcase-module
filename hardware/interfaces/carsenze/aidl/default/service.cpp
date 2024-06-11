#define LOG_TAG "Carsenze"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "Carsenze.h"

using aidl::android::hardware::carsenze::Carsenze;
using std::string_literals::operator""s;

void logd(std::string msg) {
    std::cout << msg << std::endl;
    ALOGD("%s", msg.c_str());
}

void loge(std::string msg) {
    std::cout << msg << std::endl;
    ALOGE("%s", msg.c_str());
}

int main() {
    // Enable vndbinder to allow vendor-to-venfor binder call
    android::ProcessState::initWithDriver("/dev/vndbinder");

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    ABinderProcess_startThreadPool();

    std::shared_ptr<Carsenze> carsenze = ndk::SharedRefBase::make<Carsenze>();
    const std::string name = Carsenze::descriptor + "/default"s;

    if (carsenze != nullptr) {
        if(AServiceManager_addService(carsenze->asBinder().get(), name.c_str()) != STATUS_OK) {
            loge("Failed to register ICarsense service");
            return -1;
        }
    } else {
        loge("Failed to get ICarsenze instance");
        return -1;
    }

    logd("ICarsenze service starts to join service pool");
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE;  // should not reached
}
