#pragma once
#include "Component/Object.h"
#include "Vertex.h"

class Mesh :
	public Object
{
public:
	Mesh();
	~Mesh();

	void SetVertexCount(int varVertexCount);//���ö�������ͬʱ�����ڴ�

	void PushVertexArray(Vertex* varVertex);//���붥������

	Vertex* GetVertexArray();

	void SetVertexIndicesSize(int varVertexIndicesSize);

	void PushVertexIndicesArray(unsigned short* varVertexIndices);

	int GetVertexIndicesSize();
	unsigned short* GetVertexIndices();

private:
	int mVertexCount;
	Vertex* mVertexArray;

	int mVertexIndicesSize;
	unsigned short* mVertexIndices;
};

