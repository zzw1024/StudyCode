#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

using namespace std;

#define INPUT_SIZE 4096 //共享内存的大小
#define PROCESS_NAME L"MemoryShare" //访问地址标志，类似于字典中的key

/*
	服务器的功能就是开辟出一块共享内存，然后将数据放入内存中

*/

int main() {
	char input_str[] = "test data";//存放的数据

	//创建共享内存
	HANDLE hFileMap_Handle = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL, PAGE_EXECUTE_READWRITE, 0, INPUT_SIZE, PROCESS_NAME);
	//得到的共享内存指针
	LPVOID share_memory_ptr = MapViewOfFile(hFileMap_Handle, 
		FILE_MAP_ALL_ACCESS, 0, 0, INPUT_SIZE);
	//把客户端读取的数据放在共享内存地址上
	strcpy((char*)share_memory_ptr, input_str);
	//设置等待时间
	Sleep(5000000);
	//解除映射
	UnmapViewOfFile(share_memory_ptr);
	//关闭句柄
	CloseHandle(hFileMap_Handle);

	cout << "End" << endl;
	return 0;
}


