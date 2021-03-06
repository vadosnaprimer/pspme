/*
 * @(#)jni_util_import.h	1.5 06/10/10
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

#ifndef JNI_UTIL_H
#define JNI_UTIL_H

#include "jni.h"
#include "jni_cvm_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file contains utility functions that can be implemented in pure JNI.
 *
 * Caution: Callers of functions declared in this file should be
 * particularly aware of the fact that these functions are convenience
 * functions, and as such are often compound operations, each one of
 * which may throw an exception. Therefore, the functions this file
 * will often return silently if an exception has occured, and callers
 * must check for exception themselves.  
 */

/* Throw a Java exception by name. Similar to SignalError. */
_declspec(dllimport) void JNICALL 
JNU_ThrowByName(JNIEnv *env, const char *name, const char *msg);

/* Throw common exceptions */
/* Note: these have been macroized in jni_cvm_util.h */

#if 0

_declspec(dllimport) void JNICALL 
JNU_ThrowNullPointerException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowArrayIndexOutOfBoundsException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowOutOfMemoryError(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowIllegalArgumentException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowIllegalAccessError(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowIllegalAccessException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowInternalError(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowIOException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowNoSuchFieldException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowNoSuchMethodException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowClassNotFoundException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowNumberFormatException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowNoSuchFieldError(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowNoSuchMethodError(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowStringIndexOutOfBoundsException(JNIEnv *env, const char *msg);

_declspec(dllimport) void JNICALL 
JNU_ThrowInstantiationException(JNIEnv *env, const char *msg);

#endif

/* Throw an exception by name, using the string returned by
 * JVM_LastErrorString for the detail string.  If the last-error
 * string is NULL, use the given default detail string.
 */
_declspec(dllimport) void JNICALL
JNU_ThrowByNameWithLastError(JNIEnv *env, const char *name,
			     const char *defaultMessage);

/* Throw an IOException, using the last-error string for the detail
 * string.  If the last-error string is NULL, use the given default
 * detail string.
 */
_declspec(dllimport) void JNICALL
JNU_ThrowIOExceptionWithLastError(JNIEnv *env, const char *defaultDetail);

/* Convert between Java strings and i18n C strings */
_declspec(dllimport) jstring
NewStringPlatform(JNIEnv *env, const char *str);

_declspec(dllimport) const char *
GetStringPlatformChars(JNIEnv *env, jstring jstr, jboolean *isCopy);

_declspec(dllimport) jstring JNICALL
JNU_NewStringPlatform(JNIEnv *env, const char *str);

_declspec(dllimport) const char * JNICALL
JNU_GetStringPlatformChars(JNIEnv *env, jstring jstr, jboolean *isCopy);

_declspec(dllimport) void JNICALL 
JNU_ReleaseStringPlatformChars(JNIEnv *env, jstring jstr, const char *str);

/* Class constants */ 
/* Note: these have been macroized in jni_cvm_util.h */

#if 0

_declspec(dllimport) jclass JNICALL 
JNU_ClassString(JNIEnv *env);

_declspec(dllimport) jclass JNICALL 
JNU_ClassClass(JNIEnv *env);

_declspec(dllimport) jclass JNICALL 
JNU_ClassObject(JNIEnv *env);

_declspec(dllimport) jclass JNICALL 
JNU_ClassThrowable(JNIEnv *env);

#endif

/* Copy count number of arguments from src to dst. Array bounds
 * and ArrayStoreException are checked.
 */
_declspec(dllimport) jint JNICALL 
JNU_CopyObjectArray(JNIEnv *env, jobjectArray dst, jobjectArray src, 
		    jint count);

/* Invoke a object-returning static method, based on class name,
 * method name, and signature string.
 *
 * The caller should check for exceptions by setting hasException
 * argument. If the caller is not interested in whether an exception
 * has occurred, pass in NULL.
 */
_declspec(dllimport) jvalue JNICALL
JNU_CallStaticMethodByName(JNIEnv *env,
			   jboolean *hasException,
			   const char *class_name, 
			   const char *name, 
			   const char *signature,
			   ...);

/* Invoke an instance method by name. 
 */
_declspec(dllimport) jvalue JNICALL 
JNU_CallMethodByName(JNIEnv *env, 
		     jboolean *hasException,
		     jobject obj, 
		     const char *name,
		     const char *signature,
		     ...);

_declspec(dllimport) jvalue JNICALL 
JNU_CallMethodByNameV(JNIEnv *env, 
		      jboolean *hasException,
		      jobject obj, 
		      const char *name,
		      const char *signature,
		      va_list args);

/* Construct a new object of class, specifiying the class by name,
 * and specififying which constructor to run and what arguments to
 * pass to it.
 *
 * The method will return an initialized instance if successful.
 * It will return NULL if an error has occured (for example if
 * it ran out of memory) and the appropriate Java exception will
 * have been thrown.
 */
_declspec(dllimport) jobject JNICALL 
JNU_NewObjectByName(JNIEnv *env, const char *class_name,
		    const char *constructor_sig, ...);

/* returns:
 * 0: object is not an instance of the class named by classname.
 * 1: object is an instance of the class named by classname.
 * -1: the class named by classname cannot be found. An exception
 * has been thrown.
 */
_declspec(dllimport) jint JNICALL
JNU_IsInstanceOfByName(JNIEnv *env, jobject object, char *classname);


/* Get or set class and instance fields.
 * Note that set functions take a variable number of arguments,
 * but only one argument of the appropriate type can be passed.
 * For example, to set an integer field i to 100:
 *
 * JNU_SetFieldByName(env, &exc, obj, "i", "I", 100);
 *
 * To set a float field f to 12.3:
 *
 * JNU_SetFieldByName(env, &exc, obj, "f", "F", 12.3);
 *
 * The caller should check for exceptions by setting hasException
 * argument. If the caller is not interested in whether an exception
 * has occurred, pass in NULL.
 */
_declspec(dllimport) jvalue JNICALL
JNU_GetFieldByName(JNIEnv *env, 
		   jboolean *hasException,
		   jobject obj,
		   const char *name, 
		   const char *sig);
_declspec(dllimport) void JNICALL
JNU_SetFieldByName(JNIEnv *env,
		   jboolean *hasException,
		   jobject obj, 
		   const char *name,
		   const char *sig,
		   ...);

_declspec(dllimport) jvalue JNICALL
JNU_GetStaticFieldByName(JNIEnv *env,
			 jboolean *hasException,
			 const char *classname,
			 const char *name,
			 const char *sig);
_declspec(dllimport) void JNICALL
JNU_SetStaticFieldByName(JNIEnv *env,
			 jboolean *hasException,
			 const char *classname, 
			 const char *name,
			 const char *sig,
			 ...);


/*
 * Calls the .equals method.
 */
_declspec(dllimport) jboolean JNICALL
JNU_Equals(JNIEnv *env, jobject object1, jobject object2);


/************************************************************************
 * Thread calls
 *
 * Convenience thread-related calls on the java.lang.Object class.
 */

_declspec(dllimport) void JNICALL
JNU_MonitorWait(JNIEnv *env, jobject object, jlong timeout);

_declspec(dllimport) void JNICALL
JNU_Notify(JNIEnv *env, jobject object);

_declspec(dllimport) void JNICALL
JNU_NotifyAll(JNIEnv *env, jobject object);


/************************************************************************
 * Miscellaneous utilities used by the class libraries
 */

#define IS_NULL(obj) ((obj) == NULL)
#define JNU_IsNull(env,obj) ((obj) == NULL)


/************************************************************************
 * Debugging utilities
 */

_declspec(dllimport) void JNICALL
JNU_PrintString(JNIEnv *env, char *hdr, jstring string);

_declspec(dllimport) void JNICALL
JNU_PrintClass(JNIEnv *env, char *hdr, jobject object);

_declspec(dllimport) jstring JNICALL
JNU_ToString(JNIEnv *env, jobject object);

/* 
 * Package shorthand for use by native libraries
 */
#define JNU_JAVAPKG         "java/lang/"
#define JNU_JAVAIOPKG       "java/io/"
#define JNU_JAVANETPKG      "java/net/"

/*
 * Check if the current thread is attached to the VM, and returns
 * the JNIEnv of the specified version if the thread is attached.
 *
 * If the current thread is not attached, this function returns 0.
 *
 * If the current thread is attached, this function returns the
 * JNI environment, or returns (void *)JNI_ERR if the specified
 * version is not suppored. 
 */
_declspec(dllimport) void * JNICALL
JNU_GetEnv(JavaVM *vm, jint version);

/*
 * Warning free access to pointers stored in Java long fields.
 */
#define JNU_GetLongFieldAsPtr(env,obj,id) \
    ((void *)(unsigned long)(*(env))->GetLongField((env),(obj),(id)))
#define JNU_SetLongFieldFromPtr(env,obj,id,val) \
    (*(env))->SetLongField((env),(obj),(id),(jlong)(unsigned long)(val))

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* JNI_UTIL_H */
