#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

using namespace std;

#define INPUT_SIZE 4096 //�����ڴ�Ĵ�С
#define PROCESS_NAME L"MemoryShare" //���ʵ�ַ��־���������ֵ��е�key

/*
	�������Ĺ��ܾ��ǿ��ٳ�һ�鹲���ڴ棬Ȼ�����ݷ����ڴ���

*/

int main() {
	char input_str[] = "test data";//��ŵ�����

	//���������ڴ�
	HANDLE hFileMap_Handle = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL, PAGE_EXECUTE_READWRITE, 0, INPUT_SIZE, PROCESS_NAME);
	//�õ��Ĺ����ڴ�ָ��
	LPVOID share_memory_ptr = MapViewOfFile(hFileMap_Handle, 
		FILE_MAP_ALL_ACCESS, 0, 0, INPUT_SIZE);
	//�ѿͻ��˶�ȡ�����ݷ��ڹ����ڴ��ַ��
	strcpy((char*)share_memory_ptr, input_str);
	//���õȴ�ʱ��
	Sleep(5000000);
	//���ӳ��
	UnmapViewOfFile(share_memory_ptr);
	//�رվ��
	CloseHandle(hFileMap_Handle);

	cout << "End" << endl;
	return 0;
}


