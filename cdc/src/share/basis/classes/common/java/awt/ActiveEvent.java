/*
 * @(#)ActiveEvent.java	1.9 06/10/10
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

package java.awt;

/**
 * An interface for events that know how dispatch themselves.
 * By implementing this interface an event can be placed upon the event
 * queue and its <code>dispatch()</code> method will be called when the event
 * is dispatched, using the <code>EventDispatchThread</code>.
 * <p>
 * This is a very useful mechanism for avoiding deadlocks. If
 * a thread is executing in a critical section (i.e., it has entered
 * one or more monitors), calling other synchronized code may
 * cause deadlocks. To avoid the potential deadlocks, an 
 * <code>ActiveEvent</code> can be created to run the second section of
 * code at later time. If there is contention on the monitor,
 * the second thread will simply block until the first thread
 * has finished its work and exited its monitors.
 * <p>
 * For security reasons, it is often desirable to use an <code>ActiveEvent</code> 
 * to avoid calling untrusted code from a critical thread. For
 * instance, peer implementations can use this facility to avoid 
 * making calls into user code from a system thread. Doing so avoids
 * potential deadlocks and denial-of-service attacks.
 *
 * @author  Timothy Prinzing
 * @version 1.9 02/02/00
 * @since   1.2
 */
public interface ActiveEvent {
    /**
     * Dispatch the event to it's target, listeners of the events source, 
     * or do whatever it is this event is supposed to do.
     */
    public void dispatch();
}
