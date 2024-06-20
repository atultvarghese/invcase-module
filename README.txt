## Repo status 

project build/make/                             (*** NO BRANCH ***)
 -m	target/product/base_vendor.mk
project device/generic/goldfish/                (*** NO BRANCH ***)
 -m	init.ranchu.rc
project hardware/interfaces/                    (*** NO BRANCH ***)
 -m	compatibility_matrices/compatibility_matrix.202404.xml
 -m	compatibility_matrices/compatibility_matrix.202504.xml
 -m	compatibility_matrices/compatibility_matrix.5.xml
 -m	compatibility_matrices/compatibility_matrix.6.xml
 -m	compatibility_matrices/compatibility_matrix.7.xml
 -m	compatibility_matrices/compatibility_matrix.8.xml
 --	invcase/1.0/Android.bp.ignore
 --	invcase/1.0/IInvcase.hal
 --	invcase/aidl/Android.bp
 --	invcase/aidl/Android.bp.old
 --	invcase/aidl/aidl_api/android.hardware.invcase/current/android/hardware/invcase/IInvcase.aidl
 --	invcase/aidl/android/hardware/invcase/IInvcase.aidl
 --	invcase/aidl/default/Android.bp
 --	invcase/aidl/default/Invcase.cpp
 --	invcase/aidl/default/Invcase.h
 --	invcase/aidl/default/android.hardware.invcase-service.rc
 --	invcase/aidl/default/android.hardware.invcase-service.xml
 --	invcase/aidl/default/service.cpp
 --	invcase/compatible_matrices/compatible_matrix.current.xml
project system/sepolicy/                        (*** NO BRANCH ***)
 -m	prebuilts/api/202404/private/compat/31.0/31.0.ignore.cil
 -m	prebuilts/api/202404/private/compat/34.0/34.0.ignore.cil
 -m	prebuilts/api/202404/private/hwservice_contexts
 -m	prebuilts/api/202404/private/system_server.te
 -m	prebuilts/api/202404/public/attributes
 --	prebuilts/api/202404/public/hal_invcase.te
 -m	prebuilts/api/202404/public/hwservice.te
 -m	prebuilts/api/32.0/public/hwservice.te
 -m	prebuilts/api/34.0/public/hwservice.te
 -m	private/compat/31.0/31.0.ignore.cil
 -m	private/compat/34.0/34.0.ignore.cil
 -m	private/domain.te
 -m	private/hwservice_contexts
 -m	public/attributes
 --	public/hal_invcase.te
 -m	public/hwservice.te
 -m	public/system_server.te
 -m	vendor/file_contexts
 --	vendor/hal_invcase_service.te

## Repo diff for reference
project build/make/
diff --git a/target/product/base_vendor.mk b/target/product/base_vendor.mk
index 1854f9756f..f2b9bd3ae3 100644
--- a/target/product/base_vendor.mk
+++ b/target/product/base_vendor.mk
@@ -29,6 +29,9 @@ PRODUCT_PACKAGES += \
     servicemanager.recovery \
     shell_and_utilities_recovery \
     watchdogd.recovery \
+    android.hardware.invcase \
+    android.hardware.invcase-service \
+    Invcase
 
 PRODUCT_VENDOR_PROPERTIES += \
     ro.recovery.usb.vid?=18D1 \
@@ -105,3 +108,6 @@ PRODUCT_PACKAGES += \
 PRODUCT_PACKAGES += \
     adb_debug.prop \
     userdebug_plat_sepolicy.cil
+
+PRODUCT_ARTIFACT_PATH_REQUIREMENT_ALLOWED_LIST+= \
+    system/app/Invcase/%

project device/generic/goldfish/
diff --git a/init.ranchu.rc b/init.ranchu.rc
index 7ee7c20e..4be6f472 100644
--- a/init.ranchu.rc
+++ b/init.ranchu.rc
@@ -72,6 +72,9 @@ on zygote-start
 on boot
     chown root system /sys/power/wake_lock
     chown root system /sys/power/wake_unlock
+    insmod /system/lib/modules/invcase.ko
+    chown system system /dev/invcase
+    chmod 0600 /dev/invcase
 
     # Create an unused USB gadget to allow sysfs testing
     mkdir /config/usb_gadget/g1 0770 root root

project hardware/interfaces/
diff --git a/compatibility_matrices/compatibility_matrix.202404.xml b/compatibility_matrices/compatibility_matrix.202404.xml
index a5e40ddfe2..9603bd41c5 100644
--- a/compatibility_matrices/compatibility_matrix.202404.xml
+++ b/compatibility_matrices/compatibility_matrix.202404.xml
@@ -153,6 +153,13 @@
             <name>IBluetoothFinder</name>
             <instance>default</instance>
         </interface>
