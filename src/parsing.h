#ifndef SMOLRTSP_PARSING_H
#define SMOLRTSP_PARSING_H

#include <smolrtsp/common.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <datatype99.h>
#include <slice99.h>

#define MATCH(parse_expr)                                                                          \
    do {                                                                                           \
        const SmolRTSP_ParseResult parse_res_var = parse_expr;                                     \
                                                                                                   \
        match(parse_res_var) {                                                                     \
            of(SmolRTSP_ParseResult_Success, status) {                                             \
                input = CharSlice99_advance(input, status->offset);                                \
                                                                                                   \
                if (!status->is_complete) {                                                        \
                    return parse_res_var;                                                          \
                }                                                                                  \
            }                                                                                      \
            of(SmolRTSP_ParseResult_Failure, err) return SmolRTSP_ParseResult_Failure(*err);       \
        }                                                                                          \
    } while (0)

#define TRY_PARSE(if_state, expr)                                                                  \
    do {                                                                                           \
        if (if_state == state->tag) {                                                              \
            MATCH(expr);                                                                           \
            state->tag++;                                                                          \
        }                                                                                          \
    } while (0)

SmolRTSP_ParseResult
smolrtsp_match_until(CharSlice99 input, bool (*matcher)(char c, void *ctx), void *ctx);
SmolRTSP_ParseResult smolrtsp_match_until_str(CharSlice99 input, const char *restrict str);

SmolRTSP_ParseResult smolrtsp_match_until_crlf(CharSlice99 input);
SmolRTSP_ParseResult smolrtsp_match_char(CharSlice99 input, char c);
SmolRTSP_ParseResult smolrtsp_match_str(CharSlice99 input, const char *restrict str);
SmolRTSP_ParseResult smolrtsp_match_whitespaces(CharSlice99 input);
SmolRTSP_ParseResult smolrtsp_match_non_whitespaces(CharSlice99 input);
SmolRTSP_ParseResult smolrtsp_match_numeric(CharSlice99 input);
SmolRTSP_ParseResult smolrtsp_match_ident(CharSlice99 input);
SmolRTSP_ParseResult smolrtsp_match_header_name(CharSlice99 input);

#endif // SMOLRTSP_PARSING_H
