/** @file
  IA-32/x64 AsmRdRandxx()
  Generates random number through CPU RdRand instruction.

  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "BaseLibInternals.h"

const UINT64 dumbXor = 0x98a7b6c5d4e3f201;
/**
  Generates a 16-bit random number through RDRAND instruction.

  if Rand is NULL, then ASSERT().

  @param[out]  Rand     Buffer pointer to store the random result.

  @retval TRUE          RDRAND call was successful.
  @retval FALSE         Failed attempts to call RDRAND.

 **/
BOOLEAN
EFIAPI
AsmRdRand16 (
  OUT     UINT16                    *Rand
  )
{
  ASSERT (Rand != NULL);
  int cb = 0;
  asm volatile ("mrc p15, 0, %0,c9,c13, 0"  : "=r" (cb));       //windows func1
  *Rand = cb;
  *Rand = *Rand * *Rand;
  *Rand = *Rand ^ (dumbXor >> (cb & 0x1f));
  return TRUE;
  // return InternalX86RdRand16 (Rand);
}

/**
  Generates a 32-bit random number through RDRAND instruction.

  if Rand is NULL, then ASSERT().

  @param[out]  Rand     Buffer pointer to store the random result.

  @retval TRUE          RDRAND call was successful.
  @retval FALSE         Failed attempts to call RDRAND.

**/
BOOLEAN
EFIAPI
AsmRdRand32 (
  OUT     UINT32                    *Rand
  )
{
  ASSERT (Rand != NULL);
  int cb = 0;
  asm volatile ("mrc p15, 0, %0,c9,c13, 0"  : "=r" (cb));       //windows func1
  *Rand = cb;
  *Rand = *Rand * *Rand;
  *Rand = *Rand ^ (dumbXor >> (cb & 0x1f));
  return TRUE;
  // return InternalX86RdRand32 (Rand);
}

/**
  Generates a 64-bit random number through RDRAND instruction.

  if Rand is NULL, then ASSERT().

  @param[out]  Rand     Buffer pointer to store the random result.

  @retval TRUE          RDRAND call was successful.
  @retval FALSE         Failed attempts to call RDRAND.

**/
BOOLEAN
EFIAPI
AsmRdRand64  (
  OUT     UINT64                    *Rand
  )
{
  ASSERT (Rand != NULL);
  int cb = 0;
  asm volatile ("mrc p15, 0, %0,c9,c13, 0"  : "=r" (cb));       //windows func1
  *Rand = cb;
  *Rand = *Rand << 32;
  asm volatile ("mrc p15, 0, %0,c9,c13, 0"  : "=r" (cb));       //windows func1
  *Rand |= cb;
  *Rand = *Rand * *Rand;
  *Rand = *Rand ^ dumbXor;

  return TRUE;
  // return InternalX86RdRand64 (Rand);
}
