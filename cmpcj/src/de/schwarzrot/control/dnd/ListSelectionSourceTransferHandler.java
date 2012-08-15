/**
 * ======================== legal notice ======================
 * 
 * File:      ListSelectionSourceTransferHandler.java
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
package de.schwarzrot.control.dnd;


import java.awt.datatransfer.Transferable;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JComponent;
import javax.swing.TransferHandler;
import ca.odell.glazedlists.EventList;
import ca.odell.glazedlists.swing.DefaultEventSelectionModel;
import de.schwarzrot.media.domain.Media;


public class ListSelectionSourceTransferHandler extends TransferHandler {
    private static final long serialVersionUID = 713L;


    public ListSelectionSourceTransferHandler(DefaultEventSelectionModel<Media> selectionModel) {
        sm = selectionModel;
    }


    @Override
    public Transferable createTransferable(JComponent c) {
        if (sm.isSelectionEmpty())
            return null;
        EventList<Media> selection = sm.getSelected();
        List<File> transferList = new ArrayList<File>();

        for (Media m : selection) {
            transferList.add(m.getRealPath());
        }
        return new FilelistTransferable(transferList);
    }


    @Override
    public int getSourceActions(JComponent c) {
        return TransferHandler.LINK;
    }

    private DefaultEventSelectionModel<Media> sm;
}
