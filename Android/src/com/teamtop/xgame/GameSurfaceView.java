package com.teamtop.xgame;

import com.teamtop.xgame.GameNativeInterface.TOUCH_EVENT;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class GameSurfaceView extends GLSurfaceView
{
	private GameRender m_Render;

	public GameSurfaceView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		
		//����GLES�汾Ϊ2
		setEGLContextClientVersion(2);
		
		//����Render
		m_Render=new GameRender();
		setRenderer(m_Render);
	}
	
	public void onPause()
	{
		//queueEvent() ��������Ⱦ�̺߳�UI�߳�֮��ͨ��
		queueEvent(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				GameNativeInterface.nativeOnPause();
			}
		});
		super.onPause();
	}
	
	public void onResume()
	{
		//queueEvent() ��������Ⱦ�̺߳�UI�߳�֮��ͨ��
		queueEvent(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				GameNativeInterface.nativeOnResume();
			}
		});
		super.onResume();
	}
	
	//��С����
	protected void onSizeChanged(int w,int h,int oldw,int oldh)
	{
		m_Render.setScreenWidthHeight(w, h);
	}
	
	
	public boolean onTouchEvent(final MotionEvent event)
	{
		queueEvent(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				//Log.i("cp", "GameSurfaceView onTouchEvent");
				int action=event.getAction();
				int touchCount=event.getPointerCount();
				if(touchCount==1)
				{
					switch (action) 
					{
						case MotionEvent.ACTION_DOWN:
							Log.i("cp", "GameSurfaceView TouchDown x="+event.getX(0)+" y= "+event.getY(0));
							GameNativeInterface.nativeOnTouch(event.getX(0), event.getY(0), (int)action);
							break;
	
						case MotionEvent.ACTION_UP:
							Log.i("cp", "GameSurfaceView onTouchUp x="+event.getX(0)+" y= "+event.getY(0));
							GameNativeInterface.nativeOnTouch(event.getX(0), event.getY(0), (int)action);
							break;
							
						case MotionEvent.ACTION_MOVE:
							Log.i("cp", "GameSurfaceView onTouchMove x="+event.getX(0)+" y= "+event.getY(0));
							GameNativeInterface.nativeOnTouch(event.getX(0), event.getY(0),(int)action);
							break;
							
						default:
							break;
					}
				}
			}
		});
		return true; //��ϣ�������ص������ٴδ�������True
	}
	
}