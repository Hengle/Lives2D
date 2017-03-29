package com.teamtop.xgame;

public class GameNativeInterface {
	
	public static enum TOUCH_EVENT
	{
		TOUCH_DOWN,
		TOUCH_UP,
		TOUCH_MOVE
	};
	
	public static native int nativeOnCreate(int width,int height); //��Render��ʼ����ʱ���ʼ��C++ GLES
	
	public static native int nativeOnDraw();  

	public static native int nativeOnPause();
	
	public static native int nativeOnResume();
	
	public static native int nativeOnUpdate();
	
	public static native int nativeOnEvent(byte[] date); 
	
	public static native int nativeSetDataPath(String dataPath); //�����ļ��洢·��

	public static native int nativeOnTouch(float x,float y,int touchevent);//��Android��ĵ���¼�����C++��
}
