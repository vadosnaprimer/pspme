/*
 * @(#)AWTEventListenerProxy.java	1.5 03/01/23
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

package java.awt.event;

import java.util.EventListenerProxy;
import java.awt.AWTEvent;
import java.awt.event.AWTEventListener;

/**
 * A class which extends the <code>EventListenerProxy</code>, specifically 
 * for adding an <code>AWTEventListener</code> for a specific event mask.
 * Instances of this class can be added as <code>AWTEventListener</code>s to
 * a Toolkit object. 
 * <p>
 * The <code>getAWTEventListeners</code> method of Toolkit can 
 * return a mixture of <code>AWTEventListener</code> and
 * <code>AWTEventListenerProxy</code> objects.
 * 
 * @see java.awt.Toolkit
 * @see java.util.EventListenerProxy
 * @since 1.4
 */
public class AWTEventListenerProxy extends java.util.EventListenerProxy
        implements AWTEventListener {

    private long eventMask;

    /**
     * Constructor which binds the AWTEventListener to a specific
     * event mask.
     * 
     * @param listener The listener object
     * @param eventMask The bitmap of event types to receive
     */ 
    public AWTEventListenerProxy (long eventMask, 
            AWTEventListener listener) {
        super(listener);
        this.eventMask = eventMask;
    }

    /**
     * Forwards the property change event to the listener delegate.
     *
     * @param evt the property change event
     */
    public void eventDispatched(AWTEvent evt) {
        ((AWTEventListener)getListener()).eventDispatched(evt);
    }

    /**
     * Returns the event mask associated with the
     * listener.
     */
    public long getEventMask() {
        return eventMask;
    }
}
