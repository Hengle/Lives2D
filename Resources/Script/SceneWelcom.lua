local ResourcesManager=require("ResourcesManager")

local SceneWelcom=class()

function SceneWelcom:ctor()
	print("SceneWelcom:ctor")
	self.mUIRoot=nil
	
	print(ResourcesManager:DataPath())
end

--��ʼ��
function SceneWelcom:Init()
	print("SceneWelcom:Init")
	local audioSource1 = AudioSource:new()
	audioSource1:LoadAudio(ResourcesManager:DataPath().. "/Resources/Audio/m_sound600.wav")
	audioSource1:Loop()
	audioSource1:Play()

	local audioSource2 = AudioSource:new()
	audioSource2:LoadAudio(ResourcesManager:DataPath() .. "/Resources/Audio/click.wav")
	
	self.mUIRoot=UIRoot:new()

	
	local	mImage_Bg =  Image:new()
	mImage_Bg:Init(ResourcesManager:DataPath() .. "/Resources/GUI/bbg_temple_circle.jpg");
	mImage_Bg:SetPosition(0, 0);
	mImage_Bg:SetDepth(0);
	self.mUIRoot:AddChild(mImage_Bg);

	local mUIButton = UIButton:new(ResourcesManager:DataPath() .. "/Resources/GUI/pop_button0.png", ResourcesManager:DataPath() .. "/Resources/GUI/pop_button1.png", 0, 200, 86, 48)
	mUIButton:SetOnClickListener(function(varTime)
		--print(varTime)

		audioSource2:Play()
	end,111)
	mUIButton:SetDepth(2);
	self.mUIRoot:AddChild(mUIButton);

	
end

--ˢ֡
function SceneWelcom:Update(varDeltaTime)
	--print("SceneWelcom:Update")
	self.mUIRoot:Update(varDeltaTime)
end

--����
function SceneWelcom:Draw()
	self.mUIRoot:Draw()
end

return SceneWelcom