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


/// Return min of two numbers. Commonly used but never defined as part of standard headers
#ifndef MIN
#define MIN( n1, n2 )   ((n1) > (n2) ? (n2) : (n1))
#endif

/// Return max of two numbers. Commonly used but never defined as part of standard headers
#ifndef MAX
#define MAX( n1, n2 )   ((n1) > (n2) ? (n1) : (n2))
#endif


//------------------------------------------------------------------------------
/**
 * Initialization of internal structures
 * @param Buf: class item
 * @param Mem: Pointer to the memory was allocated
 * @param Len: size of allocated memory
 */
void CRingBuf_Init(CRingBuf* Buf, char* Mem, int Len);
//------------------------------------------------------------------------------
/**
 * Return of used (and an available) space (bytes) in this class item
 * @param rb: class item
 */
unsigned CRingBuf_UsedSpace(CRingBuf *rb);
unsigned CRingBuf_FreeSpace(CRingBuf *rb);
//------------------------------------------------------------------------------
/**
 * Total size (bytes) of internal buffer, just for internal use
 * @param rb
 */
unsigned CRingBuf_Capacity(CRingBuf *rb);
//------------------------------------------------------------------------------
/**
 * Fast check without size computation
 * @param rb
 * @return
 */
BOOL CRingBuf_IsEmpty(CRingBuf *rb);
BOOL CRingBuf_IsFull(CRingBuf *rb);
//------------------------------------------------------------------------------
/**
 * Clear of all data that was stored.
 * Really just index cleared
 * @param rb
 */
void CRingBuf_Clear(CRingBuf *rb);
//------------------------------------------------------------------------------
/**
 * Store some data. If no enough space then only leader part going on
 * @param rb
 * @param InBufPtr: pointer to the incoming buffer
 * @param Cnt: size (byte) on the input
 * @return: the real size of data stored
 */
unsigned CRingBuf_Put(CRingBuf *rb, pMem_t InBufPtr, unsigned Cnt);
//------------------------------------------------------------------------------
/**
 * extract data from this object.
 * @param rb
 * @param OutBufPtr
 * @param Cnt
 */
unsigned CRingBuf_Get(CRingBuf *rb, pMem_t OutBufPtr, unsigned Cnt);
//------------------------------------------------------------------------------
/**
 * The same as before but for one byte only
 * @param rb
 * @param Dat
 * @return: TRUE if success
 */
BOOL CRingBuf_PutOneChar(CRingBuf *rb, char Dat);
BOOL CRingBuf_GetOneChar(CRingBuf *rb, char * Dat);
//------------------------------------------------------------------------------
// TODO: must be implemented together with iterators
BOOL CRingBuf_Read(CRingBuf *rb, pMem_t Dat) ;
//------------------------------------------------------------------------------



#endif /* RBUF_H_ */
