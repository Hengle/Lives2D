#pragma once

#include"GUI\UIRoot.h"

#include"Image\Image.h"
#include"ImageAnimation\ImageAnimation.h"

//�̳�KeyTouchListener��������������¼�
#include"KeyTouch\KeyTouchListener.h"
#include"KeyTouch\KeyTouch.h"

#include"GUI\UIButton.h"

#include"../Tools/Helper.h"

#include"./Audio/AudioSource.h"

class DemoScene:KeyTouchListener
{
private:
	//����һ��֡����
	ImageAnimation* mImageAnimation_Angel;

	//����һ����ť
	UIButton* mUIButton;

	//����һ��ͼƬ
	Image* mImage_Hanhua;
	Image* mImage_Sweep;
	Image* mImage_Bg;

	//һ������
	UIRoot* mUIRoot;

public:
	DemoScene():KeyTouchListener("DemoScene"), mImageAnimation_Angel(nullptr),mUIButton(nullptr), mImage_Hanhua(nullptr), mImage_Sweep(nullptr), mImage_Bg(nullptr), mUIRoot(nullptr)
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

		mImage_Bg = new Image();
		mImage_Bg->Init("../../Resources/GUI/bbg_temple_circle.jpg");
		mImage_Bg->SetPosition(0, 0);
		mImage_Bg->SetDepth(9999);
		mUIRoot->AddChild(mImage_Bg);
		

		//֡������ʼ��
		mImageAnimation_Angel = new ImageAnimation("../../Resources/ImageAnimations/Angel/Animations.txt",1.0f/5);

		mImageAnimation_Angel->SetPosition(0, 200);
		mImageAnimation_Angel->SetScale(0.6, 0.6);
		mImageAnimation_Angel->Play("Idle");

		mUIRoot->AddChild(mImageAnimation_Angel);


		////��ť��ʼ��
		//mUIButton = new UIButton("../../Resources/GUI/pop_button0.png", "../../Resources/GUI/pop_button1.png", 0, 200, 86, 48, [=]()
		//{
		//	Helper::LOG("Click Button");
		//	mImageAnimation_Angel->Play("Talk");
		//});
		//mUIButton->SetDepth(-1); //DepthԽС��λ���ϲ�
		//mUIRoot->AddChild(mUIButton);
		//

		////ͼƬ��ʼ��
		//mImage_Sweep = new Image();
		//mImage_Sweep->Init("../../Resources/GUI/sweep.png");
		//mImage_Sweep->SetPosition(100, 70);
		//mUIRoot->AddChild(mImage_Sweep);

		//mImage_Hanhua = new Image();
		//mImage_Hanhua->Init("../../Resources/GUI/hanhua.png");
		//mImage_Hanhua->SetPosition(100, 100);
		//mUIRoot->AddChild(mImage_Hanhua);
		

		AudioSource* audioSource = new AudioSource();
		audioSource->LoadAudio("../../Resources/Audio/m_sound600.wav");
		audioSource->Loop();
		audioSource->Play();

		//AudioSource* audioSource1 = new AudioSource();
		//audioSource1->LoadAudio("../../Resources/Audio/file2.au");
		//audioSource1->Loop();
		//audioSource1->Play();
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
			mImageAnimation_Angel->Play("Walk");
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