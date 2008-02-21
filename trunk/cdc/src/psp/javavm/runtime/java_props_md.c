/*
 * @(#)java_props_md.c	1.36 06/10/24
 *
 * Portions Copyright  2000-2006 Sun Microsystems, Inc. All Rights
 * Reserved.  Use is subject to license terms.
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
 */

#include <pwd.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/param.h>
#include <time.h>

#include "jvm.h"
#include "jni_util.h"

#include "locale_str.h"
#include "javavm/include/porting/java_props.h"
#include "generated/javavm/include/build_defs.h"
#include "javavm/include/porting/endianness.h"

#ifndef P_tmpdir
#define P_tmpdir "./tmp"
#endif

CVMBool
CVMgetJavaProperties(java_props_t *sprops)
{
    if (sprops->user_dir) {
        return CVM_TRUE;
    }

    /* tmp dir */
    sprops->tmp_dir = P_tmpdir;

    /* Printing properties */
    sprops->printerJob = NULL;

    /* Java 2D properties */
    sprops->graphics_env = NULL;

    sprops->awt_toolkit = NULL;

    sprops->font_dir = "";

    sprops->cpu_isalist = NULL;

    /* endianness of platform */
    {
        unsigned int endianTest = 0xff000000;
        if (((char*)(&endianTest))[0] != 0)
            sprops->cpu_endian = "big";
        else
            sprops->cpu_endian = "little";
    }

    /* os properties */
    {
	sprops->os_name = "PSP";
	sprops->os_version = "?";
	
        sprops->os_arch = "mips";
    }

    /* Determing the language, country, and encoding from the host,
     * and store these in the user.language, user.region, and
     * file.encoding system properties. */
    {
        
            sprops->language = "en";
            sprops->region = "US";
	     
            sprops->encoding = "ISO8859_1";
        
    }
    
#if (CVM_ENDIANNESS == CVM_LITTLE_ENDIAN)
   sprops->unicode_encoding = "UnicodeLittle";
#else
   sprops->unicode_encoding = "UnicodeBig";
#endif

    /* user properties */
    {
	
	sprops->user_name = "?";
	sprops->user_home = "?";
    }

    /* User TIMEZONE */
    {
	/*
	 * We defer setting up timezone until it's actually necessary.
	 * Refer to TimeZone.getDefault(). However, the system
	 * property is necessary to be able to be set by the command
	 * line interface -D. Here temporarily set a null string to
	 * timezone.
	 */
	tzset();	/* for compatibility */
	sprops->timezone = "";
    }

    /* Current directory */
    {
        sprops->user_dir = ".";
    }

    sprops->file_separator = "/";
    sprops->path_separator = ":";
    sprops->line_separator = "\n";

    /* Generic Connection Framework (GCF): CommConnection Property */
    /* NOTE: comma-delimited (no spaces) list of available comm (serial)
       ports */
    sprops->commports = "";

    return CVM_TRUE;

}

/*
 * Free up memory allocated by CVMgetJavaProperties().
 */
void CVMreleaseJavaProperties(java_props_t *sprops)
{
}
