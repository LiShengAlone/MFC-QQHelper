#pragma once
class QQMessage
{
public:
	QQMessage();
	~QQMessage();


	//设计模式 单例模式
	static QQMessage*Instance()
	{
		static QQMessage object;
		return &object;
	}

	void Start(const wchar_t*msg);

private:
	//线程函数
	static unsigned int WINAPI RinThreadProc(void*param);
	//发送主函数
	void SendAll();

	//模拟按键的函数
	//TAB 回车 下键 ctrl v esc
	void Presskey(BYTE vkey);

	//发送函数
	void SendMsg();

	//把输入的文字报春到剪切板
	void CopyToClipBoard();
private:
	CString m_msg;
};

