/**
 * @file
 * An RTSP reason phrase.
 */

#pragma once

#include <smolrtsp/types/error.h>

#include <stdbool.h>

#include <slice99.h>

/**
 * An RTSP reason phrase.
 */
typedef CharSlice99 SmolRTSP_ReasonPhrase;

/**
 * Parses @p data to @p self.
 *
 * @pre `self != NULL`
 */
SmolRTSP_ParseResult
SmolRTSP_ReasonPhrase_parse(SmolRTSP_ReasonPhrase *restrict self, CharSlice99 data);

/**
 * Tests @p lhs and @p rhs for equality.
 */
bool SmolRTSP_ReasonPhrase_eq(SmolRTSP_ReasonPhrase lhs, SmolRTSP_ReasonPhrase rhs);