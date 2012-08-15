/**
 * ======================== legal notice ======================
 * 
 * File:      MediaTableFormat.java
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
package de.schwarzrot.control.table;


import ca.odell.glazedlists.gui.TableFormat;
import de.schwarzrot.base.util.ApplicationServiceProvider;
import de.schwarzrot.base.util.MessageBundle;
import de.schwarzrot.control.app.CMPMessageBundle;
import de.schwarzrot.media.domain.Media;


public class MediaTableFormat implements TableFormat<Media> {
    private static MessageBundle bundle;


    @Override
    public int getColumnCount() {
        return 3;
    }


    @Override
    public String getColumnName(int column) {
        if (bundle == null)
            bundle = ApplicationServiceProvider.getService(MessageBundle.class);

        switch (column) {
        case 0:
            return bundle.getMessage(CMPMessageBundle.MTF_0);
        case 1:
            return bundle.getMessage(CMPMessageBundle.MTF_1);
        case 2:
            return bundle.getMessage(CMPMessageBundle.MTF_2);
        default:
            throw new IndexOutOfBoundsException();
        }
    }


    @Override
    public Object getColumnValue(Media m, int column) {
        switch (column) {
        case 0:
            return m.getType();
        case 1:
            return m.getFormat();
        case 2:
            return m.getName();
        default:
            throw new IndexOutOfBoundsException();
        }
    }


    public int getColumnWidth(int column) {
        switch (column) {
        case 0:
            return 80;
        case 1:
            return 110;
        case 2:
            return -1;
        default:
            throw new IndexOutOfBoundsException();
        }
    }
}
