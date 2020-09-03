#include <iostream>
#include <afxsock.h>
#include "stdafx.h"

using namespace std;

class CChessBorad :public CSocket {
public:
	void AcceptConnection();//用于客户端的连接
};