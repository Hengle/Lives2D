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

	glm::vec3* GetVertexPositionAnim();

	void ApplySkin();

	const bool& GetApplyedSkin();

	Vertex* GetVertexArray();

	const int& GetVertexCount();

	void SetVertexIndicesSize(int varVertexIndicesSize);

#ifdef MINI_MESH
	void PushVertexIndicesArray(unsigned short * varVertexIndices);
#else
	void PushVertexIndicesArray(int * varVertexIndices);
#endif

	const int& GetVertexIndicesSize();
	

#ifdef MINI_MESH
	unsigned short* GetVertexIndices();
#else
	int* GetVertexIndices();
#endif

private:
	int mVertexCount;
	Vertex* mVertexArray;

	glm::vec3* mVertexPositionAnim;

	int mVertexIndicesSize;
	
#ifdef MINI_MESH
	unsigned short* mVertexIndices;
#else
	int* mVertexIndices;
#endif

	bool mApplyedSkin;
};

