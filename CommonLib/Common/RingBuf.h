/*
 * RBuf.h
 *
 *  Created on: 8 июн. 2021 г.
 *      Author: grau
 */

#ifndef RBUF_H_
#define RBUF_H_



#define BOOL unsigned char
#define TRUE 1
#define FALSE 0


typedef char* pMem_t;
typedef struct CRingBuf CRingBuf;

//------------------------------------------------------------------------------
void CRingBuf_Init(CRingBuf* Buf, char* Mem, int Len);
//------------------------------------------------------------------------------
unsigned CRingBuf_UsedSpace(CRingBuf *Buf);
//------------------------------------------------------------------------------
unsigned CRingBuf_Capacity(CRingBuf *Buf);
//------------------------------------------------------------------------------
BOOL CRingBuf_IsEmpty(CRingBuf *Buf);
//------------------------------------------------------------------------------
BOOL CRingBuf_IsFull(CRingBuf *Buf);
//------------------------------------------------------------------------------
void CRingBuf_Clear(CRingBuf *Buf);
//------------------------------------------------------------------------------
unsigned CRingBuf_Put(CRingBuf *Buf, pMem_t InBufPtr, unsigned Cnt);
//------------------------------------------------------------------------------
unsigned CRingBuf_Get(CRingBuf *Buf, pMem_t OutBufPtr, unsigned Cnt);
//------------------------------------------------------------------------------
BOOL CRingBuf_PutOneChar(CRingBuf *Buf, char Dat);
//------------------------------------------------------------------------------
// TODO: must be implemented together with iterators
BOOL CRingBuf_Read(CRingBuf *Buf, pMem_t Dat) ;
//------------------------------------------------------------------------------
BOOL CRingBuf_GetOneChar(CRingBuf *Buf, char * Dat);


#endif /* RBUF_H_ */
