#pragma once

#include <vector>
#include <string>
#include <iostream>

class FileSystem
{
public:
	struct Node;

	using				Str = std::string;
	using				VecPtrNode = std::vector<Node*>;

	struct Node
	{
		Str				name;
		Node*			ptrParent;
		VecPtrNode		ptrsChild;
		bool			isDir = false;

						Node(Str name, Node* ptrParent, bool isDir);
	};

public:
						FileSystem();

	Str					getCurPath() const;
	bool				isPath(const std::string& path);
	void				insert(const std::string& name, const std::string& path, bool isDir);
	void				printListPath(const std::string& path);
	void				moveCurDir(const std::string& path);

private:
	Str					getPath(Node* ptrDir) const;
	Node*				searchPath(Node* ptrCur, int idxNameFirst, int lenPath, const std::string& path);
	void				printListDir(Node* ptrDir);

private:
	Node*				m_ptrRootDir = nullptr;
	Node*				m_ptrCurDir = nullptr;

};

std::ostream& operator<<(std::ostream& os, const FileSystem& fs);
