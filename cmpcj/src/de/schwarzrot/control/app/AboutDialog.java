/**
 * ======================== legal notice ======================
 * 
 * File:      AboutDialog.java
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
package de.schwarzrot.control.app;


import java.awt.Dimension;
import java.awt.Window;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import de.schwarzrot.base.util.AbstractDialog;


public class AboutDialog extends AbstractDialog {
    private static final long serialVersionUID = 713L;


    public AboutDialog(Window parent) {
        super(parent, true, DialogMode.CLOSE, Orientation.Center);
    }


    @Override
    public JComponent createContentPane() {
        JPanel rv = new JPanel();

        rv.setLayout(new BoxLayout(rv, BoxLayout.Y_AXIS));
        rv.setBorder(new EmptyBorder(20, 20, 20, 20));
        JLabel appInfo = new JLabel(msgBundle.getMessage(getClass().getSimpleName() + ".app.info"), JLabel.CENTER);

        rv.add(appInfo);
        JLabel aboutText = new JLabel(msgBundle.getMessage(getClass().getSimpleName() + ".about.text"), JLabel.CENTER);

        rv.add(aboutText);
        rv.add(Box.createRigidArea(new Dimension(0, 30)));
        JLabel contribution = new JLabel(msgBundle.getMessage(getClass().getSimpleName() + ".contribution"),
                JLabel.LEFT);

        rv.add(contribution);

        return rv;
    }
}
