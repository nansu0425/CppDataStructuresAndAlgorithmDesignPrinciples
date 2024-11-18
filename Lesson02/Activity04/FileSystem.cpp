#include "FileSystem.h"

FileSystem::Node::Node(Str name, Node* ptrParent, bool isDir)
	: name(name)
	, ptrParent(ptrParent)
	, isDir(isDir)
{}

FileSystem::FileSystem()
	: m_ptrRootDir(new Node("", nullptr, true))
	, m_ptrCurDir(m_ptrRootDir)
{
	// insert test code
	insert("hello", "", false);
	insert("world", "\\", true);
	insert("good", "", false);

	m_ptrCurDir = m_ptrCurDir->ptrsChild[1];

	insert("bye", "", false);
	insert("today", "\\world", false);
	insert("is", "", true);

	insert("good", "is", true);
	insert("super", "\\world\\is", false);
	insert("exciting", "is", false);

	m_ptrCurDir = m_ptrRootDir;
	m_ptrCurDir = m_ptrCurDir->ptrsChild[1];
}

std::string FileSystem::getCurPath() const
{
	Str curPath = Str("\\");

	// 현재 디렉토리가 루트인 경우
	if (m_ptrCurDir->ptrParent == nullptr)
	{
		return curPath;
	}

	curPath = getPath(m_ptrCurDir->ptrParent) 
			  + "\\" 
			  + m_ptrCurDir->name;

	return curPath;
}

bool FileSystem::isPath(const std::string& path)
{
	if (path.empty())
	{
		return false;
	}

	int lenPath = static_cast<int>(path.size());

	// 절대 경로 탐색
	if (path[0] == '\\')
	{
		// 루트 경로
		if (path == "\\")
		{
			return true;
		}
		
		// 찾는 디렉토리/파일이 없는 경우
		if (searchPath(m_ptrRootDir, 1, lenPath, path) == nullptr)
		{
			return false;
		}
	}
	// 상대 경로 탐색
	else
	{
		// 찾는 디렉토리/파일이 없는 경우
		if (searchPath(m_ptrCurDir, 0, lenPath, path) == nullptr)
		{
			return false;
		}
	}

	return true;
}

void FileSystem::insert(const std::string& name, const std::string& path, bool isDir)
{
	// 현재 경로에 삽입
	if (path.empty())
	{
		m_ptrCurDir->ptrsChild.emplace_back(new Node(name, m_ptrCurDir, isDir));
		std::cout << getPath(m_ptrCurDir->ptrsChild.back()) << std::endl;

		return;
	}

	Node* ptrDir = nullptr;
	int lenPath = static_cast<int>(path.size());

	// 절대 경로인 경우
	if (path[0] == '\\')
	{
		// 루트 경로인 경우
		if (path == "\\")
		{
			m_ptrRootDir->ptrsChild.emplace_back(new Node(name, m_ptrRootDir, isDir));
			std::cout << getPath(m_ptrRootDir->ptrsChild.back()) << std::endl;

			return;
		}

		ptrDir = searchPath(m_ptrRootDir, 1, lenPath, path);
	}
	// 상대 경로 탐색
	else
	{
		ptrDir = searchPath(m_ptrCurDir, 0, lenPath, path);
	}

	// 찾는 디렉토리가 없거나 디렉토리가 아닌 경우
	if ((ptrDir == nullptr) ||
		(!ptrDir->isDir))
	{
		std::cout << "Failed to search " + path << std::endl;
		return;
	}

	ptrDir->ptrsChild.emplace_back(new Node(name, ptrDir, isDir));
	std::cout << getPath(ptrDir->ptrsChild.back()) << std::endl;
}

std::string FileSystem::getPath(Node* ptrDir) const
{
	Str path = Str("");

	// 파라미터가 루트 디렉토리인 경우
	if (ptrDir->ptrParent == nullptr)
	{
		return path;
	}

	path = getPath(ptrDir->ptrParent) 
		   + "\\" 
		   + ptrDir->name;

	return path;
}

FileSystem::Node* FileSystem::searchPath(Node* ptrCur, int idxNameFirst, int lenPath, const std::string& path)
{
	// 탐색 완료 후 현재 노드 리턴
	if (lenPath < idxNameFirst)
	{
		return ptrCur;
	}

	int idxNameLast = idxNameFirst + 1;

	while ((path[idxNameLast] != '\\') &&
		   (idxNameLast != lenPath))
	{
		++idxNameLast;
	}

	// 현재 디렉토리에서 확인하려는 파일/디렉토리 이름을 구한다
	Str name = path.substr(idxNameFirst, idxNameLast - idxNameFirst);

	for (Node* ptrChild : ptrCur->ptrsChild)
	{
		// 현재 디렉토리까지 path와 일치하면 하위 레벨로 내려가서 탐색
		if (ptrChild->name == name)
		{
			return searchPath(ptrChild, idxNameLast + 1, lenPath, path);
		}
	}

	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const FileSystem& fs)
{
	os << fs.getCurPath() << "> ";

	return os;
}
