#include "stdafx.h"
#include "QQMessage.h"
#define Time 100


QQMessage::QQMessage()
{
}


QQMessage::~QQMessage()
{
}


void QQMessage::Start(const wchar_t*msg) //��ʼ����
{
	m_msg = CString(msg);
	_beginthreadex(NULL, 0, QQMessage::RinThreadProc, NULL, 0, NULL);
}

//�̺߳���
unsigned int QQMessage::RinThreadProc(void*param)
{
	//��������
	QQMessage::Instance()->SendAll();
	return 0;
 }
//����������
void QQMessage::SendAll()
{
	//����
	//1.�������ֵ����а�
	CopyToClipBoard();//��û�ж���
	//QQMessage::CopyToClipBoard();
	int errorTimes = 0;//����Ĵ���
	while (errorTimes<=4)
	{
		//TXGuiFoundation  QQ   �����   ������
		HWND qqHwnd = FindWindow(L"TXGuiFoundation", L"QQ");  //find window
															  //�ж�QQ�����ǲ�����ǰ
		HWND frontHwnd = GetForegroundWindow();//��ȡ��ǰ�Ĵ���
		if (qqHwnd != frontHwnd)
		{
			if (!SetForegroundWindow(qqHwnd))//������ǰ�Ĵ���
			{
				MessageBox(NULL, L"���ȣ����QQ�أ�", NULL, NULL);
				break;
			}
		}
		if (errorTimes == 0) {
			Presskey(VK_TAB);
			Presskey(VK_TAB);
		}
		Presskey(VK_DOWN);
		Presskey(VK_RETURN);

		HWND curFrontHwnd=GetForegroundWindow();//��ô��ȡ����ǰ�Ĵ���?
		if (curFrontHwnd == qqHwnd)
		{
			errorTimes++;
			continue;
		}
		errorTimes = 0;
		QQMessage::SendMsg();
	}
}

//ģ�ⰴ���ĺ���
//TAB �س� �¼� ctrl v esc
void QQMessage::Presskey(BYTE vkey)
{
	keybd_event(vkey, 0, 0, 0);
	Sleep(Time);
	keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);
	Sleep(Time);
}

//���ͺ���
void QQMessage::SendMsg()
{
	keybd_event(VK_CONTROL, 0, 0, 0);
	Sleep(Time);
	keybd_event(0x56, 0, 0, 0);//����V
	Sleep(Time);
	
	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);//����V
	Sleep(Time);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(Time);
	Presskey(VK_RETURN);
	Presskey(VK_ESCAPE);
}

//����������ֱ��������а�
//����ͣ�����   д��һģһ��   ����
void QQMessage::CopyToClipBoard()
{
	//ȫ���ڴ�Ŀ���
	//int a ջ
	//malloc ���ڴ�  ��������
	int memLen = m_msg.GetLength() * sizeof(wchar_t) + 2;//����
	HANDLE hGlobalmem = GlobalAlloc(GHND,memLen);
	void *memAddr = GlobalLock(hGlobalmem);//��ַ
	ZeroMemory(memAddr, memLen);//��memAddr  ��ʼ��memLen
	memcpy(memAddr, (const void*)m_msg.GetBuffer(), memLen);

	//memAddr   memLen���������������

	//2.���а�Ĳ���
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hGlobalmem);
	CloseClipboard();


}
/*
keybd_event(VK_CONTROL, 0, 0, 0);
Sleep(Time);
keybd_event(0x55, 0, 0, 0);//����C
Sleep(Time);

keybd_event(0x55, 0, KEYEVENTF_KEYUP, 0);//����C
Sleep(Time);
keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
Sleep(Time);
*/