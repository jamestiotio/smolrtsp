#include "../correctness.h"
#include "../match.h"
#include <smolrtsp/deserializers/method.h>

#include <stdlib.h>
#include <string.h>

struct SmolRTSP_MethodDeserializer {
    SmolRTSP_Method inner;
    size_t bytes_read;
};

SmolRTSP_MethodDeserializer *SmolRTSP_MethodDeserializer_new(void) {
    SmolRTSP_MethodDeserializer *self;
    if ((self = malloc(sizeof(*self))) == NULL) {
        return NULL;
    }

    self->bytes_read = 0;

    return self;
}

void SmolRTSP_MethodDeserializer_free(SmolRTSP_MethodDeserializer *self) {
    free(self);
}

SmolRTSP_Method SmolRTSP_MethodDeserializer_inner(SmolRTSP_MethodDeserializer *self) {
    precondition(self);

    return self->inner;
}

size_t SmolRTSP_MethodDeserializer_bytes_read(SmolRTSP_MethodDeserializer *self) {
    precondition(self);

    return self->bytes_read;
}

SmolRTSP_DeserializeResult SmolRTSP_MethodDeserializer_deserialize(
    SmolRTSP_MethodDeserializer *restrict self, Slice99 *restrict data) {
    precondition(self);
    precondition(data);

    size_t bytes_read = 0;

    MATCH(SmolRTSP_match_whitespaces(data, &bytes_read));
    self->inner.ptr = data->ptr;
    MATCH(SmolRTSP_match_ident(data, &bytes_read));
    self->inner = Slice99_from_ptrdiff(self->inner.ptr, data->ptr, sizeof(char));

    self->bytes_read = bytes_read;

    return SmolRTSP_DeserializeResultOk;
}
