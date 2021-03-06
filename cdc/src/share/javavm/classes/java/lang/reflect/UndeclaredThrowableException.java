/*
 * @(#)UndeclaredThrowableException.java	1.13 06/10/10
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

package java.lang.reflect;

/**
 * Thrown by a method invocation on a proxy instance if its invocation
 * handler's {@link InvocationHandler#invoke invoke} method throws a
 * checked exception (a <code>Throwable</code> that is not assignable
 * to <code>RuntimeException</code> or <code>Error</code>) that
 * is not assignable to any of the exception types declared in the
 * <code>throws</code> clause of the method that was invoked on the
 * proxy instance and dispatched to the invocation handler.
 *
 * <p>An <code>UndeclaredThrowableException</code> instance contains
 * the undeclared checked exception that was thrown by the invocation
 * handler, and it can be retrieved with the
 * <code>getUndeclaredThrowable()</code> method.
 * <code>UndeclaredThrowableException</code> extends
 * <code>RuntimeException</code>, so it is an unchecked exception
 * that wraps a checked exception.
 *
 * <p>As of release 1.4, this exception has been retrofitted to
 * conform to the general purpose exception-chaining mechanism.  The
 * "undeclared checked exception that was thrown by the invocation
 * handler" that may be provided at construction time and accessed via
 * the {@link #getUndeclaredThrowable()} method is now known as the
 * <i>cause</i>, and may be accessed via the {@link
 * Throwable#getCause()} method, as well as the aforementioned "legacy
 * method."
 *
 * @author	Peter Jones
 * @version	1.6, 00/02/02
 * @see		InvocationHandler
 * @since	JDK1.3
 */
public class UndeclaredThrowableException extends RuntimeException {
    static final long serialVersionUID = 330127114055056639L;

    /**
     * the undeclared checked exception that was thrown
     * @serial
     */
    private Throwable undeclaredThrowable;

    /**
     * Constructs an <code>UndeclaredThrowableException</code> with the
     * specified <code>Throwable</code>.
     *
     * @param	undeclaredThrowable the undeclared checked exception
     *		that was thrown
     */
    public UndeclaredThrowableException(Throwable undeclaredThrowable) {
	super((Throwable) null);  // Disallow initCause
        this.undeclaredThrowable = undeclaredThrowable;
    }

    /**
     * Constructs an <code>UndeclaredThrowableException</code> with the
     * specified <code>Throwable</code> and a detail message.
     *
     * @param	undeclaredThrowable the undeclared checked exception
     *		that was thrown
     * @param	s the detail message
     */
    public UndeclaredThrowableException(Throwable undeclaredThrowable,
					String s)
    {
	super(s, null);  // Disallow initCause
        this.undeclaredThrowable = undeclaredThrowable;
    }

    /**
     * Returns the <code>Throwable</code> instance wrapped in this
     * <code>UndeclaredThrowableException</code>, which may be <tt>null</tt>.
     *
     * <p>This method predates the general-purpose exception chaining facility.
     * The {@link Throwable#getCause()} method is now the preferred means of
     * obtaining this information.
     *
     * @return the undeclared checked exception that was thrown
     */
    public Throwable getUndeclaredThrowable() {
        return undeclaredThrowable;
    }

    /**
     * Returns the the cause of this exception (the <code>Throwable</code>
     * instance wrapped in this <code>UndeclaredThrowableException</code>,
     * which may be <tt>null</tt>).
     *
     * @return  the cause of this exception.
     * @since   1.4
     */
    public Throwable getCause() {
        return undeclaredThrowable;
    }
}
