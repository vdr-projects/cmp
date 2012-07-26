/**
 * ======================== legal notice ======================
 * 
 * File:      MediaTableFormat.java
 * Created:   
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
package de.schwarzrot.cmpc.util;


import ca.odell.glazedlists.gui.TableFormat;
import de.schwarzrot.cmpc.domain.Media;


public class MediaTableFormat implements TableFormat<Media> {
    @Override
    public int getColumnCount() {
        return 2;
    }


    @Override
    public String getColumnName(int column) {
        switch (column) {
        case 0:
            return "Type";
        case 1:
            return "Name";
        default:
            throw new IllegalStateException();
        }
    }


    @Override
    public Object getColumnValue(Media m, int column) {
        switch (column) {
        case 0:
            return m.getType();
        case 1:
            return m.getName();
        default:
            throw new IllegalStateException();
        }
    }
}
