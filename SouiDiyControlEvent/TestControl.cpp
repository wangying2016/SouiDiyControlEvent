#include "stdafx.h"
#include "TestControl.h"

namespace SOUI
{

STestControl::STestControl()
{
	m_evtSet.addEvent(EVENTID(EventTestControl));
}

STestControl::~STestControl()
{

}

// 创建控件：初始化 xml，绑定事件等等
int STestControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	pugi::xml_document xmlDoc;
	SOUI::SStringW strXml = L"test_control";

	if (!LOADXML(xmlDoc, strXml, L"LAYOUT")) {
		return E_FAIL;
	}
	pugi::xml_node itemXmlNode = xmlDoc.child(L"testcontrol");
	if (!itemXmlNode) {
		return E_FAIL;
	}
	this->CreateChildren(itemXmlNode);

	// 绑定两个按钮被点击事件
	for (UINT i = 0; i < 2; ++i) {
		SOUI::SStringW strXmlName;
		strXmlName.Format(L"btn_%d", i + 1);
		SOUI::SButton* pButton =
			FindChildByName2<SOUI::SButton>(strXmlName);
		assert(pButton != NULL);
		pButton->GetEventSet()->subscribeEvent(SOUI::EVT_CMD,
			Subscriber(&STestControl::OnBtnClick, this));
	}
	return 0;
}

// 按钮点击响应
bool STestControl::OnBtnClick(SOUI::EventArgs* pEvt)
{
	// 获取按钮名称，获取后缀数字
	SOUI::SWindow* pButton =
		SOUI::sobj_cast<SOUI::SWindow>(pEvt->sender);
	assert(pButton != NULL);
	SOUI::SStringW strName = pButton->GetName();
	SOUI::SStringW strIndex = strName.Right(1);
	INT nIndex = _wtoi(strIndex);

	// 发送全局的自定义消息
	EventTestControl evt(this);
	evt.nIndex = nIndex;
	FireEvent(evt);	// 激活事件 Fire!!!
	return true;
}

}