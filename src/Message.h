#ifndef WHISPER_IPC_MESSAGE_H
#define WHISPER_IPC_MESSAGE_H

#include <string>
#include "Header.h"
#include "Messageable.h"

namespace nys::whisper
{
    template<MessageableObject T>
    class Message
    {
        Header header;
        std::string mime;
        std::string topic;
        std::string resource;
        T body;
    };
}

#endif //WHISPER_IPC_MESSAGE_H
