/*
 * @(#)Visibility.java	1.19 06/10/10
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

package java.beans;

/**
 * Under some circumstances a bean may be run on servers where a GUI
 * is not available.  This interface can be used to query a bean to
 * determine whether it absolutely needs a gui, and to advise the
 * bean whether a GUI is available.
 * <p>
 * This interface is for expert developers, and is not needed
 * for normal simple beans.  To avoid confusing end-users we
 * avoid using getXXX setXXX design patterns for these methods.
 */

public interface Visibility {
    /**
     * Determines whether this bean needs a GUI.
     *
     * @return True if the bean absolutely needs a GUI available in
     *		order to get its work done.
     */
    boolean needsGui();
    /**
     * This method instructs the bean that it should not use the Gui.
     */
    void dontUseGui();
    /**
     * This method instructs the bean that it is OK to use the Gui.
     */
    void okToUseGui();
    /**
     * Determines whether this bean is avoiding using a GUI.
     *
     * @return true if the bean is currently avoiding use of the Gui.
     *   e.g. due to a call on dontUseGui().
     */
    boolean avoidingGui();
}
