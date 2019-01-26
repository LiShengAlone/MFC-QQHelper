#include "stdafx.h"
#include "QQMessage.h"
#define Time 100


QQMessage::QQMessage()
{
}


QQMessage::~QQMessage()
{
}


void QQMessage::Start(const wchar_t*msg) //开始函数
{
	m_msg = CString(msg);
	_beginthreadex(NULL, 0, QQMessage::RinThreadProc, NULL, 0, NULL);
}

//线程函数
unsigned int QQMessage::RinThreadProc(void*param)
{
	//发送流程
	QQMessage::Instance()->SendAll();
	return 0;
 }
//发送主函数
void QQMessage::SendAll()
{
	//流程
	//1.复制文字到剪切板
	CopyToClipBoard();//还没有定义
	//QQMessage::CopyToClipBoard();
	int errorTimes = 0;//错误的次数
	while (errorTimes<=4)
	{
		//TXGuiFoundation  QQ   不会变   句柄会变
		HWND qqHwnd = FindWindow(L"TXGuiFoundation", L"QQ");  //find window
															  //判断QQ窗口是不是最前
		HWND frontHwnd = GetForegroundWindow();//获取最前的窗口
		if (qqHwnd != frontHwnd)
		{
			if (!SetForegroundWindow(qqHwnd))//设置最前的窗口
			{
				MessageBox(NULL, L"逗比！你的QQ呢？", NULL, NULL);
				break;
			}
		}
		if (errorTimes == 0) {
			Presskey(VK_TAB);
			Presskey(VK_TAB);
		}
		Presskey(VK_DOWN);
		Presskey(VK_RETURN);

		HWND curFrontHwnd=GetForegroundWindow();//怎么获取到最前的窗口?
		if (curFrontHwnd == qqHwnd)
		{
			errorTimes++;
			continue;
		}
		errorTimes = 0;
		QQMessage::SendMsg();
	}
}

//模拟按键的函数
//TAB 回车 下键 ctrl v esc
void QQMessage::Presskey(BYTE vkey)
{
	keybd_event(vkey, 0, 0, 0);
	Sleep(Time);
	keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);
	Sleep(Time);
}

//发送函数
void QQMessage::SendMsg()
{
	keybd_event(VK_CONTROL, 0, 0, 0);
	Sleep(Time);
	keybd_event(0x56, 0, 0, 0);//按下V
	Sleep(Time);
	
	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);//弹起V
	Sleep(Time);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(Time);
	Presskey(VK_RETURN);
	Presskey(VK_ESCAPE);
}

//把输入的文字报春到剪切板
//万金油！！！   写法一模一样   面试
void QQMessage::CopyToClipBoard()
{
	//全局内存的拷贝
	//int a 栈
	//malloc 堆内存  输入文字
	int memLen = m_msg.GetLength() * sizeof(wchar_t) + 2;//长度
	HANDLE hGlobalmem = GlobalAlloc(GHND,memLen);
	void *memAddr = GlobalLock(hGlobalmem);//地址
	ZeroMemory(memAddr, memLen);//从memAddr  初始化memLen
	memcpy(memAddr, (const void*)m_msg.GetBuffer(), memLen);

	//memAddr   memLen保存了输入的文字

	//2.剪切板的操作
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hGlobalmem);
	CloseClipboard();


}
/*
keybd_event(VK_CONTROL, 0, 0, 0);
Sleep(Time);
keybd_event(0x55, 0, 0, 0);//按下C
Sleep(Time);

keybd_event(0x55, 0, KEYEVENTF_KEYUP, 0);//弹起C
Sleep(Time);
keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
Sleep(Time);
*/