#include "Printer.h"

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

void Printer::AddJob(const std::string userRequested, int numPages)
{
	m_jobs.emplace(userRequested, m_nextId, numPages);
	++m_nextId;
}

void Printer::ProcessJobs()
{
	while (!m_jobs.empty())
	{
		std::cout << m_jobs.front();
		m_jobs.pop();
	}
}
