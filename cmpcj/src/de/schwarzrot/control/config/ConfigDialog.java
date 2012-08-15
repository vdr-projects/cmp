/**
 * ======================== legal notice ======================
 * 
 * File: ConfigDialog.java Created: 13. June 2012, 04:57 Author: <a
 * href="mailto:geronimo013@gmx.de">Geronimo</a> Project: cmpc - a java frontend
 * (client) part of compound media player uses external players to play the
 * media
 * 
 * CMP - compound media player
 * 
 * is a client/server mediaplayer intended to play any media from any
 * workstation without the need to export or mount shares. cmps is an easy to
 * use backend with a (ready to use) HTML-interface. Additionally the backend
 * supports authentication via HTTP-digest authorization. cmpc is a client with
 * vdr-like osd-menues.
 * 
 * Copyright (c) 2012 Reinhard Mantey, some rights reserved! published under
 * Creative Commons by-sa For details see
 * http://creativecommons.org/licenses/by-sa/3.0/
 * 
 * The cmp project's homepage is at
 * http://projects.vdr-developer.org/projects/cmp
 * 
 * --------------------------------------------------------------
 */
package de.schwarzrot.control.config;


import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.util.List;
import javax.swing.AbstractAction;
import javax.swing.JComponent;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.KeyStroke;
import ca.odell.glazedlists.BasicEventList;
import ca.odell.glazedlists.EventList;
import ca.odell.glazedlists.GlazedLists;
import ca.odell.glazedlists.swing.DefaultEventTableModel;
import de.schwarzrot.base.util.AbstractDialog;
import de.schwarzrot.base.util.ApplicationServiceProvider;
import de.schwarzrot.control.table.PlayerDefinitionTableFormat;
import de.schwarzrot.control.table.ServerDefinitionTableFormat;
import de.schwarzrot.media.domain.AbstractMediaNode;
import de.schwarzrot.media.domain.Config;
import de.schwarzrot.media.domain.MediaServer;
import de.schwarzrot.media.domain.PlayerDefinition;


public class ConfigDialog extends AbstractDialog {
    private static final long serialVersionUID = 713L;


    public ConfigDialog(Window parent) {
        super(parent, true, DialogMode.CANCEL_APPROVE, Orientation.Right);
        config = ApplicationServiceProvider.getService(Config.class);
    }


    @Override
    public JComponent createContentPane() {
        JTabbedPane rv = new JTabbedPane();

        rv.addTab("server", createServerTable());
        rv.addTab("player", createPlayerTable());

        return rv;
    }


    protected JComponent createPlayerTable() {
        playerDefinitions = new BasicEventList<PlayerDefinition>();
        for (AbstractMediaNode.SupportedMediaType mt : AbstractMediaNode.SupportedMediaType.values()) {
            if (mt == AbstractMediaNode.SupportedMediaType.Unknown)
                break;
            PlayerDefinition pd = config.getPlayerMap().get(mt);

            pd.setMediaType(mt);
            playerDefinitions.add(pd);
        }
        PlayerDefinitionTableFormat ptf = new PlayerDefinitionTableFormat();
        DefaultEventTableModel<PlayerDefinition> tm = new DefaultEventTableModel<PlayerDefinition>(playerDefinitions,
                ptf);
        JTable playerTable = new JTable(tm);
        JScrollPane playerTableScrollPane = new JScrollPane(playerTable);
        int mx = playerTable.getColumnModel().getColumnCount();

        for (int i = 0; i < mx; ++i) {
            int cw = ptf.getColumnWidth(i);

            if (cw > 0) {
                playerTable.getColumnModel().getColumn(i).setPreferredWidth(cw);
                playerTable.getColumnModel().getColumn(i).setMaxWidth(cw);
            }
        }
        return playerTableScrollPane;
    }


    protected void createServerDefinition() {
        serverDefinitions.add(new MediaServer());
    }


    protected JComponent createServerTable() {
        serverDefinitions = GlazedLists.eventList(config.getKnownServers());
        ServerDefinitionTableFormat stf = new ServerDefinitionTableFormat();
        DefaultEventTableModel<MediaServer> tm = new DefaultEventTableModel<MediaServer>(serverDefinitions, stf);
        JTable serverTable = new JTable(tm);
        JScrollPane serverTableScrollPane = new JScrollPane(serverTable);
        int mx = serverTable.getColumnModel().getColumnCount();

        for (int i = 0; i < mx; ++i) {
            int cw = stf.getColumnWidth(i);

            if (cw > 0) {
                serverTable.getColumnModel().getColumn(i).setPreferredWidth(cw);
                serverTable.getColumnModel().getColumn(i).setMaxWidth(cw);
            }
        }
        serverTable.getActionMap().put("createServerDefinition", new AbstractAction() {
            private static final long serialVersionUID = 1L;


            @Override
            public void actionPerformed(ActionEvent e) {
                createServerDefinition();
            }
        });
        serverTable.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_INSERT, 0), "createServerDefinition");

        return serverTableScrollPane;
    }


    @Override
    protected void performApprove() {
        System.out.println("should save config now!?!");
        List<MediaServer> cfgServers = config.getKnownServers();

        cfgServers.clear();
        cfgServers.addAll(serverDefinitions);
    }

    private EventList<MediaServer> serverDefinitions;
    private EventList<PlayerDefinition> playerDefinitions;
    private Config config;
}
