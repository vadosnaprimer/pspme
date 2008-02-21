/*
 * @(#)sync_md.c	1.32 06/10/10
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

#include "javavm/include/porting/sync.h"
#include "javavm/include/porting/threads.h"
#include "javavm/include/porting/float.h"	/* for setFPMode() */
#ifdef CVM_JVMPI
#include "javavm/include/globals.h"
#endif
#ifdef CVM_JVMTI
#include "javavm/include/globals.h"
#include "javavm/include/jvmtiExport.h"
#endif
#ifdef CVM_JIT
#include "javavm/include/porting/jit/jit.h"
#endif


#ifdef CVM_THREAD_SUSPENSION
/* Purpose: Locks the mutex.  This version is only needed to work around
   issues that pthread library semantics that poses a problem for mutex
   locking in the face of thread suspension.  Without thread suspension,
   we can call the POSIX mutex lock directly. */
void CVMmutexLock(CVMMutex *m)
{
}
#endif /* CVM_THREAD_SUSPENSION */

void
CVMmutexSetOwner(CVMThreadID *self, CVMMutex *m, CVMThreadID *target)
{
}

CVMBool
CVMcondvarWait(CVMCondVar* c, CVMMutex* m, CVMJavaLong millis)
{
    return CVM_TRUE;

}

CVMBool
CVMcondvarInit(CVMCondVar * c, CVMMutex * m)
{
    return CVM_TRUE;
}

void
CVMcondvarDestroy(CVMCondVar * c)
{
}

void
CVMcondvarNotify(CVMCondVar * c)
{
}

void
CVMcondvarNotifyAll(CVMCondVar * c)
{
}

