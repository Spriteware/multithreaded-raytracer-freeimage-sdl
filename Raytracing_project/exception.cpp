#include "exception.h"

Exception::Exception()
{
}

Exception::Exception(std::string p_message) :
Exception(p_message, false)
{
}


Exception::Exception(std::string p_message, bool p_fatal)
{
	m_message = p_message;
	m_fatal = p_fatal;
}

Exception::~Exception()
{
}

std::string Exception::getMessage()
{
	return m_message;
}

bool Exception::isFatal()
{
	return m_fatal;
}

