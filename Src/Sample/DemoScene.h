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
		std::string tmpImageArray[] = { 
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/29.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/28.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/27.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/26.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/25.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/24.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/23.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/22.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/21.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/20.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/19.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/18.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/17.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/16.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/15.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/14.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/13.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/12.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/11.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/10.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/9.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/8.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/7.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/6.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/5.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/4.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/3.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/2.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/1.png",
			"../../Resources/ImageAnimations/mage_overmind/sprite_character_mage_effect_cutin/mage_overmind.img/0.png"
		};
		mImageAnimation = new ImageAnimation(tmpImageArray,30,1.0f/10);

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