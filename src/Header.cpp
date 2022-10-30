#include "Header.h"

using namespace nys::whisper;

std::ostream &Header::Write(std::ostream &os) const
{
    os.write(this->magic, WHISPER_MAGIC_LENGTH);
    os.write((char*)&this->command, sizeof(this->command));
    os.write((char*)&this->version, sizeof(this->version));
    os.write((char*)&this->topic_length, sizeof(this->topic_length));
    os.write((char*)&this->mime_length, sizeof(this->mime_length));
    os.write((char*)&this->resource_length, sizeof(this->resource_length));
    os.write((char*)&this->body_length, sizeof(this->body_length));

    return os;
}

std::istream &Header::Consume(std::istream &is)
{
    is.read(this->magic, WHISPER_MAGIC_LENGTH);
    is.read((char*)&this->version, sizeof(this->version));
    is.read((char*)&this->command, sizeof(this->command));
    is.read((char*)&this->topic_length, sizeof(this->topic_length));
    is.read((char*)&this->mime_length, sizeof(this->mime_length));
    is.read((char*)&this->resource_length, sizeof(this->resource_length));
    is.read((char*)&this->body_length, sizeof(this->body_length));

    return is;
}
