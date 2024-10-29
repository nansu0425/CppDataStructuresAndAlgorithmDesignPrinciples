#pragma once

#include <queue>
#include <string>
#include <iostream>

class Job
{
private:
	using String	= std::string;

public:
	Job(const String& userRequested, int id, int numPages);

	String			GetUserRequested() const { return m_userRequested; }
	int				GetId() const { return m_id; }
	int				GetNumPages() const { return m_numPages; }

private:
	String			m_userRequested;
	int				m_id;
	int				m_numPages;
};

std::ostream& operator<<(std::ostream& os, const Job& job);

class Printer
{
private:
	using Queue		= std::queue<Job>;

public:
	void			AddJob(const std::string userRequested, int numPages = 1);
	void			ProcessJobs();

private:
	Queue			m_jobs;
	int				m_nextId = 0;
};
