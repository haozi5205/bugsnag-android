#include <greatest/greatest.h>
#include <event.h>
#include <utils/string.h>
#include "../../main/assets/include/bugsnag.h"
#include <event.h>

bugsnag_event *init_event() {
    bugsnag_event *event = calloc(1, sizeof(bugsnag_event));
    bsg_strncpy_safe(event->context, "Foo", sizeof(event->context));

    bsg_strncpy_safe(event->app.binaryArch, "x86", sizeof(event->app.binaryArch));
    bsg_strncpy_safe(event->app.build_uuid, "123", sizeof(event->app.build_uuid));
    bsg_strncpy_safe(event->app.id, "fa02", sizeof(event->app.id));
    bsg_strncpy_safe(event->app.release_stage, "dev", sizeof(event->app.release_stage));
    bsg_strncpy_safe(event->app.type, "C", sizeof(event->app.type));
    bsg_strncpy_safe(event->app.version, "1.0", sizeof(event->app.version));
    event->app.version_code = 55;
    event->app.duration = 9019;
    event->app.duration_in_foreground = 7017;
    event->app.in_foreground = true;

    event->device.jailbroken = true;
    event->device.total_memory = 1095092340;
    bsg_strncpy_safe(event->device.id, "my-id-123", sizeof(event->device.id));
    bsg_strncpy_safe(event->device.locale, "en", sizeof(event->device.locale));
    bsg_strncpy_safe(event->device.os_name, "android", sizeof(event->device.os_name));
    bsg_strncpy_safe(event->device.manufacturer, "Google", sizeof(event->device.manufacturer));
    bsg_strncpy_safe(event->device.model, "Nexus", sizeof(event->device.model));
    bsg_strncpy_safe(event->device.os_version, "9.1", sizeof(event->device.os_version));
    bsg_strncpy_safe(event->device.orientation, "portrait", sizeof(event->device.orientation));
    event->device.time = 7609;

    bsg_strncpy_safe(event->error.errorClass, "SIGSEGV", sizeof(event->error.errorClass));
    bsg_strncpy_safe(event->error.errorMessage, "Whoops!", sizeof(event->error.errorMessage));
    bsg_strncpy_safe(event->error.type, "C", sizeof(event->error.type));
    return event;
}

TEST test_event_context(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("Foo", bugsnag_event_get_context(event));
    bugsnag_event_set_context(event, "SomeContext");
    ASSERT_STR_EQ("SomeContext", bugsnag_event_get_context(event));
    free(event);
    PASS();
}

TEST test_app_binary_arch(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("x86", bugsnag_app_get_binary_arch(event));
    bugsnag_app_set_binary_arch(event, "armeabi-v7a");
    ASSERT_STR_EQ("armeabi-v7a", bugsnag_app_get_binary_arch(event));
    free(event);
    PASS();
}

TEST test_app_build_uuid(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("123", bugsnag_app_get_build_uuid(event));
    bugsnag_app_set_build_uuid(event, "my-id-123");
    ASSERT_STR_EQ("my-id-123", bugsnag_app_get_build_uuid(event));
    free(event);
    PASS();
}

TEST test_app_id(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("fa02", bugsnag_app_get_id(event));
    bugsnag_app_set_id(event, "my-id-123");
    ASSERT_STR_EQ("my-id-123", bugsnag_app_get_id(event));
    free(event);
    PASS();
}

TEST test_app_release_stage(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("dev", bugsnag_app_get_release_stage(event));
    bugsnag_app_set_release_stage(event, "beta");
    ASSERT_STR_EQ("beta", bugsnag_app_get_release_stage(event));
    free(event);
    PASS();
}

TEST test_app_type(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("C", bugsnag_app_get_type(event));
    bugsnag_app_set_type(event, "C++");
    ASSERT_STR_EQ("C++", bugsnag_app_get_type(event));
    free(event);
    PASS();
}

TEST test_app_version(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("1.0", bugsnag_app_get_version(event));
    bugsnag_app_set_version(event, "2.2");
    ASSERT_STR_EQ("2.2", bugsnag_app_get_version(event));
    free(event);
    PASS();
}

TEST test_app_version_code(void) {
    bugsnag_event *event = init_event();
    ASSERT_EQ(55, bugsnag_app_get_version_code(event));
    bugsnag_app_set_version_code(event, 99);
    ASSERT_EQ(99, bugsnag_app_get_version_code(event));
    free(event);
    PASS();
}

TEST test_app_duration(void) {
    bugsnag_event *event = init_event();
    ASSERT_EQ(9019, bugsnag_app_get_duration(event));
    bugsnag_app_set_duration(event, 552);
    ASSERT_EQ(552, bugsnag_app_get_duration(event));
    free(event);
    PASS();
}

TEST test_app_duration_in_foreground(void) {
    bugsnag_event *event = init_event();
    ASSERT_EQ(7017, bugsnag_app_get_duration_in_foreground(event));
    bugsnag_app_set_duration_in_foreground(event, 209);
    ASSERT_EQ(209, bugsnag_app_get_duration_in_foreground(event));
    free(event);
    PASS();
}

