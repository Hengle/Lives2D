package com.teamtop.xgame;

import java.io.File;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.teamtop.util.GameGlobalVal;

import android.opengl.GLSurfaceView.Renderer;
import android.os.Environment;

public class GameRender implements Renderer {

	private int m_Width;
	private int m_Height;
	
	private long m_begin=0;
	private long m_end=0;
	

	@Override
	public void onDrawFrame(GL10 arg0) {
		// TODO Auto-generated method stub
		
		//ͨ����ͣ������֡��
		m_end=System.currentTimeMillis(); //һ֡����
		long time=m_end-m_begin;	//������Ⱦ��һ֡��ʱ��
		long frame_time=33;   //����ÿһ֡�ļ��ʱ��
		if(time<frame_time) //�����Ⱦ��һ֡��ʱ��û��33ms,����ͣ33-��Ⱦһ֡��ʱ��
		{
			try {
				Thread.sleep(frame_time-time);
			} catch (InterruptedException e) {
				// TODO: handle exception
				e.printStackTrace();
			}
		}
		
		m_begin=System.currentTimeMillis(); //һ֡��ʼ
	
		GameNativeInterface.nativeOnUpdate();
		GameNativeInterface.nativeOnDraw(); //Android���ˢ֡��ִ��C++���ˢ֡
		
	}

	//��������൱��Glut�е�resharp,���Ǹı䴰�ڴ�С�Ļص�
	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		// TODO Auto-generated method stub
	}

	//�൱��GLut�е�Init
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		// TODO Auto-generated method stub
		
		String sdcardPathString=Environment.getExternalStorageDirectory().getPath(); //��ȡ�洢����ַ
		GameNativeInterface.nativeSetDataPath(sdcardPathString+ File.separator+GameGlobalVal.SavePath); //������Ϸ��Դ�洢·��
		
		GameNativeInterface.nativeOnCreate(m_Width, m_Height);
	}
	
	//������Ⱦ�ӿڴ�С
	public void setScreenWidthHeight(int width,int height)
	{
		m_Width=width;
		m_Height=height;
	}

}
