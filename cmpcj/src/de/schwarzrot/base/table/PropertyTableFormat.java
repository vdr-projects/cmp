/**
 * ======================== legal notice ======================
 * 
 * File:      PropertyTableFormat.java
 * Created:   13. June 2012, 04:57
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   cmpc - a java frontend (client) part of compound media player
 *                   uses external players to play the media
 * 
 * CMP - compound media player
 * 
 * is a client/server mediaplayer intended to play any media from any workstation
 * without the need to export or mount shares. cmps is an easy to use backend
 * with a (ready to use) HTML-interface. Additionally the backend supports
 * authentication via HTTP-digest authorization.
 * cmpc is a client with vdr-like osd-menues.
 * 
 * Copyright (c) 2012 Reinhard Mantey, some rights reserved!
 * published under Creative Commons by-sa
 * For details see http://creativecommons.org/licenses/by-sa/3.0/
 * 
 * The cmp project's homepage is at http://projects.vdr-developer.org/projects/cmp
 * 
 * --------------------------------------------------------------
 */
package de.schwarzrot.base.table;


import java.util.Map;
import java.util.Map.Entry;
import ca.odell.glazedlists.gui.TableFormat;
import de.schwarzrot.base.util.ApplicationServiceProvider;
import de.schwarzrot.base.util.MessageBundle;
import de.schwarzrot.control.app.CMPMessageBundle;


public class PropertyTableFormat implements TableFormat<Map.Entry<String, Object>> {
    private static MessageBundle bundle;


    @Override
    public int getColumnCount() {
        return 2;
    }


    @Override
    public String getColumnName(int column) {
        if (bundle == null)
            bundle = ApplicationServiceProvider.getService(MessageBundle.class);

        switch (column) {
        case 0:
            return bundle.getMessage(CMPMessageBundle.PTF_0);
        case 1:
            return bundle.getMessage(CMPMessageBundle.PTF_1);
        default:
            throw new IndexOutOfBoundsException();
        }
    }


    @Override
    public Object getColumnValue(Entry<String, Object> e, int column) {
        switch (column) {
        case 0:
            return e.getKey();
        case 1:
            return e.getValue();
        default:
            throw new IndexOutOfBoundsException();
        }
    }


    public int getColumnWidth(int column) {
        switch (column) {
        case 0:
            return 100;
        case 1:
            return -1;
        default:
            throw new IndexOutOfBoundsException();
        }
    }
}
