#include "fwMetaData/Blob.hpp"
namespace fwMetaData
{

Blob::Blob(::fwTools::BufferObject::sptr buffer)
             : m_bufferObject(buffer)
{}

Blob::sptr Blob::New(::fwTools::BufferObject::sptr buffer)
{
    Blob::sptr blob(new Blob(buffer));

    return blob;
}

Blob::sptr Blob::New(void* buffer, unsigned int size)
{
    ::fwTools::BufferObject::sptr bufferObject = ::fwTools::BufferObject::New();
    bufferObject->setBuffer(buffer, size);
    Blob::sptr blob(new Blob(bufferObject));
    return blob;
}

unsigned int Blob::getSize() const
{
    return m_bufferObject->getSize();
}

char* Blob::getBuffer()const
{
    const ::fwTools::BufferObject::Lock& lock = m_bufferObject->lock();
    return static_cast<char *>( lock.getBuffer());
}

::fwTools::BufferObject::sptr Blob::getBufferObject()
{
    return m_bufferObject;
}



Base::sptr Blob::clone()
{
    return this->getSptr();
}

}