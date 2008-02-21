/*
 * @(#)sync_md.h	1.22 06/10/10
 *
 * Copyright  1990-2006 Sun Microsystems, Inc. All Rights Reserved.  
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER  
 *   
 * This program is free software; you can redistribute it and/or  
 * modify it under the terms of the GNU General Public License version  
 * 2 only, as published by the Free Software Foundation.   
 *   
 * This program is distributed in the hope that it will be useful, but  
 * WITHOUT ANY WARRANTY; without even the implied warranty of  
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  
 * General Public License version 2 for more details (a copy is  
 * included at /legal/license.txt).   
 *   
 * You should have received a copy of the GNU General Public License  
 * version 2 along with this work; if not, write to the Free Software  
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  
 * 02110-1301 USA   
 *   
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa  
 * Clara, CA 95054 or visit www.sun.com if you need additional  
 * information or have any questions. 
 *
 */

/*
 * Machine-dependent synchronization definitions.
 */

#ifndef _PSP_SYNC_MD_H
#define _PSP_SYNC_MD_H

#include "javavm/include/porting/vm-defs.h"
#include "javavm/include/sync_arch.h"

#ifndef CVM_FASTLOCK_TYPE
/* Use microlocks for fastlocks by default */
#define CVM_FASTLOCK_TYPE CVM_FASTLOCK_MICROLOCK
#endif

#ifndef CVM_MICROLOCK_TYPE
#define CVM_MICROLOCK_TYPE CVM_MICROLOCK_DEFAULT
#endif

#ifndef _ASM

/*
 * CVM_ADV_SPINLOCK support, if needed. Note that CVMvolatileStore
 * must be implemented in sync_arch.h because it is CPU dependent.
 */
#ifdef CVM_ADV_SPINLOCK

#include <time.h>   /* for nanosleep() */

/* Yield to another thread when microlock is contended */
#define CVMspinlockYield() \
    CVMspinlockYieldImpl()

static inline void CVMspinlockYieldImpl()
{
    struct timespec tm;
    tm.tv_sec = 0;
    tm.tv_nsec = 5000000; /* 5 milliseconds. */
    nanosleep(&tm, NULL);
}

#endif /* CVM_ADV_SPINLOCK */


struct CVMMutex {
   int dummy;
};

struct CVMCondVar {
   int dummy;
};

#endif /* !_ASM */
#endif /* _PSP_SYNC_MD_H */
