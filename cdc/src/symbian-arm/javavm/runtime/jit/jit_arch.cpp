/*
 * @(#)jit_arch.c	1.22 04/08/23
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
extern "C" {
#include "javavm/include/defs.h"
#include "javavm/include/porting/jit/jit.h"
#if 0
#include "javavm/include/objects.h"

#include "javavm/include/assert.h"
#include "javavm/include/globals.h"
#include "javavm/include/porting/memory.h"
#include "javavm/include/porting/jit/jit.h"
#endif
}

#include <e32def.h>
#include <e32std.h>


static RChunk rc;
void *
CVMJITallocCodeCache(CVMSize *size)
{
    if (rc.CreateLocalCode((TInt)(*size), (TInt)(*size), EOwnerProcess) != KErrNone) {
        return NULL; /* allocation failed */
    } else {
        return rc.Base();
    }
}

void
CVMJITfreeCodeCache(void *start)
{
    rc.Close();
}
