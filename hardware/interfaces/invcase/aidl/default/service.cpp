#define LOG_TAG "Invcase_hal"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "Invcase.h"

using aidl::android::hardware::invcase::Invcase;
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
    // new line compared to the power module main.cpp
    //android::ProcessState::initWithDriver("/dev/binder");

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    // ABinderProcess_startThreadPool();

    std::shared_ptr<Invcase> invcase = ndk::SharedRefBase::make<Invcase>();
    const std::string name = std::string() + Invcase::descriptor + "/default";

    /*if (invcase != nullptr) {
        if(AServiceManager_addService(invcase->asBinder().get(), name.c_str()) != STATUS_OK) {
            loge("Failed to register IInvcase service");
            return -1;
        }
    } else {
        loge("Failed to get IInvcase instance");
        return -1;
    }*/

    binder_status_t status = AServiceManager_addService(invcase->asBinder().get(), name.c_str());
    CHECK_EQ(status, STATUS_OK);

    logd("IInvcase service starts to join service pool");
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE;  // should not reached
}
