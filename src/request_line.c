#include "correctness.h"
#include "match.h"
#include <smolrtsp/request_line.h>

#include <string.h>

void SmolRTSP_RequestLine_serialize(
    const SmolRTSP_RequestLine *restrict self, SmolRTSP_UserWriter user_writer, void *user_cx) {
    precondition(self);
    precondition(user_writer);

    user_writer(Slice99_size(self->method), self->method.ptr, user_cx);
    user_writer(Slice99_size(self->uri), self->uri.ptr, user_cx);
    SmolRTSP_RTSPVersion_serialize(&self->version, user_writer, user_cx);
    user_writer(strlen("\r\n"), "\r\n", user_cx);
}

SmolRTSP_DeserializeResult SmolRTSP_RequestLine_deserialize(
    SmolRTSP_RequestLine *restrict self, Slice99 *restrict data, size_t *restrict bytes_read,
    SmolRTSP_RequestLineDeserializerState *restrict state) {
    precondition(self);
    precondition(data);
    precondition(bytes_read);
    precondition(state);

#define TRY_PARSE(if_state, expr)                                                                  \
    do {                                                                                           \
        if (*state == if_state) {                                                                  \
            MATCH(expr);                                                                           \
            (*state)++;                                                                            \
        }                                                                                          \
    } while (0)

    TRY_PARSE(
        SmolRTSP_RequestLineDeserializerStateMethod,
        SmolRTSP_Method_deserialize(&self->method, data, bytes_read));

    TRY_PARSE(
        SmolRTSP_RequestLineDeserializerStateRequestURI,
        SmolRTSP_RequestURI_deserialize(&self->uri, data, bytes_read));

    TRY_PARSE(
        SmolRTSP_RequestLineDeserializerStateRTSPVersion,
        SmolRTSP_RTSPVersion_deserialize(&self->version, data, bytes_read));

    TRY_PARSE(
        SmolRTSP_RequestLineDeserializerStateCRLF, SmolRTSP_match_str(data, bytes_read, "\r\n"));

#undef TRY_PARSE

    return SmolRTSP_DeserializeResultOk;
}

bool SmolRTSP_RequestLine_eq(
    const SmolRTSP_RequestLine *restrict lhs, const SmolRTSP_RequestLine *restrict rhs) {
    precondition(lhs);
    precondition(rhs);

    return Slice99_primitive_eq(lhs->method, rhs->method) &&
           Slice99_primitive_eq(lhs->uri, rhs->uri) &&
           SmolRTSP_RTSPVersion_eq(&lhs->version, &rhs->version);
}
