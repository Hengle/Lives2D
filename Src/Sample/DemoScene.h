#pragma once

#include"Image\Image.h"
#include"ImageAnimation\ImageAnimation.h"

//�̳�KeyTouchListener��������������¼�
#include"KeyTouch\KeyTouchListener.h"
#include"KeyTouch\KeyTouch.h"

#include"GUI\UIButton.h"

#include"../Tools/Helper.h"

class DemoScene:KeyTouchListener
{
private:
	//����һ��֡����
	ImageAnimation* mImageAnimation;

	//����һ����ť
	UIButton* mUIButton;

	//����һ��ͼƬ
	Image* mImage_Hanhua;
	Image* mImage_Sweep;

public:
	DemoScene():KeyTouchListener("DemoScene"), mImageAnimation(NULL),mUIButton(NULL), mImage_Hanhua(NULL), mImage_Sweep(NULL)
	{

	}

	~DemoScene()
	{
		KeyTouch::UnRegisterKeyTouchListener(this);
	}

public:
	void Init()
	{
		//ע����������Ļ����
		KeyTouch::RegisterKeyTouchListener(this);

		//֡������ʼ��
		mImageAnimation = new ImageAnimation("../../Resources/ImageAnimations/Swordman/Saber/Animations.txt",1.0f/4);

		mImageAnimation->Play("Idle");

		//��ť��ʼ��
		mUIButton = new UIButton("../../Resources/GUI/pop_button0.png", "../../Resources/GUI/pop_button1.png", 0, 100, 86, 48, [=]()
		{
			Helper::LOG("Click Button");
			mImageAnimation->Play("Walk");
		});

		//ͼƬ��ʼ��
		mImage_Hanhua = new Image();
		mImage_Hanhua->Init("../../Resources/GUI/hanhua.png");
		mImage_Hanhua->SetPosition(100, 100);

		mImage_Sweep = new Image();
		mImage_Sweep->Init("../../Resources/GUI/sweep.png");
		mImage_Sweep->SetPosition(100, 100);
	}

	void Update(float varDeltaTime)
	{
		mImageAnimation->Update(varDeltaTime);

		mUIButton->Update(varDeltaTime);

		
	}

	void Draw()
	{
		mImageAnimation->Draw();

		mUIButton->Draw();

		mImage_Hanhua->Draw();

		mImage_Sweep->Draw();
	}

private:
	void OnKey(KeyCode varkeyCode) override
	{
		switch (varkeyCode)
		{
		case Right:
			mImageAnimation->Play("Walk");
			break;
		case Esc:
			break;
		default:
			break;
		}
	}

	void OnTouch(float varX, float varY) override
	{

	}

	void OnTouchRelease(float varX, float varY) override
	{

	}
};