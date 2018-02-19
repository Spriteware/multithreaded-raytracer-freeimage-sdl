#include <string>

class Exception
{
protected:
	std::string m_message;
	bool		m_fatal;

public:
	Exception();
	Exception(std::string p_message);
	Exception(std::string p_message, bool p_fatal);
	~Exception();

	virtual std::string getMessage();
	bool isFatal();
};
