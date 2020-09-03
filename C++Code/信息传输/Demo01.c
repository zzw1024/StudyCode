
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "itcast_asn1_der.h"
#include "itcastderlog.h"

typedef struct _Teacher
{
	char name[64];
	int age;
	char *p;
	int plen;
}Teacher;

void freeTeacher(Teacher **pTeacher)
{
	if (pTeacher == NULL) {
		return;
	}
	if (pTeacher != NULL) {
		if ((*pTeacher)->p != NULL) {
			free((*pTeacher)->p);
			(*pTeacher)->p = NULL;
		}
		free(*pTeacher);
		*pTeacher = NULL;
	}
}

// 传入、传出、传入传出。
int TeacherEncode(Teacher *pThecher, unsigned char **out, int *outlen)
{
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHeadBuf = NULL;
	ITCAST_ANYBUF		*pTmpBuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;

	unsigned char		*tmpout = NULL;
	int					tmpoutlen = 0;

	//将 char * 类型的name 转换成 ITCAST_ANYBUF 类型
	ret = DER_ITCAST_String_To_AnyBuf(&pTmpBuf, pThecher->name, strlen(pThecher->name));
	if (ret != 0) {
		printf("DER_ITCAST_String_To_AnyBuf error: %d\n", ret);
		return ret;
	}

	// 编码 name  --> TLV
	ret = DER_ItAsn1_WritePrintableString(pTmpBuf, &pHeadBuf);
	if (ret != 0) {
		DER_ITCAST_FreeQueue(pTmpBuf);
		printf("DER_ItAsn1_WritePrintableString error: %d\n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmpBuf);

	pTmp = pHeadBuf;

	// 编码 age
	ret = DER_ItAsn1_WriteInteger(pThecher->age, &(pTmp->next));
	if (ret != 0) {
		printf("DER_ItAsn1_WriteInteger error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 p  char *
	ret = EncodeChar(pThecher->p, pThecher->plen, &pTmp->next);
	if (ret != 0) {
		printf("EncodeChar error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 plen
	ret = DER_ItAsn1_WriteInteger(pThecher->plen, &(pTmp->next));
	if (ret != 0) {
		printf("DER_ItAsn1_WriteInteger plen error: %d\n", ret);
		return ret;
	}

	//编码大结构体
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
	if (ret != 0) {
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("DER_ItAsn1_WriteSequence error: %d\n", ret);
		return ret;
	}

	*out = pOutData->pData;

	*outlen = pOutData->dataLen;

	return 0;
}

int mywritefile(unsigned char *buf, int len)
{
	FILE *fp = NULL;
	fp = fopen("c:/itcast/teacher.ber", "wb+");
	if (fp == NULL)
	{
		printf("fopen file error \n");
		return -1;
	}
	fwrite(buf, 1, len, fp);
	fclose(fp);
	return 0;
}

int TeacherDecode(unsigned char *indata, int inLen, Teacher **pStruct)
{
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHead = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	ITCAST_ANYBUF		*tmpAnyBuf = NULL;

	Teacher *pStrTeacher = NULL;

	// 转码 BER 报文 unsigned char * --> ITCAST_ANYBUF
	ret = DER_ITCAST_String_To_AnyBuf(&tmpAnyBuf, indata, inLen);
	if (ret != 0) {
		if (tmpAnyBuf != NULL)
			DER_ITCAST_FreeQueue(tmpAnyBuf);

		printf(" Decode DER_ITCAST_String_To_AnyBuf error: %d\n", ret);
		return ret;
	}

	// 解码大Teacher 结构体
	ret = DER_ItAsn1_ReadSequence(tmpAnyBuf, &pHead);
	if (ret != 0) {
		if (tmpAnyBuf != NULL)
			DER_ITCAST_FreeQueue(tmpAnyBuf);
		printf(" Decode DER_ItAsn1_ReadSequence error: %d\n", ret);
		return ret;
	}

	// 给Teacher 结构体 malloc 空间。
	if (pStrTeacher == NULL) {
		pStrTeacher = (Teacher *)malloc(sizeof(Teacher));
		if (pStrTeacher == NULL) {
			DER_ITCAST_FreeQueue(pHead);
			ret = -1;
			printf("Teacher malloc error: %d\n", ret);
			return ret;
		}
		memset(pStrTeacher, 0, sizeof(Teacher));
	}

	pTmp = pHead;

	// 解码 name
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0) {
		DER_ITCAST_FreeQueue(pHead);
		freeTeacher(&pStrTeacher);

		printf(" Decode DER_ItAsn1_ReadPrintableString name error: %d\n", ret);
		return ret;
	}

	// ppPrintString -> pData; ---> name
	memcpy(pStrTeacher->name, pOutData->pData, pOutData->dataLen);

	pTmp = pTmp->next;
	// 解码age
	ret = DER_ItAsn1_ReadInteger(pTmp, &pStrTeacher->age);
	if (ret != 0) {
		DER_ITCAST_FreeQueue(pHead);
		freeTeacher(&pStrTeacher);
		printf(" Decode DER_ItAsn1_ReadInteger age error: %d\n", ret);
		return ret;
	}

	pTmp = pTmp->next;
	// 解码 p
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0) {
		DER_ITCAST_FreeQueue(pHead);
		freeTeacher(&pStrTeacher);
		printf(" Decode DER_ItAsn1_ReadPrintableString p error: %d\n", ret);
		return ret;
	}
	// 给Teacher 结构体中的 p 指针开辟空间
	pStrTeacher->p = malloc(pOutData->dataLen + 1);
	if (pStrTeacher->p == NULL) {
		DER_ITCAST_FreeQueue(pHead);
		freeTeacher(&pStrTeacher);
		ret = -2;
		printf("Teacher->p malloc error: %d\n", ret);
		return ret;
	}
	memcpy(pStrTeacher->p, pOutData->pData, pOutData->dataLen);
	//pStrTeacher->p[pOutData->dataLen - 4] = 'R';
	pStrTeacher->p[pOutData->dataLen] = '\0';

	pTmp = pTmp->next;
	// 解码plen
	ret = DER_ItAsn1_ReadInteger(pTmp, &pStrTeacher->plen);
	if (ret != 0) {
		DER_ITCAST_FreeQueue(pHead);
		freeTeacher(&pStrTeacher);
		printf(" Decode DER_ItAsn1_ReadInteger plen error: %d\n", ret);
		return ret;
	}

	*pStruct = pStrTeacher;

	return 0;
}



int main(void)
{
	int					ret = 0;

	Teacher				t1;
	Teacher  *pt2 = NULL;

	unsigned char		*myOut = NULL;
	int					myOutlen = 0;

	t1.age = 10;
	strcpy(t1.name, "myName");
	t1.p = malloc(64);
	strcpy(t1.p, "aaaabbbb");
	t1.plen = strlen(t1.p);

	TeacherEncode(&t1, &myOut, &myOutlen);
	mywritefile(myOut, myOutlen);

	TeacherDecode(myOut, myOutlen, &pt2);

	if (strcmp(t1.name, pt2->name) == 0 &&
		memcmp(t1.p, pt2->p, pt2->plen) == 0)
	{
		printf("编码 == 解码 \n");
	}
	else
	{
		printf("编码 != 解码 \n");
	}

	freeTeacher(&pt2);

	printf("hello...\n");
	system("pause");

	return 0;
}