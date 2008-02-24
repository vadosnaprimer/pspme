/*
 * @(#)globals_md.c	1.35 06/10/10
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
#include "javavm/include/porting/globals.h"
#include "javavm/include/porting/net.h"
#include "javavm/include/porting/io.h"
#include "javavm/include/porting/threads.h"
#include "portlibs/posix/threads.h"
#include "generated/javavm/include/build_defs.h"
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <javavm/include/utils.h>
#ifdef CVM_JIT
#include "javavm/include/porting/jit/jit.h"
#include "javavm/include/globals.h"
#endif

CVMBool CVMinitVMTargetGlobalState()
{
    /*
     * Initialize the target global state pointed to by 'target'.
     */
    return CVM_TRUE;
}

void CVMdestroyVMTargetGlobalState()
{
}

static CVMProperties props;

CVMBool CVMinitStaticState()
{
    /*
     * Initialize the static state for this address space
     */
    if (!POSIXthreadInitStaticState()) {
#ifdef CVM_DEBUG
	fprintf(stderr, "POSIXthreadInitStaticState failed\n");
#endif
	return CVM_FALSE;
    }

    
    linuxCaptureInitialStack();

    if (!linuxSyncInit()) {
#ifdef CVM_DEBUG
	fprintf(stderr, "linuxSyncInit failed\n");
#endif
        return CVM_FALSE;
    }
    
    CVMinitPathValues( &props, ".", "lib", "lib" );
    return CVM_TRUE;
}

void CVMdestroyStaticState()
{
    /*
     * ... and destroy it.
     */
    CVMdestroyPathValues((void *)&props);
    POSIXthreadDestroyStaticState();
}

const CVMProperties *CVMgetProperties()
{
    return &props;
}

