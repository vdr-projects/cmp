/**
 * ======================== legal notice ======================
 * 
 * File:      BasicDockable.java
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
package de.schwarzrot.base.dock;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JComponent;
import javax.swing.JMenuItem;
import bibliothek.gui.dock.common.DefaultSingleCDockable;


public class BasicDockable extends DefaultSingleCDockable {
    public BasicDockable(String id, String title, JComponent content) {
        super(id, title, content);
    }


    public JMenuItem createMenuItem() {
        final JCheckBoxMenuItem item = new JCheckBoxMenuItem(getTitleText(), getTitleIcon());

        item.setSelected(isVisible());
        item.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (item.isSelected())
                    doShow();
                else
                    doClose();
            }
        });
        return item;
    }


    public void doClose() {
        setVisible(false);
    }


    public void doShow() {
        setVisible(true);
    }


    public JComponent getContent() {
        return content;
    }

    private JComponent content;
}
