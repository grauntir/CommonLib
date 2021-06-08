/*
 * RingBuf.c
 *
 *  Created on: 8 июн. 2021 г.
 *      Author: grau
 */

#include "RingBuf.h"

struct CRingBuf {
	int     L;
	pMem_t	B;
	pMem_t	Head;
	pMem_t	Tail;	// used as empty flag when zero
};

void CRingBuf_Init(CRingBuf* rb, char* Mem, int Len){
	rb->L = Len;
	rb->B = Mem;
	CRingBuf_Clear(rb);
};

unsigned CRingBuf_UsedSpace(CRingBuf *rb)
{
	pMem_t TmpHead = rb->Head;
	pMem_t TmpTail = rb->Tail;
	unsigned Space = 0;

	if(rb->Tail == 0){
		return 0;
	}

	if ( TmpTail > TmpHead){
		unsigned Distance = TmpTail - TmpHead;
		Space = Distance;
	}else{
		unsigned Distance = TmpHead - TmpTail;
		Space = Distance + 1;
	};

	return Space;
};

unsigned CRingBuf_Capacity(CRingBuf *rb)
{
	return rb->L;
};

BOOL CRingBuf_IsEmpty(CRingBuf *Buf)
{
	BOOL Ret = (Buf->Tail == 0);
	return Ret;
}

BOOL CRingBuf_IsFull(CRingBuf *rb)
{
	BOOL Ret = FALSE;

	if(rb->Tail == 0){
		return FALSE;
	}

	pMem_t TmpHead = (rb->Head);
	++TmpHead;

	if(TmpHead == &(rb->B[rb->L])){
		TmpHead = &(rb->B[0]);
	}

	if ( TmpHead == rb->Tail) {
		Ret = TRUE;
	}

	return Ret;
}

void CRingBuf_Clear(CRingBuf *rb)
{
	rb->Head=&(rb->B[0]);
	rb->Tail=0;
}


unsigned CRingBuf_Put(CRingBuf *rb, pMem_t InBufPtr, unsigned Cnt)
{
	unsigned Total = 0;
	unsigned FreeSpace = rb->L - CRingBuf_UsedSpace(rb);

	Total = (FreeSpace > Cnt) ? Cnt : FreeSpace;
	unsigned Ret = Total;

	pMem_t TmpHead = rb->Head;
	pMem_t End = &(rb->B[rb->L]);
	pMem_t Beg = &(rb->B[0]);
	pMem_t pTmpIn = InBufPtr;


	if(Total && rb->Tail==0){
		rb->Tail = TmpHead;
		*TmpHead = *pTmpIn;
		++pTmpIn;
		--Total;
	}

	while(Total--){
		++TmpHead;
		if(TmpHead == End){
			TmpHead = Beg;
		}
		*TmpHead = *pTmpIn;
		++pTmpIn;
	}
	rb->Head = TmpHead;

	return Ret;
}

unsigned CRingBuf_Get(CRingBuf *rb, pMem_t pOutBuf, unsigned Cnt)
{
	unsigned Total = 0;
	unsigned UsedCnt = CRingBuf_UsedSpace(rb);

	Total = (UsedCnt > Cnt) ? Cnt : UsedCnt;
	unsigned Ret = Total;

	//pMem_t TmpHead = rb->Head;
	pMem_t TmpTail = rb->Tail;
	pMem_t End = &(rb->B[rb->L]);
	pMem_t Beg = &(rb->B[0]);

	pMem_t TmpOutPtr = pOutBuf;

	while(Total--){
		*TmpOutPtr = *TmpTail;
		++TmpOutPtr;
		++TmpTail;
		if(TmpTail == End){
			TmpTail = Beg;
		}
	}

	if(Ret == UsedCnt){
		rb->Tail = 0;
	}else{
		rb->Tail = TmpTail;
	}

	return Ret;
}


BOOL CRingBuf_PutOneChar(CRingBuf *rb, char Dat)
{
	BOOL Ret = FALSE;

	if( !CRingBuf_IsFull(rb) )
	{
		pMem_t TmpHead = rb->Head;
		pMem_t End = &(rb->B[rb->L]);
		pMem_t Beg = &(rb->B[0]);


		if(rb->Tail==0){
			*(rb->Head) = Dat;
			rb->Tail = rb->Head;
		}else{
			++TmpHead;
			if(TmpHead == End){
				TmpHead = Beg;
			}

			*TmpHead = Dat;
			rb->Head = TmpHead;
		}
		Ret = TRUE;
	}
	return Ret;
}

BOOL CRingBuf_GetOneChar(CRingBuf *rb, char * Dat)
{
	BOOL Ret = FALSE;

	unsigned UsedSpace = CRingBuf_UsedSpace(rb);

	if( UsedSpace > 0 )
	{
		//pMem_t TmpHead = rb->Head;
		pMem_t TmpTail = rb->Tail;
		pMem_t End = &(rb->B[rb->L]);
		pMem_t Beg = &(rb->B[0]);

		++TmpTail;
		if(TmpTail == End){
			TmpTail = Beg;
		}
		*Dat = *TmpTail;

		if(UsedSpace == 1){
			rb->Tail = 0;
		}else{
			rb->Tail = TmpTail;
		}
		Ret = TRUE;
	}
	return Ret;
}

