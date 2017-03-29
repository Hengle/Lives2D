//����Shader
static const char g_VertexShaderNormal[]=
"attribute vec4 vPosition;\n" //��������
"attribute vec2 textureCoords;\n" //��������
"varying vec2 frag_textureCoords;\n" //�������괫��ƬԪ��ɫ��
"void main(){\n"
"frag_textureCoords=textureCoords;\n" //�Ѵ����д��������������괫��ƬԪ��ɫ����
"	gl_Position=vPosition;\n"
"}\n";



//ƬԪ��ɫ��
static const char g_FragmentShaderNormal[]=
                        "varying vec2 frag_textureCoords;                            \n"
                        "uniform sampler2D s_texture;                        \n"
                        "void main()                                         \n"
                        "{                                                   \n"
                        "  gl_FragColor = texture2D( s_texture, frag_textureCoords );\n"
                        "}\n";
