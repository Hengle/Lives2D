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

	void PushVertexIndicesArray(int* varVertexIndices);

	int GetVertexIndicesSize();
	int* GetVertexIndices();

private:
	int mVertexCount;
	Vertex* mVertexArray;

	int mVertexIndicesSize;
	int* mVertexIndices;
};

