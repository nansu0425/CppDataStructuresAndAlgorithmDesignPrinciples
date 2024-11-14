#pragma once

#include <vector>
#include <string>
#include <iostream>



class FileSystem
{
private:
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

private:
	Str					getPath(Node* ptrDir) const;

private:
	Node*				m_ptrCurDir = nullptr;

};

std::ostream& operator<<(std::ostream& os, const FileSystem& fs);
