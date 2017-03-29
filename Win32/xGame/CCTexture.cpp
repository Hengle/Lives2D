#include "CCTexture.h"


using namespace std;

#ifdef WIN32
#pragma comment(lib,"libpng16.lib")
#endif

CCTexture::CCTexture(void)
{
}

///��Png�ļ�����Texture
GLuint CCTexture::CreateTextureFromPng(const char* filename)
{
	unsigned char header[8]; //ͷ����Ϣ
	int k; //ѭ��
	GLuint textureID; //��������
	int width,height;
	png_byte color_type; //ͼƬ����
	png_byte bit_depth; //�ֽ����
	png_structp png_ptr; //ͼƬ
	png_infop info_ptr; //ͼƬ��Ϣ
	int number_of_passes; //����ɨ��
	png_bytep *row_pointers; //ͼƬ��������
	int row,col,pos; //���ڸı�png�������е�����
	GLubyte *rgba;
	FILE *fp=fopen(filename,"rb"); //ֻ����pngͼƬ
	if(!fp) //��ȡʧ��
	{
		//fclose(fp);
		return 0;
	}
	//LOGI("CreateTextureFromPng 22 \n");
	fread(header,1,8,fp); //��ȡ8���ֽ�
	//LOGI("CreateTextureFromPng 23 \n");
	if(png_sig_cmp(header,0,8)) //����pngͼƬ
	{
		//LOGI("CreateTextureFromPng 24 \n");
		fclose(fp);
		return 0;
	}
	//��ʼ��png_structp png_infop
	//LOGI("CreateTextureFromPng 3 \n");
	png_ptr=png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL); //�������������ô���ص�
	if(!png_ptr)  //��ʼ��ʧ��
	{
		fclose(fp);
		return 0;
	}

	//���ݳ�ʼ����png_ptr��ʼ��png_info
	info_ptr=png_create_info_struct(png_ptr);
	if(!info_ptr)
	{
		png_destroy_read_struct(&png_ptr,(png_infopp)NULL,(png_infopp)NULL);
		fclose(fp);
		return 0;
	}
	//LOGI("CreateTextureFromPng 4 \n");
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		//�ͷ��ڴ棬�ر��ļ�������һ����ͼID���˴�Ӧ����һ������Ĭ����ͼ����ID�ĺ���
		png_destroy_read_struct(&png_ptr,(png_infopp)NULL,(png_infopp)NULL);
		fclose(fp);
		return 0;
	}

	//ͨ��2���ƴ��ļ���ͨ��i/o���ƺ���png_init_io
	png_init_io(png_ptr,fp);

	png_set_sig_bytes(png_ptr,8); //png��־ͷ ����

	png_read_info(png_ptr,info_ptr); //ʵ�ʶ�ȡͼƬ��Ϣ

	width=png_get_image_width(png_ptr,info_ptr); //��ȡͼƬ���

	height=png_get_image_height(png_ptr,info_ptr); //��ȡͼƬ�߶�

	color_type=png_get_color_type(png_ptr,info_ptr); //��ȡͼƬ�ֽ���� λ���http://t.cn/8suqDV1

	//���ͼƬ����alphaͨ��
	//if(color_type==PNG_COLOR_TYPE_RGBA)
	//{
	//	png_set_swap_alpha(png_ptr);
	//}
	//LOGI("CreateTextureFromPng 5 \n");
	bit_depth=png_get_bit_depth(png_ptr,info_ptr);

	number_of_passes=png_set_interlace_handling(png_ptr); //����ɨ��;

	png_read_update_info(png_ptr,info_ptr); //����ȡ������Ϣ���µ�info_ptr;

	if(setjmp(png_jmpbuf(png_ptr))) //���ļ�
	{
		fclose(fp);
		return 0;
	}

	rgba=(GLubyte*)malloc(width * height *4);

	//ʹ�ö�̬���� ���ó���
	row_pointers=(png_bytep*) malloc (sizeof(png_bytep)*height);
	//LOGI("CreateTextureFromPng 6 \n");
	for (k = 0; k < height; k++)
	{
		row_pointers[k]=NULL;
	}

	//ͨ��ɨ���������ÿһ�н��õ������ݸ�ֵ����̬����
	for(k=0;k<height;k++)
	{
		row_pointers[k]=(png_bytep)png_malloc(png_ptr,png_get_rowbytes(png_ptr,info_ptr));
	}
	//LOGI("CreateTextureFromPng 7 \n");
	//Png�Ǵ����� �Ӷ�����  ����ͼ��Ҫ�������� ������ �ӵ׵��� ����������Ҫ��������
	png_read_image(png_ptr,row_pointers);
	pos=(width*height*4)-(4*width);
	for (row = 0; row < height; row++)
	{
		for (col= 0; col< (4*width); col+=4)
		{
			rgba[pos++]=row_pointers[row][col]; //red
			rgba[pos++]=row_pointers[row][col+1]; //green
			rgba[pos++]=row_pointers[row][col+2]; //blue
			rgba[pos++]=row_pointers[row][col+3]; //alpha
		}
		pos=(pos-(width*4)*2);
	}
	//LOGI("CreateTextureFromPng 8 \n");
	//����������ͼ OpenGL ES2.0 ����Ҫ�������˻ᱨ�� invalid_enum
	//glEnable(GL_TEXTURE_2D);
	//LOGI("CreateTextureFromPng 81 \n");

	//��������
	glGenTextures(1,&textureID);
	//LOGI("CreateTextureFromPng 82 \n");
	Helper::CheckGLError("glGenTextures");
	//������
	glBindTexture(GL_TEXTURE_2D,textureID);
	//LOGI("CreateTextureFromPng 83 \n");
	Helper::CheckGLError("glBindTexture");

	 //������ͼ������Ļ��Ч��������Ĭ��ֻ������
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	//�����������õ�ͼƬ����
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,rgba);
	//LOGI("CreateTextureFromPng 84 \n");
	Helper::CheckGLError("glTexImage2D");

	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Helper::CheckGLError("glTexParameteri");
	//LOGI("CreateTextureFromPng 9 \n");
	free(row_pointers);
	fclose(fp);
	return textureID;
}


CCTexture::~CCTexture(void)
{
}
