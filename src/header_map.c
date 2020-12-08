#include "parsing_aux.h"
#include <smolrtsp/header_map.h>

#include <string.h>

char *SmolRTSP_HeaderMap_find(SmolRTSP_HeaderMap *restrict self, const char *restrict key) {
    for (size_t i = 0; i < self->count; i++) {
        if (strncmp(self->headers[i].key, key, SMOLRTSP_HEADER_KEY_SIZE) == 0) {
            return self->headers[i].value;
        }
    }

    return NULL;
}

void SmolRTSP_HeaderMap_serialize(
    const SmolRTSP_HeaderMap *restrict self, SmolRTSP_UserWriter user_writer, void *user_cx) {
    for (size_t i = 0; i < self->count; i++) {
        SmolRTSP_Header_serialize(&self->headers[i], user_writer, user_cx);
    }

    user_writer(strlen(SMOLRTSP_CRLF), SMOLRTSP_CRLF, user_cx);
}