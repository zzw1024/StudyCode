#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

using namespace std;

#define INPUT_SIZE 4096
#define PROCESS_NAME L"MemoryShare"

int main() {
	//打开共享内存文件对象
	HANDLE hFileMap_Handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL,
		PROCESS_NAME);
	//判断句柄是否存在
	if (hFileMap_Handle) {
		LPVOID lpBase = MapViewOfFile(hFileMap_Handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		char szBuffer[INPUT_SIZE] = { 0 };
		strcpy(szBuffer, (char*)lpBase);
		cout << "读取的数据为：" << szBuffer << endl;

		//解除映射
		UnmapViewOfFile(lpBase);
		//关闭句柄
		CloseHandle(hFileMap_Handle);
	}
	return 0;
}