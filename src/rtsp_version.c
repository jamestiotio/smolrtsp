#include <rtsp_version.h>

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

void SmolRTSP_RTSPVersion_serialize(
    const SmolRTSP_RTSPVersion version, SmolRTSP_UserWriter user_writer, void *user_cx) {
    static const char rtsp_slash[] = "RTSP/", dot[] = ".";
    char minor[3], major[3];
    snprintf(minor, sizeof(minor), "%" PRIuLEAST8, version.minor);
    snprintf(major, sizeof(major), "%" PRIuLEAST8, version.major);

    user_writer(strlen(rtsp_slash), (const void *)rtsp_slash, user_cx);
    user_writer(strlen(minor), (const void *)minor, user_cx);
    user_writer(strlen(dot), (const void *)dot, user_cx);
    user_writer(strlen(major), (const void *)major, user_cx);
}