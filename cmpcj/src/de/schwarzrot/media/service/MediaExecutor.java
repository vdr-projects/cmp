/**
 * ======================== legal notice ======================
 * 
 * File:      MediaExecutor.java
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
package de.schwarzrot.media.service;


import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JTable;
import ca.odell.glazedlists.EventList;
import de.schwarzrot.control.client.MediaClientExecutor;
import de.schwarzrot.media.domain.Media;


public class MediaExecutor extends MouseAdapter {
    public MediaExecutor(JTable table, EventList<Media> list, MediaClientExecutor mce) {
        this.table = table;
        this.list = list;
        executor = mce;
    }


    @Override
    public void mouseClicked(MouseEvent e) {
        if (e.getButton() == MouseEvent.BUTTON1 && e.getClickCount() > 1) {
            int i = table.rowAtPoint(e.getPoint());
            Media m = list.get(i);

            executor.playMedia(m);
        }
    }

    private JTable table;
    private EventList<Media> list;
    private MediaClientExecutor executor;
}
