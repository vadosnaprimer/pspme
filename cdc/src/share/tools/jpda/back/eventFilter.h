/*
 * @(#)eventFilter.h	1.6 06/10/25
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
 */

#ifndef JDWP_EVENTFILTER_H
#define JDWP_EVENTFILTER_H

#include "eventHandler.h"

/***** filter set-up *****/

jvmtiError eventFilter_setConditionalFilter(HandlerNode *node,
                                      jint index, jint exprID);
jvmtiError eventFilter_setCountFilter(HandlerNode *node,
                                jint index, jint count);
jvmtiError eventFilter_setThreadOnlyFilter(HandlerNode *node,
                                     jint index, jthread thread);
jvmtiError eventFilter_setLocationOnlyFilter(HandlerNode *node,
                                       jint index, 
                                       jclass clazz, 
                                       jmethodID method, 
                                       jlocation location);
jvmtiError eventFilter_setFieldOnlyFilter(HandlerNode *node,
                                    jint index, 
                                    jclass clazz, 
                                    jfieldID field);
jvmtiError eventFilter_setClassOnlyFilter(HandlerNode *node,
                                    jint index, 
                                    jclass clazz);
jvmtiError eventFilter_setExceptionOnlyFilter(HandlerNode *node,
                                        jint index, 
                                        jclass exceptionClass, 
                                        jboolean caught, 
                                        jboolean uncaught);
jvmtiError eventFilter_setInstanceOnlyFilter(HandlerNode *node,
                                       jint index, 
                                       jobject object);
jvmtiError eventFilter_setClassMatchFilter(HandlerNode *node,
                                     jint index, 
                                     char *classPattern);
jvmtiError eventFilter_setClassExcludeFilter(HandlerNode *node,
                                       jint index, 
                                       char *classPattern);
jvmtiError eventFilter_setStepFilter(HandlerNode *node,
                               jint index, 
                               jthread thread, 
                               jint size, jint depth);
jvmtiError eventFilter_setSourceNameMatchFilter(HandlerNode *node, 
                                                jint index, 
                                                char *sourceNamePattern);

/***** misc *****/

jboolean eventFilter_predictFiltering(HandlerNode *node, jclass clazz, char *classname);
jboolean isBreakpointSet(jclass clazz, jmethodID method, jlocation location);

#endif /* _EVENT_FILTER_H */
