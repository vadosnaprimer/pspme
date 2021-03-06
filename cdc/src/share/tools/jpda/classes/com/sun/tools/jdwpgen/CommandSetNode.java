/*
 * @(#)CommandSetNode.java	1.12 06/10/25
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

package com.sun.tools.jdwpgen;

import java.util.*;
import java.io.*;

class CommandSetNode extends AbstractNamedNode {

    void constrainComponent(Context ctx, Node node) {
        if (node instanceof CommandNode) {
            node.constrain(ctx);
        } else {
            error("Expected 'Command' item, got: " + node);
        }
    }

    void document(PrintWriter writer) {
        writer.println("<h4><a name=\"" + context.whereC + "\">" + name + 
                       " Command Set</a> (" + 
                       nameNode.value() + ")</h4>");
        writer.println(comment());
        for (Iterator it = components.iterator(); it.hasNext();) {
            ((Node)it.next()).document(writer);
        }
    }

    void documentIndex(PrintWriter writer) {
        writer.print("<li><a href=\"#" + context.whereC + "\">");
        writer.println(name() + "</a> Command Set (" + 
                       nameNode.value() + ")");
        writer.println("<ul>");
        for (Iterator it = components.iterator(); it.hasNext();) {
            ((Node)it.next()).documentIndex(writer);
        }
        writer.println("</ul>");
    }

    void genJavaClassSpecifics(PrintWriter writer, int depth) {
        indent(writer, depth);
        writer.println("static final int COMMAND_SET = " + nameNode.value() + ";");
        indent(writer, depth);
        writer.println("private " + name() + "() {}  // hide constructor");
    }

    void genJava(PrintWriter writer, int depth) {
        genJavaClass(writer, depth);
    }

}