+    </hal><hal format="aidl" optional="true">
+        <name>android.hardware.invcase</name>
+        <version>1</version>
+        <interface>
+            <name>IInvcase</name>
+            <instance>default</instance>
+        </interface>
     </hal>
     <hal format="aidl">
         <name>android.hardware.bluetooth.lmp_event</name>
@@ -708,4 +715,12 @@
             <regex-instance>.*</regex-instance>
         </interface>
     </hal>
+    <hal format="aidl" optional="true">
+        <name>android.hardware.invcase</name>
+        <version>1</version>
+        <interface>
+            <name>IInvcase</name>
+            <instance>default</instance>
+        </interface>
+    </hal>
 </compatibility-matrix>
diff --git a/compatibility_matrices/compatibility_matrix.8.xml b/compatibility_matrices/compatibility_matrix.8.xml
index 7054bfa240..d9d691e3e8 100644
--- a/compatibility_matrices/compatibility_matrix.8.xml
+++ b/compatibility_matrices/compatibility_matrix.8.xml
@@ -724,4 +724,12 @@
             <regex-instance>.*</regex-instance>
         </interface>
     </hal>
+    <hal format="aidl" optional="true">
+        <name>android.hardware.invcase</name>
+        <version>1</version>
+        <interface>
+            <name>IInvcase</name>
+            <instance>default</instance>
+        </interface>
+    </hal>
 </compatibility-matrix>

project system/sepolicy/
diff --git a/prebuilts/api/202404/private/compat/34.0/34.0.ignore.cil b/prebuilts/api/202404/private/compat/34.0/34.0.ignore.cil
index 5f835a4cb..59cf4314c 100644
--- a/prebuilts/api/202404/private/compat/34.0/34.0.ignore.cil
+++ b/prebuilts/api/202404/private/compat/34.0/34.0.ignore.cil
@@ -49,4 +49,5 @@
     aconfigd
     aconfigd_exec
     aconfigd_socket
+    hal_invcase_hwservice
   ))
diff --git a/prebuilts/api/202404/private/hwservice_contexts b/prebuilts/api/202404/private/hwservice_contexts
index 4a44dc58b..67b3f5f11 100644
--- a/prebuilts/api/202404/private/hwservice_contexts
+++ b/prebuilts/api/202404/private/hwservice_contexts
@@ -84,3 +84,4 @@ android.system.net.netd::INetd                                  u:object_r:syste
 android.system.suspend::ISystemSuspend                          u:object_r:system_suspend_hwservice:s0
 android.system.wifi.keystore::IKeystore                         u:object_r:system_wifi_keystore_hwservice:s0
 *                                                               u:object_r:default_android_hwservice:s0
+android.hardware.invcase::IInvcase                              u:object_r:hal_invcase_hwservice:s0
diff --git a/prebuilts/api/202404/private/system_server.te b/prebuilts/api/202404/private/system_server.te
index 886499e07..801a492d8 100644
--- a/prebuilts/api/202404/private/system_server.te
+++ b/prebuilts/api/202404/private/system_server.te
@@ -350,6 +350,7 @@ hal_client_domain(system_server, hal_weaver)
 hal_client_domain(system_server, hal_wifi)
 hal_client_domain(system_server, hal_wifi_hostapd)
 hal_client_domain(system_server, hal_wifi_supplicant)
+hal_client_domain(system_server, hal_invcase)
 # The bootctl is a pass through HAL mode under recovery mode. So we skip the
 # permission for recovery in order not to give system server the access to
 # the low level block devices.
diff --git a/prebuilts/api/202404/public/attributes b/prebuilts/api/202404/public/attributes
index 759b773a2..f5928dcdb 100644
--- a/prebuilts/api/202404/public/attributes
+++ b/prebuilts/api/202404/public/attributes
@@ -403,6 +403,7 @@ hal_attribute(weaver);
 hal_attribute(wifi);
 hal_attribute(wifi_hostapd);
 hal_attribute(wifi_supplicant);
+hal_attribute(invcase);
 
 # HwBinder services offered across the core-vendor boundary
 #
@@ -449,3 +450,7 @@ attribute charger_type;
 
 # All types of ART properties.
 attribute dalvik_config_prop_type;
+
+# attribute hal_invcase;
+# attribute hal_invcase_client;
+# attribute hal_invcase_server; 
diff --git a/prebuilts/api/202404/public/hwservice.te b/prebuilts/api/202404/public/hwservice.te
index 11b77f08b..1b9f66928 100644
--- a/prebuilts/api/202404/public/hwservice.te
+++ b/prebuilts/api/202404/public/hwservice.te
@@ -90,6 +90,7 @@ type hidl_base_hwservice, hwservice_manager_type;
 type hidl_manager_hwservice, hwservice_manager_type, coredomain_hwservice;
 type hidl_memory_hwservice, hwservice_manager_type, coredomain_hwservice;
 type hidl_token_hwservice, hwservice_manager_type, coredomain_hwservice;
