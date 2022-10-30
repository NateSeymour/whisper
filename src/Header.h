#ifndef WHISPER_IPC_HEADER_H
#define WHISPER_IPC_HEADER_H

#include <cstdint>
#include "Messageable.h"

namespace nys::whisper
{
    static constexpr int WHISPER_MAGIC_LENGTH = 6;
    static constexpr int WHISPER_HEADER_SIZE = 12;

    enum class Command : uint8_t
    {
        TELL,
        SUBSCRIBE,
        PUSH
    };

    struct Header : public Messageable
    {
        char magic[WHISPER_MAGIC_LENGTH] = {};
        uint8_t version = -1;
        uint8_t command = -1;
        uint16_t mime_length = -1;
        uint16_t topic_length = -1;
        uint16_t resource_length = -1;
        uint16_t body_length = -1;

        static constexpr const char* MIME = "application/binary";

        std::ostream& Write(std::ostream& os) const override;
        std::istream& Consume(std::istream& is) override;
    };
}

#endif //WHISPER_IPC_HEADER_H
