attribute vec4 vPosition; //��������
attribute vec2 textureCoords; //��������
varying vec2 frag_textureCoords; //�������괫��ƬԪ��ɫ��

void main()
{
	frag_textureCoords=textureCoords; //�Ѵ����д��������������괫��ƬԪ��ɫ����
	gl_Position=vPosition;
}