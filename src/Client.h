#ifndef WHISPER_IPC_CLIENT_H
#define WHISPER_IPC_CLIENT_H

#include <filesystem>
#include <cstring>
#include <future>
#include <unistd.h>
#include <thread>
#include <memory>
#include <poll.h>
#include <arpa/inet.h>
#include "Connection.h"
#include "Header.h"

namespace nys::whisper {
    class Client
    {
    private:
        std::string socket_path;

    public:
        explicit Client(std::string socket_path) : socket_path(std::move(socket_path)) {}
    };
}

#endif //WHISPER_IPC_CLIENT_H
