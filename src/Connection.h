#ifndef WHISPER_IPC_CONNECTION_H
#define WHISPER_IPC_CONNECTION_H

#include <unistd.h>
#include <filesystem>
#include <future>
#include <utility>
#include <istream>
#include <ostream>
#include <nys/format.h>
#include <sys/poll.h>
#include <nys/sockbuf.h>
#include "Message.h"
#include "Messageable.h"
#include "Header.h"

namespace nys::whisper
{
    struct Connection
    {
        nys::sockbuf socket;

        template <MessageableObject T>
        Message<T> GetMessage(int timeout) const
        {
            /*
             * We use `poll` to be able to implement a response timeout.
             * Wait for incoming data before starting read.
             */
            struct pollfd fds = {
                    .fd = this->socket.fd(),
                    .events = POLLIN,
                    .revents = 0
            };

            int nfds = poll(&fds, 1, timeout);

            if(nfds == 0)
            {
                throw std::runtime_error("Reached timout on expected message!");
            }

            // Parse message
            Message<T> message;

            std::istream msg_stream((std::streambuf*)&this->socket);

            // Read header
            msg_stream >> message.header;

            // Header sanity checks
            if(strcmp(message.header.magic, "NYSIPC") != 0)
            {
                throw std::runtime_error("Header contains unexpected magic.");
            }

            if(message.header.version != 1)
            {
                throw std::runtime_error("Unsupported header version.");
            }

            // Compare MIME types
            message.mime.reserve(message.header.mime_length);
            msg_stream.read(message.mime.data(), message.header.mime_length);

            if(message.mime != T::MIME)
            {
                throw std::runtime_error("Unexpected MIME type");
            }

            // Read topic
            message.topic.reserve(message.header.topic_length);
            msg_stream.read(message.topic.data(), message.header.topic_length);

            // Read resource
            message.resource.reserve(message.header.resource_length);
            msg_stream.read(message.resource.data(), message.header.resource_length);

            // Read body
            msg_stream >> message.body;

            return message;
        }

        explicit Connection(sockbuf socket) : socket(std::move(socket)) {}

        // Delete default, copy and assignment constructors
        Connection() = delete;
        Connection(const Connection&) = delete;
        Connection& operator=(const Connection&) = delete;
    };
}

#endif //WHISPER_IPC_CONNECTION_H
