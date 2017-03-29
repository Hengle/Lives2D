package com.teamtop.xgame;

import android.os.Bundle;
import android.app.Activity;

public class GameActivity extends Activity {
	
	private GameSurfaceView m_gameSurfaceView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		//��Activity��View����ΪGLSurfaceView������ָ��RendererΪGameRender������ˢ֡��Ⱦ��ʱ����õ��������Լ���GameRender��Ȼ����GameRenderÿһִ֡��onDrawFrame��ʱ�����C++��nativeDraw
		m_gameSurfaceView=new GameSurfaceView(this);
		setContentView(m_gameSurfaceView);
	}

	
	//������Ϸso(C++�������)
	static 
	{
		System.loadLibrary("xGame");
	}

}
