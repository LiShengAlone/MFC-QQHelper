#pragma once
class QQMessage
{
public:
	QQMessage();
	~QQMessage();


	//���ģʽ ����ģʽ
	static QQMessage*Instance()
	{
		static QQMessage object;
		return &object;
	}

	void Start(const wchar_t*msg);

private:
	//�̺߳���
	static unsigned int WINAPI RinThreadProc(void*param);
	//����������
	void SendAll();

	//ģ�ⰴ���ĺ���
	//TAB �س� �¼� ctrl v esc
	void Presskey(BYTE vkey);

	//���ͺ���
	void SendMsg();

	//����������ֱ��������а�
	void CopyToClipBoard();
private:
	CString m_msg;
};

