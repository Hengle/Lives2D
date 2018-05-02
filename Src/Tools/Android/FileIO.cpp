#include "FileIO.h"


#ifdef ANDROID
AAssetManager* FileIO::sAAssetManager = nullptr;
#endif

FileIO::FileIO(void)
{
	AAsset* asset = AAssetManager_open(sAAssetManager, "", AASSET_MODE_UNKNOWN);
	if (asset == NULL)
	{
		LOGI(" %s", "asset==NULL");
		return;
	}

	/*��ȡ�ļ���С*/
	off_t bufferSize = AAsset_getLength(asset);
	LOGI("file size : %d\n", bufferSize);
	char *buffer = (char *)malloc(bufferSize + 1);
	buffer[bufferSize] = 0;

	int numBytesRead = AAsset_read(asset, buffer, bufferSize);
	LOGI(": %s", buffer);
	free(buffer);
	/*�ر��ļ�*/
	AAsset_close(asset);
}


FileIO::~FileIO(void)
{
}
