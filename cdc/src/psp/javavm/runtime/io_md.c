/*
 * @(#)io_md.c	1.21 06/10/10
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

#include "javavm/include/porting/io.h"
#include "javavm/include/porting/int.h"
#include "javavm/include/porting/sync.h"
#include "javavm/include/porting/threads.h"
#include "javavm/include/porting/doubleword.h"
#include "javavm/include/porting/globals.h"
#include "javavm/export/jvm.h"

static int
fileMode(int fd, int *mode)
{
    int ret;
    struct stat buf;

    ret = fstat(fd, &buf);
    (*mode) = buf.st_mode;
    return ret;
}


CVMInt32
POSIXioAvailable(CVMInt32 fd, CVMInt64 *bytes)
{
    CVMInt64 cur, end;
    int mode;

    if (fileMode(fd, &mode) >= 0) {
        if (S_ISCHR(mode) || S_ISFIFO(mode) || S_ISSOCK(mode)) {
	    printf("POSIXioAvailable is not implemented for this file mode: %x\n", mode);
	    return -1;
        }
    }
    {
	CVMInt32 cur32, end32;
	if ((cur32 = lseek(fd, 0L, SEEK_CUR)) == -1) {
	    return 0;
	} else if ((end32 = lseek(fd, 0L, SEEK_END)) == -1) {
	    return 0;
	} else if (lseek(fd, cur32, SEEK_SET) == -1) {
	    return 0;
	}
	/* %comment d003 */
	cur = CVMint2Long(cur32);
	end = CVMint2Long(end32);
    }
    *bytes = CVMlongSub(end, cur);
    return 1;
}

