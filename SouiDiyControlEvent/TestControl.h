/*******************************************************************   
 *  文件名称: TestControl.h
 *  简要描述: 测试控件类，主要用来测试自定义事件功能
 *   
 *  创建日期: 2017-9-12
 *  作　　者: 王莹
 *  说　　明: 
 *   
 *  修改日期: 
 *  作　　者: 
 *  说　　明: 
 ******************************************************************/  
#pragma once

namespace SOUI
{
// 自定义事件消息
#define EVT_TEST_CONTROL (SOUI::EVT_EXTERNAL_BEGIN + 400)

class EventTestControl : public TplEventArgs<EventTestControl>
{
	SOUI_CLASS_NAME(EventTestControl, L"on_test_constrol")
public:
	EventTestControl(SOUI::SWindow* pSender) : TplEventArgs<EventTestControl>(pSender)
	{

	}
	enum { EventID = EVT_TEST_CONTROL };

	INT nIndex;
};
	
// 自定义测试控件
class STestControl : public SWindow
{
	SOUI_CLASS_NAME(STestControl, L"testcontrol")
public:
	STestControl();
	virtual ~STestControl();

protected:
	// 创建控件：初始化 xml，绑定事件等等
	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// 处理控件 xml 属性
	SOUI_ATTRS_BEGIN()
	SOUI_ATTRS_END()

	// 响应控件窗口消息
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_CREATE(OnCreate)
	SOUI_MSG_MAP_END()

private:
	// 按钮点击响应
	bool OnBtnClick(SOUI::EventArgs* pEvt);
};

}