/*
 ============================================================================
 Name        : RBuf.c
 Author      : Grau
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "../Common/RingBuf.h"

struct CRingBuf {
	int     L;
	pMem_t	B;
	pMem_t	Head;	// used as FULL flag when zero
	pMem_t	Tail;
};


void PrintBuf(CRingBuf* rb){
	int Total = rb->L;

	// take idx from ptr
	pMem_t Head = rb->Head;
	pMem_t Tail = rb->Tail;
	int HeadIdx =  Head - rb->B +1;
	if(!Head){
		HeadIdx = 0;
	}
	int TailIdx = Tail - rb->B;
	int UsedCnt = CRingBuf_UsedSpace(rb);

	//printf("Items: %d, Head: %d, Tail: %d \n", UsedCnt, HeadIdx, TailIdx);

	int i = 0;
	while(i < Total){
		if(TailIdx == i){
			if(CRingBuf_IsFull(rb)){
				printf("%d:TH \t,", rb->B[i]);
			}else{
				printf("%d:T \t,", rb->B[i]);
			}
		} else if(Head == &(rb->B[i])){
			printf("%d:H \t,", rb->B[i]);
		} else {
			printf("%d \t,", rb->B[i]);
		}
		++i;
	}

	printf("Items: %d", UsedCnt);
	if(CRingBuf_IsFull(rb)){
		printf("[F]");
	};
	printf(", Head: %d, Tail: %d \n", HeadIdx, TailIdx);

	printf("\n");
}


int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	printf("size of char == %d\n", (int)sizeof(char));

	CRingBuf TstBuf;
	enum {eBufLen = 3};
	char Buf[eBufLen] = {0};
	char OutBuf[eBufLen];
	char TstDataBuf[eBufLen] = {6, 7, 8};
	int USpace = 0;

	int i = 0;
	while(i < eBufLen){
		printf("%d \t,", i);
		++i;
	}
	printf("\n \n");

	CRingBuf_Init(&TstBuf, Buf, eBufLen);
	USpace = CRingBuf_UsedSpace(&TstBuf);
	printf("Test of used space: should be zero\n");
	printf("used size: %d\n", USpace);

	CRingBuf_PutOneChar(&TstBuf, 0);
	USpace = CRingBuf_UsedSpace(&TstBuf);
	printf("Test of used space: should be one\n");
	printf("used size: %d\n", USpace);

	PrintBuf(&TstBuf);
	CRingBuf_PutOneChar(&TstBuf, 1);
	PrintBuf(&TstBuf);
	CRingBuf_PutOneChar(&TstBuf, 2);
	PrintBuf(&TstBuf);

	USpace = CRingBuf_UsedSpace(&TstBuf);
	printf("Test of used space: should be the same as buffer size\n");
	printf("used size: %d\n", USpace);


	printf("Test of overflow: nothing should be changed\n");
	CRingBuf_PutOneChar(&TstBuf, 4);
	PrintBuf(&TstBuf);
	CRingBuf_PutOneChar(&TstBuf, 5);

	printf("Test of read all\n");
	CRingBuf_Get(&TstBuf, OutBuf, eBufLen-1);
	CRingBuf_Get(&TstBuf, &(OutBuf[eBufLen-1]), 1);

	printf("data was read from: 0, 1, 2 are expected:\n");
	for(i=0; i<eBufLen; ++i){
		printf("%d\t,", OutBuf[i]);
	}
	printf("\n\n");

	printf("Test refill: 3, 4, 5 are expected\n");
	CRingBuf_PutOneChar(&TstBuf, 3);
	PrintBuf(&TstBuf);
	CRingBuf_PutOneChar(&TstBuf, 4);
	PrintBuf(&TstBuf);
	CRingBuf_PutOneChar(&TstBuf, 5);
	PrintBuf(&TstBuf);

	printf("Test of clear and refill from buf: 6, 7, 8 are expected\n");
	CRingBuf_Clear(&TstBuf);
	CRingBuf_Put(&TstBuf, TstDataBuf, eBufLen);
	PrintBuf(&TstBuf);

	printf("And read them back: 6, 7, 8 are expected\n");
	CRingBuf_Get(&TstBuf, OutBuf, eBufLen);
	for(i=0; i<eBufLen; ++i){
		printf("%d\t,", OutBuf[i]);
	}
	printf("\n\n");

	return EXIT_SUCCESS;
}