TEST test_app_in_foreground(void) {
    bugsnag_event *event = init_event();
    ASSERT(bugsnag_app_get_in_foreground(event));
    bugsnag_app_set_in_foreground(event, false);
    ASSERT_FALSE(bugsnag_app_get_in_foreground(event));
    free(event);
    PASS();
}


TEST test_device_jailbroken(void) {
    bugsnag_event *event = init_event();
    ASSERT(bugsnag_device_get_jailbroken(event));
    bugsnag_device_set_jailbroken(event, false);
    ASSERT_FALSE(bugsnag_device_get_jailbroken(event));
    free(event);
    PASS();
}

TEST test_device_id(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("my-id-123", event->device.id);
    bugsnag_device_set_id(event, "SomeId");
    ASSERT_STR_EQ("SomeId", bugsnag_device_get_id(event));
    free(event);
    PASS();
}

TEST test_device_locale(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("en", event->device.locale);
    bugsnag_device_set_locale(event, "hue");
    ASSERT_STR_EQ("hue", bugsnag_device_get_locale(event));
    free(event);
    PASS();
}

TEST test_device_manufacturer(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("Google", event->device.manufacturer);
    bugsnag_device_set_manufacturer(event, "Apple");
    ASSERT_STR_EQ("Apple", bugsnag_device_get_manufacturer(event));
    free(event);
    PASS();
}

TEST test_device_model(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("Nexus", event->device.model);
    bugsnag_app_set_model(event, "Pixel");
    ASSERT_STR_EQ("Pixel", bugsnag_device_get_model(event));
    free(event);
    PASS();
}

TEST test_device_os_version(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("9.1", event->device.os_version);
    bugsnag_device_set_os_version(event, "7.0");
    ASSERT_STR_EQ("7.0", bugsnag_device_get_os_version(event));
    free(event);
    PASS();
}

TEST test_device_total_memory(void) {
    bugsnag_event *event = init_event();
    ASSERT_EQ(1095092340, event->device.total_memory);
    bugsnag_device_set_total_memory(event, 200923409);
    ASSERT_EQ(200923409, bugsnag_device_get_total_memory(event));
    free(event);
    PASS();
}

TEST test_device_orientation(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("portrait", event->device.orientation);
    bugsnag_device_set_orientation(event, "landscape");
    ASSERT_STR_EQ("landscape", bugsnag_device_get_orientation(event));
    free(event);
    PASS();
}

TEST test_device_time(void) {
    bugsnag_event *event = init_event();
    ASSERT_EQ(7609, event->device.time);
    bugsnag_device_set_time(event, 1509);
    ASSERT_EQ(1509, bugsnag_device_get_time(event));
    free(event);
    PASS();
}

TEST test_device_os_name(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("android", event->device.os_name);
    bugsnag_device_set_os_name(event, "samsung");
    ASSERT_STR_EQ("samsung", bugsnag_device_get_os_name(event));
    free(event);
    PASS();
}

TEST test_error_class(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("SIGSEGV", event->error.errorClass);
    bugsnag_error_set_error_class(event, "SIGTRAP");
    ASSERT_STR_EQ("SIGTRAP", bugsnag_error_get_error_class(event));
    free(event);
    PASS();
}

TEST test_error_message(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("Whoops!", event->error.errorMessage);
    bugsnag_error_set_error_message(event, "Invalid Foo");
    ASSERT_STR_EQ("Invalid Foo", bugsnag_error_get_error_message(event));
    free(event);
    PASS();
}

TEST test_error_type(void) {
    bugsnag_event *event = init_event();
    ASSERT_STR_EQ("C", event->error.type);
    bugsnag_error_set_error_type(event, "C++");
    ASSERT_STR_EQ("C++", bugsnag_error_get_error_type(event));
    free(event);
    PASS();
}

SUITE(event_mutators) {
    RUN_TEST(test_event_context);
    RUN_TEST(test_app_binary_arch);
    RUN_TEST(test_app_build_uuid);
    RUN_TEST(test_app_id);
    RUN_TEST(test_app_release_stage);
    RUN_TEST(test_app_type);
    RUN_TEST(test_app_version);
    RUN_TEST(test_app_version_code);
    RUN_TEST(test_app_duration);
    RUN_TEST(test_app_duration_in_foreground);
    RUN_TEST(test_app_in_foreground);
    RUN_TEST(test_device_jailbroken);
    RUN_TEST(test_device_id);
    RUN_TEST(test_device_locale);
    RUN_TEST(test_device_manufacturer);
    RUN_TEST(test_device_model);
    RUN_TEST(test_device_os_version);
    RUN_TEST(test_device_total_memory);
    RUN_TEST(test_device_orientation);
    RUN_TEST(test_device_time);
    RUN_TEST(test_device_os_name);
    RUN_TEST(test_error_class);
    RUN_TEST(test_error_message);
    RUN_TEST(test_error_type);
}