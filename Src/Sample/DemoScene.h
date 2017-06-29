#pragma once

#include"GUI\UIRoot.h"

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

	//һ������
	UIRoot* mUIRoot;

public:
	DemoScene():KeyTouchListener("DemoScene"), mImageAnimation(nullptr),mUIButton(nullptr), mImage_Hanhua(nullptr), mImage_Sweep(nullptr), mUIRoot(nullptr)
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

		//UIRoot
		mUIRoot = new UIRoot();

		//֡������ʼ��
		mImageAnimation = new ImageAnimation("../../Resources/ImageAnimations/Swordman/Saber/Animations.txt",1.0f/4);

		mImageAnimation->Play("Idle");

		mUIRoot->AddChild(mImageAnimation);


		//��ť��ʼ��
		mUIButton = new UIButton("../../Resources/GUI/pop_button0.png", "../../Resources/GUI/pop_button1.png", 0, 100, 86, 48, [=]()
		{
			Helper::LOG("Click Button");
			mImageAnimation->Play("Walk");
		});
		mUIButton->SetDepth(-1); //DepthԽС��λ���ϲ�
		mUIRoot->AddChild(mUIButton);
		

		//ͼƬ��ʼ��
		mImage_Sweep = new Image();
		mImage_Sweep->Init("../../Resources/GUI/sweep.png");
		mImage_Sweep->SetPosition(100, 70);
		mUIRoot->AddChild(mImage_Sweep);

		mImage_Hanhua = new Image();
		mImage_Hanhua->Init("../../Resources/GUI/hanhua.png");
		mImage_Hanhua->SetPosition(100, 100);
		mUIRoot->AddChild(mImage_Hanhua);
		
	}

	void Update(float varDeltaTime)
	{
		mUIRoot->Update(varDeltaTime);
	}

	void Draw()
	{
		
		mUIRoot->Draw();
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

	void OnTouch(int varX, int varY) override
	{

	}

	void OnTouchRelease(int varX, int varY) override
	{

	}
};