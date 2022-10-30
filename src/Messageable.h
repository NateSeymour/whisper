#ifndef WHISPER_IPC_MESSAGEABLE_H
#define WHISPER_IPC_MESSAGEABLE_H

#include <concepts>
#include <ostream>
#include <istream>

namespace nys::whisper {
    class Messageable
    {
    public:
        static constexpr const char* MIME = "application/none";

        virtual std::ostream& Write(std::ostream& os) const = 0;

        virtual std::istream& Consume(std::istream& is) = 0;

        std::istream& operator>>(std::istream& is)
        {
            return this->Consume(is);
        }

        friend std::ostream& operator<<(std::ostream& os, const Messageable& messageable)
        {
            return messageable.Write(os);
        }
    };

    template<class T>
    concept MessageableObject = std::is_base_of<Messageable, T>::value;
}

#endif //WHISPER_IPC_MESSAGEABLE_H
