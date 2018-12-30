// -----------------------------------------------------------------------------
//
//		Header file
//
//		File Name: IfSaveFile.h
//		Version		:	1.00
//
//					Copyright 2003 Interface Corporation. All rights reserved.
// -----------------------------------------------------------------------------
#if !defined( _IFSAVEFILE_H_ )
#define _IFSAVEFILE_H_

#ifdef __cplusplus
extern	"C" {
#endif

// -----------------------------------------------------------------------------
//	ÉGÉâÅ[éØï éq
// -----------------------------------------------------------------------------
#define IFSAVEFILE_ERROR_SUCCESS				0x00000000
#define IFSAVEFILE_ERROR_INVALID_PARAMETER		0xC0000010
#define IFSAVEFILE_ERROR_NOT_ALLOCATE_MEMORY	0xC0000021
#define IFSAVEFILE_ERROR_NOT_OPENFILE			0xC0001000
#define IFSAVEFILE_ERROR_INVALID_WRITEFILE		0xC0001001

int WINAPI IfSaveBitmapFile(LPCSTR, void*, unsigned long, long, long);

#ifdef __cplusplus
}
#endif

#endif