+type hal_invcase_hwservice, hwservice_manager_type;
 
 ###
 ### Neverallow rules
diff --git a/prebuilts/api/34.0/public/hwservice.te b/prebuilts/api/34.0/public/hwservice.te
index 11b77f08b..1b9f66928 100644
--- a/prebuilts/api/34.0/public/hwservice.te
+++ b/prebuilts/api/34.0/public/hwservice.te
@@ -90,6 +90,7 @@ type hidl_base_hwservice, hwservice_manager_type;
 type hidl_manager_hwservice, hwservice_manager_type, coredomain_hwservice;
 type hidl_memory_hwservice, hwservice_manager_type, coredomain_hwservice;
 type hidl_token_hwservice, hwservice_manager_type, coredomain_hwservice;
+type hal_invcase_hwservice, hwservice_manager_type;
 
 ###
 ### Neverallow rules
diff --git a/private/compat/34.0/34.0.ignore.cil b/private/compat/34.0/34.0.ignore.cil
index 455cbff28..783815d26 100644
--- a/private/compat/34.0/34.0.ignore.cil
+++ b/private/compat/34.0/34.0.ignore.cil
@@ -51,4 +51,5 @@
     aconfigd_socket
     enable_16k_pages_prop
     proc_cgroups
+    hal_invcase_hwservice
   ))
diff --git a/private/hwservice_contexts b/private/hwservice_contexts
index 4a44dc58b..67b3f5f11 100644
--- a/private/hwservice_contexts
+++ b/private/hwservice_contexts
@@ -84,3 +84,4 @@ android.system.net.netd::INetd                                  u:object_r:syste
 android.system.suspend::ISystemSuspend                          u:object_r:system_suspend_hwservice:s0
 android.system.wifi.keystore::IKeystore                         u:object_r:system_wifi_keystore_hwservice:s0
 *                                                               u:object_r:default_android_hwservice:s0
+android.hardware.invcase::IInvcase                              u:object_r:hal_invcase_hwservice:s0
diff --git a/public/attributes b/public/attributes
index 759b773a2..f363134b6 100644
--- a/public/attributes
+++ b/public/attributes
@@ -403,6 +403,7 @@ hal_attribute(weaver);
 hal_attribute(wifi);
 hal_attribute(wifi_hostapd);
 hal_attribute(wifi_supplicant);
+hal_attribute(invcase);
 
 # HwBinder services offered across the core-vendor boundary
 #
@@ -449,3 +450,7 @@ attribute charger_type;
 
 # All types of ART properties.
 attribute dalvik_config_prop_type;
+
+# attribute hal_invcase;
+# attribute hal_invcase_client;
+# attribute hal_invcase_server;
diff --git a/public/hwservice.te b/public/hwservice.te
index d6f2de45d..e6ce4e682 100644
--- a/public/hwservice.te
+++ b/public/hwservice.te
@@ -90,6 +90,7 @@ type hidl_base_hwservice, hwservice_manager_type;
 type hidl_manager_hwservice, hwservice_manager_type, coredomain_hwservice;
 type hidl_memory_hwservice, hwservice_manager_type, coredomain_hwservice;
 type hidl_token_hwservice, hwservice_manager_type, coredomain_hwservice;
+type hal_invcase_hwservice, hwservice_manager_type;
 
 # system/sepolicy/public is for vendor-facing type and attribute definitions.
 # DO NOT ADD allow, neverallow, or dontaudit statements here.
diff --git a/public/system_server.te b/public/system_server.te
index 55b163bd4..6b923d396 100644
--- a/public/system_server.te
+++ b/public/system_server.te
@@ -8,3 +8,5 @@ type system_server_tmpfs, file_type, mlstrustedobject;
 # system/sepolicy/public is for vendor-facing type and attribute definitions.
 # DO NOT ADD allow, neverallow, or dontaudit statements here.
 # Instead, add such policy rules to system/sepolicy/private/*.te.
+
+hal_client_domain(system_server, hal_invcase)
diff --git a/vendor/file_contexts b/vendor/file_contexts
index edd1c7133..9bd55dab6 100644
--- a/vendor/file_contexts
+++ b/vendor/file_contexts
@@ -202,3 +202,4 @@
 /(vendor|system/vendor)/lib(64)?/libutils\.so u:object_r:same_process_hal_file:s0
 /(vendor|system/vendor)/lib(64)?/libutilscallstack\.so u:object_r:same_process_hal_file:s0
 /(vendor|system/vendor)/lib(64)?/libz\.so u:object_r:same_process_hal_file:s0
+/(vendor|system/vendor)/bin/hw/android\.hardware\.invcase-service u:object_r:hal_invcase_service_exec:s0
