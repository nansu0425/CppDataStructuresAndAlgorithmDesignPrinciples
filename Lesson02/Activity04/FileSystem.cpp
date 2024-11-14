#include "FileSystem.h"

FileSystem::Node::Node(Str name, Node* ptrParent, bool isDir)
	: name(name)
	, ptrParent(ptrParent)
	, isDir(isDir)
{}

FileSystem::FileSystem()
	: m_ptrCurDir(new Node("", nullptr, true))
{}

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

std::ostream& operator<<(std::ostream& os, const FileSystem& fs)
{
	os << fs.getCurPath() << "> ";

	return os;
}
