/**
 * ======================== legal notice ======================
 * 
 * File:      TreePathTransferable.java
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


import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;
import javax.swing.tree.TreePath;


public class TreePathTransferable implements Transferable {
    public static final DataFlavor TreePathFlavor;


    public TreePathTransferable(TreePath path) {
        data = path;
    }


    @Override
    public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
        if (TreePathFlavor.equals(flavor))
            return data;
        throw new UnsupportedFlavorException(flavor);
    }


    @Override
    public DataFlavor[] getTransferDataFlavors() {
        return new DataFlavor[] { TreePathFlavor };
    }


    @Override
    public boolean isDataFlavorSupported(DataFlavor flavor) {
        return TreePathFlavor.equals(flavor);
    }

    private TreePath data;
    static {
        DataFlavor tmp = null;

        try {
            tmp = new DataFlavor(DataFlavor.javaJVMLocalObjectMimeType + ";class=" + TreePath.class.getName());
        } catch (ClassNotFoundException e) {
        }
        TreePathFlavor = tmp;
    }
}
