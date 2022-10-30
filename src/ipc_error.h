#ifndef WHISPER_IPC_IPC_ERROR_H
#define WHISPER_IPC_IPC_ERROR_H

#include <exception>
#include "Server.h"

namespace nys::whisper
{
    class ipc_error : public std::exception
    {
        ipc_error(const Server& server, const Connection& connection, const char *exception);
    };
}

#endif //WHISPER_IPC_IPC_ERROR_H
