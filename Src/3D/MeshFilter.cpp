#include "MeshFilter.h"
#include<fstream>
#include<iostream>
#include"Texture.h"
#include"Tools/Application.h"

IMPLEMENT_DYNCRT_ACTION(MeshFilter)

MeshFilter::MeshFilter():mMesh(nullptr)
{
}


MeshFilter::~MeshFilter()
{
}

void MeshFilter::InitWithXml(TiXmlElement * varTiXmlElement)
{
	const char* tmpMeshFilePath = varTiXmlElement->Attribute("Mesh");
	LoadMesh(Application::GetFullPath(tmpMeshFilePath));
}

Mesh * MeshFilter::GetMesh()
{
	return mMesh;
}

const std::vector<unsigned short>& MeshFilter::GetVertexIndexInMaterial(int varMaterialIndex)
{
	// TODO: �ڴ˴����� return ���
	return mVertexIndexInMaterial[varMaterialIndex];
}

void MeshFilter::LoadMesh(const char * varMeshPath)
{
	std::ifstream tmpStream(varMeshPath, std::ios::binary);

	//��ȡmeshcount;
	int tmpMeshCount = 0;
	tmpStream.read((char*)(&tmpMeshCount), sizeof(int));

	for (int tmpMeshIndex = 0; tmpMeshIndex < tmpMeshCount; tmpMeshIndex++)
	{
		Mesh* tmpMesh=new Mesh();

		//��ȡVertexMemSize;
		int tmpVertexMemSize = 0;
		tmpStream.read((char*)(&tmpVertexMemSize), sizeof(int));
		
		//����VertexCount;
		int tmpVertexCount = tmpVertexMemSize / sizeof(Vertex);

		tmpMesh->SetVertexCount(tmpVertexCount);

		//��ȡVertex����;
		Vertex* tmpVertexArray = (Vertex*)malloc(tmpVertexMemSize);
		tmpStream.read((char*)tmpVertexArray, tmpVertexMemSize);
		tmpMesh->PushVertexArray(tmpVertexArray);

		//��ȡIndicesMemSize;
		int tmpIndicesMemSize = 0;
		tmpStream.read((char*)(&tmpIndicesMemSize), sizeof(int));

		//����IndexCount;
		int tmpIndexCount = tmpIndicesMemSize / sizeof(unsigned short);
		tmpMesh->SetVertexIndicesSize(tmpIndexCount);

		//��ȡindex����;
		unsigned short* tmpVertexIndices = (unsigned short*)malloc(tmpIndicesMemSize);
		tmpStream.read((char*)tmpVertexIndices, tmpIndicesMemSize);
		tmpMesh->PushVertexIndicesArray(tmpVertexIndices);

		//��ȡTextureMemSize;
		int tmpTextureMemSize = 0;
		tmpStream.read((char*)(&tmpTextureMemSize), sizeof(int));

		//���� TextureCount;
		int tmpTextureCount = tmpTextureMemSize / sizeof(Texture);

		//��ȡTexture����;
		for (int tmpTextureIndex = 0; tmpTextureIndex < tmpTextureCount; tmpTextureIndex++)
		{
			Texture tmpTexture;
			tmpStream.read((char*)(&tmpTexture), sizeof(Texture));
		}


		//��ȡ��������
		int tmpMaterialSize = 0;
		tmpStream.read((char*)(&tmpMaterialSize), sizeof(tmpMaterialSize));

		mVertexIndexInMaterial.resize(tmpMaterialSize);

		for (size_t i = 0; i < tmpMaterialSize; i++)
		{
			//��ȡ���������� �����Ķ���
			int tmpVertexSizeInMaterial;
			tmpStream.read((char*)(&tmpVertexSizeInMaterial), sizeof(tmpVertexSizeInMaterial));

			std::vector<unsigned short> tmpVertexIndexInOneMaterial(tmpVertexSizeInMaterial);

			for (size_t tmpVectorIndex = 0; tmpVectorIndex < tmpVertexSizeInMaterial; tmpVectorIndex++)
			{
				int tmpVertexIndex = 0;
				tmpStream.read((char*)(&tmpVertexIndex), sizeof(tmpVertexIndex));

				tmpVertexIndexInOneMaterial[tmpVectorIndex] = tmpVertexIndex;
			}

			mVertexIndexInMaterial[i] = tmpVertexIndexInOneMaterial;
		}

		mMesh = tmpMesh;
	}

	tmpStream.close();
}
