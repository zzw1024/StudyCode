#include "stdafx.h"
#include <afxwin.h>
#include <afxsock.h>
#include <iostream>


using namespace std;


class CSrvSock :public CSocket 
{
public:
	
	void OnAccept(int);//���ڽ��տͻ�������
};


