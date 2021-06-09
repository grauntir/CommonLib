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

	if(rb->Head == 0){
		return rb->L;
	}

	if ( TmpTail <= TmpHead)
	{
		unsigned Distance = TmpHead - TmpTail;
		Space = Distance;
	}else{
		unsigned Distance = TmpTail - TmpHead;
		Space = rb->L - Distance;
	};

	return Space;
};

unsigned CRingBuf_FreeSpace(CRingBuf *rb)
{
	unsigned Space = rb->L - CRingBuf_UsedSpace(rb);
	return Space;
};

unsigned CRingBuf_Capacity(CRingBuf *rb)
{
	return rb->L;
};

BOOL CRingBuf_IsEmpty(CRingBuf *rb)
{
	BOOL Ret = FALSE;
	if(0 != rb->Head){
		if(rb->Tail == rb->Head){
			Ret = TRUE;
		}
	};
	return Ret;
}

BOOL CRingBuf_IsFull(CRingBuf *rb)
{
	BOOL Ret = FALSE;
	if(0 == rb->Head){
		Ret = TRUE;
	};
	return Ret;
}

void CRingBuf_Clear(CRingBuf *rb)
{
	rb->Head=&(rb->B[0]);
	rb->Tail=&(rb->B[0]);
}


unsigned CRingBuf_Put(CRingBuf *rb, pMem_t InBufPtr, unsigned Cnt)
{
	unsigned FreeSpace = CRingBuf_FreeSpace(rb);

	if(!FreeSpace){
		return 0;
	}

	unsigned Total = MIN(Cnt, FreeSpace);
	unsigned Ret = Total;

	pMem_t TmpHead = rb->Head;
	pMem_t End = &(rb->B[rb->L]);
	pMem_t Beg = &(rb->B[0]);
	pMem_t pTmpIn = InBufPtr;

	while(Total--){
		*TmpHead = *pTmpIn;
		++TmpHead;
		if(TmpHead == End){
			TmpHead = Beg;
		}
		++pTmpIn;
	};

	if(Ret == FreeSpace){
		rb->Head = 0;
	}else{
		rb->Head = TmpHead;
	};

	return Ret;
}

unsigned CRingBuf_Get(CRingBuf *rb, pMem_t pOutBuf, unsigned Cnt)
{
	unsigned Total = 0;
	unsigned UsedCnt = CRingBuf_UsedSpace(rb);

	Total = MIN(Cnt, UsedCnt);
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
	if( 0 != rb->Head){
		rb->Tail = TmpTail;
	}else{
		// order is important!
		pMem_t Swap = rb->Tail;
		rb->Tail = TmpTail;
		rb->Head = Swap;
	}

	return Ret;
}


BOOL CRingBuf_PutOneChar(CRingBuf *rb, char Dat)
{
	BOOL Ret = CRingBuf_Put(rb, &Dat, 1);
	return Ret;
}

BOOL CRingBuf_GetOneChar(CRingBuf *rb, char * Dat)
{
	BOOL Ret = CRingBuf_Get(rb, Dat, 1);
	return Ret;
}

