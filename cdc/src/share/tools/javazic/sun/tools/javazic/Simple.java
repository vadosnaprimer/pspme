/*
 * @(#)Simple.java	1.6 06/10/10
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

package sun.tools.javazic;

import	java.io.BufferedWriter;
import	java.io.File;
import	java.io.FileWriter;
import	java.io.IOException;
import	java.util.ArrayList;
import	java.util.HashMap;
import	java.util.Iterator;
import	java.util.LinkedList;
import	java.util.TreeMap;
import	java.util.TreeSet;

/** 
 * <code>Simple</code> generates TimeZoneData, which had been used as internal
 * data of TimeZone before J2SDK1.3.
 * Since J2SDK1.4 doesn't need TimeZoneData, this class is for maintenance
 * of old JDK release.
 */
class Simple extends BackEnd {

    /**
     * Zone records which are applied for given year. 
     */
    private static HashMap lastZoneRecs;

    /**
     * Rule records which are applied for given year. 
     */
    private static TreeMap lastRules;

    /** 
     * Sets last Rule records and Zone records for given timezone to each Map.
     * @param tz Timezone object for each zone
     * @return always 0
     */
    int processZoneinfo(Timezone tz) {
	String zonename = tz.getName();

	if (lastRules == null) {
	    lastRules = new TreeMap();
	    lastZoneRecs = new HashMap();
	}
	lastRules.put(zonename, tz.getLastRules()); 
	lastZoneRecs.put(zonename, tz.getLastZoneRec());

	return 0;
    }

    /** 
     * Generates TimeZoneData to output SimpleTimeZone data.
     * @param map Mappings object which is generated by {@link Main#compile Main.compile()}.
     * @return 0 if no error occurred, otherwise 1.
     */
    int generateSrc(Mappings map) {
	try {
	    String outputDir = Main.getOutputDir();
	    File outD = new File(outputDir);

	    if (!outputDir.endsWith(File.separator)) {
		outputDir += outD.separator;
	    }
	    outD.mkdirs();

	    FileWriter fw =
		new FileWriter(outputDir + "TimeZoneData.java", false);
	    BufferedWriter out = new BufferedWriter(fw);

	    out.write("import java.util.SimpleTimeZone;\n\n");
	    out.write("    static SimpleTimeZone zones[] = {\n");

	    TreeMap a = map.getAliases();
	    LinkedList roit = map.getRawOffsetsIndexTable();
	    int roit_size = roit.size();
	    for (int i = 0; i < roit_size; i++) {
		TreeSet perRO = (TreeSet)roit.get(i);
		Iterator keys = perRO.iterator();
		String realname;
		ArrayList stz;
		ZoneRec zrec;

		while (keys.hasNext()) {
		    String key = (String)keys.next();

		    if ((realname = (String)a.get(key)) != null) {
			// if this alias is not targeted, ignore it.
			if (!Zone.isTargetZone(key)) {
			    continue;
			}
			stz = (ArrayList)lastRules.get(realname);
			zrec = (ZoneRec) lastZoneRecs.get(realname);
		    } else {
			stz = (ArrayList)lastRules.get(key);
			zrec = (ZoneRec) lastZoneRecs.get(key);
		    }

		    out.write("\t//--------------------------------------------------------------------\n");
		    int offset = ((Integer)map.getRawOffsetsIndex().get(i)).intValue();
		    String s = Time.toFormedString(offset);
		    out.write("\tnew SimpleTimeZone(" + 
			Time.toFormedString(offset) + ", \"" + key + "\"");
		    if (realname != null) {
			out.write(" /* " + realname + " */");
		    }

		    if (stz == null) {
			out.write("),\n");
		    } else {
			RuleRec	rr0 = (RuleRec)stz.get(0);
			RuleRec	rr1 = (RuleRec)stz.get(1);

			out.write(",\n\t  " + Month.toString(rr0.getMonthNum()) +
				  ", " + rr0.getDay().getDayForSimpleTimeZone() + ", " + 
				  rr0.getDay().getDayOfWeekForSimpleTimeZone() + ", " +
				  Time.toFormedString((int)rr0.getTime().getTime()) + ", " + 
				  rr0.getTime().getTypeForSimpleTimeZone() + ",\n" + 

				  "\t  " + Month.toString(rr1.getMonthNum()) + ", " +
				  rr1.getDay().getDayForSimpleTimeZone() + ", " + 
				  rr1.getDay().getDayOfWeekForSimpleTimeZone() + ", " +
				  Time.toFormedString((int)rr1.getTime().getTime())+ ", " + 
				  rr1.getTime().getTypeForSimpleTimeZone() + ",\n" + 

				  "\t  " + Time.toFormedString(rr0.getSave()) + "),\n");

			out.write("\t// " + rr0.getLine() + "\n");
			out.write("\t// " + rr1.getLine() + "\n");
		    }

		    String zline = zrec.getLine();
		    if (zline.indexOf("Zone") == -1) {
			zline = "Zone " + key + "\t" + zline.trim();
		    }
		    out.write("\t// " + zline + "\n");
		}
	    }
	    out.write("    };\n");

	    out.close();
	    fw.close();
	} catch(IOException e) {
	    Main.panic("IO error: "+e.getMessage());
	    return 1;
	} 

	return 0;
    }
}
