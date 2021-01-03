#ifndef SMOLRTSP_DESER_AUX_H
#define SMOLRTSP_DESER_AUX_H

#include <smolrtsp/deserialization.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MATCH(deserialize_res)                                                                     \
    do {                                                                                           \
        const SmolRTSP_DeserializeResult deserialize_res_var = deserialize_res;                    \
        if (deserialize_res_var == SmolRTSP_DeserializeResultErr ||                                \
            deserialize_res_var == SmolRTSP_DeserializeResultPending) {                            \
            return deserialize_res_var;                                                            \
        }                                                                                          \
    } while (false)

typedef bool (*SmolRTSP_Matcher)(char c, void *cx);

SmolRTSP_DeserializeResult SmolRTSP_match_until(
    Slice99 *restrict data, size_t *restrict bytes_read, SmolRTSP_Matcher matcher, void *cx);

SmolRTSP_DeserializeResult SmolRTSP_match_until_str(
    Slice99 *restrict data, size_t *restrict bytes_read, const char *restrict str);

SmolRTSP_DeserializeResult
SmolRTSP_match_until_crlf(Slice99 *restrict data, size_t *restrict bytes_read);

SmolRTSP_DeserializeResult
SmolRTSP_match_char(Slice99 *restrict data, size_t *restrict bytes_read, char c);

SmolRTSP_DeserializeResult
SmolRTSP_match_str(Slice99 *restrict data, size_t *restrict bytes_read, const char *restrict str);

SmolRTSP_DeserializeResult
SmolRTSP_match_whitespaces(Slice99 *restrict data, size_t *restrict bytes_read);

SmolRTSP_DeserializeResult
SmolRTSP_match_non_whitespaces(Slice99 *restrict data, size_t *restrict bytes_read);

SmolRTSP_DeserializeResult
SmolRTSP_match_numeric(Slice99 *restrict data, size_t *restrict bytes_read);

SmolRTSP_DeserializeResult
SmolRTSP_match_ident(Slice99 *restrict data, size_t *restrict bytes_read);

SmolRTSP_DeserializeResult
SmolRTSP_match_header_name(Slice99 *restrict data, size_t *restrict bytes_read);

#endif // SMOLRTSP_DESER_AUX_H
