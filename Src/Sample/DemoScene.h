#pragma once

#include"Image\Image.h"
#include"ImageAnimation\ImageAnimation.h"

//�̳�KeyTouchListener��������������¼�
#include"KeyTouch\KeyTouchListener.h"
#include"KeyTouch\KeyTouch.h"

class DemoScene:KeyTouchListener
{
private:
	//����һ��ͼƬ
	Image* mImage;

	//����һ��֡����
	ImageAnimation* mImageAnimation;

public:
	DemoScene():KeyTouchListener("DemoScene"),mImage(NULL), mImageAnimation(NULL)
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

		//ͼƬ��ʼ��
		mImage = new Image();
		mImage->Init("../../Resources/images/logo.png");

		//֡������ʼ��
		mImageAnimation = new ImageAnimation("../../Resources/ImageAnimations/Swordman/Saber/Animations.txt",4,1.0f/4);

		mImageAnimation->Play();
	}

	void Update(float varDeltaTime)
	{
		//Scale Test
		//mImage->SetScale(1.0f + varDeltaTime, 1.0f + varDeltaTime);

		mImageAnimation->Update(varDeltaTime);
	}

	void Draw()
	{
		//����һ��ͼƬ
		//mImage->Draw();

		mImageAnimation->Draw();
	}

private:
	virtual void OnKey(KeyCode varkeyCode)
	{
		switch (varkeyCode)
		{
		case Up:
			mImage->SetPosition(mImage->mPosX, mImage->mPosY + 1);
			break;
		case Down:
			mImage->SetPosition(mImage->mPosX, mImage->mPosY - 1);
			break;
		case Left:
			mImage->SetPosition(mImage->mPosX-1, mImage->mPosY);
			break;
		case Right:
			mImage->SetPosition(mImage->mPosX + 1, mImage->mPosY);
			break;
		case Esc:
			break;
		default:
			break;
		}
	}

	virtual void OnTouch(float varX, float varY)
	{

	}
};