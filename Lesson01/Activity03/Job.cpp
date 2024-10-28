#include "Job.h"

Job::Job(const String& userRequested, int id, int numPages)
	: m_userRequested(userRequested)
	, m_id(id)
	, m_numPages(numPages)
{}

std::ostream& operator<<(std::ostream& os, const Job& job)
{
	os << "Job " << job.GetId() << ": "
		<< "[User: " << job.GetUserRequested() << ", "
		<< "Pages: " << job.GetNumPages() << "]\n";

	return os;
}
