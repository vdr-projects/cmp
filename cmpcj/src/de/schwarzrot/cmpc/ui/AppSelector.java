/**
 * ======================== legal notice ======================
 * 
 * File:      AppSelector.java
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
package de.schwarzrot.cmpc.ui;


import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.util.List;
import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JPanel;
import de.schwarzrot.cmpc.app.IMediaPlayer;
import de.schwarzrot.cmpc.domain.MediaServer;


public class AppSelector extends JComponent {
    private static final long serialVersionUID = 713L;


    public AppSelector(String id, List<MediaServer> mediaServerHosts) {
        this.myPanelName = id;
        this.knownMediaCenters = mediaServerHosts;
    }


    @Override
    public String getName() {
        return myPanelName;
    }


    public void setup(final IMediaPlayer mp) {
        setLayout(new GridLayout(1, 2));
        JPanel knownHosts = new JPanel();

        knownHosts.setLayout(new GridLayout(knownMediaCenters.size(), 1));
        for (MediaServer ms : knownMediaCenters) {
            JButton bt = new JButton(ms.getHostName());
            AbstractAction a = new AbstractAction() {
                private static final long serialVersionUID = 713L;


                @Override
                public void actionPerformed(ActionEvent e) {
                    String host = (String) this.getValue("mediaCenterHost");
                    Integer port = (Integer) this.getValue("mediaCenterPort");

                    System.out.println("shall connect " + host + ":" + port);
                    mp.startApp(host, port);
                }
            };
            a.putValue("mediaCenterHost", ms.getHostName());
            a.putValue("mediaCenterPort", ms.getPort());
            bt.addActionListener(a);
            knownHosts.add(bt);
        }
        add(knownHosts);
        JButton setup = new JButton("Setup");

        add(setup);
        doLayout();
    }

    private String myPanelName;
    private List<MediaServer> knownMediaCenters;
}
