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


import java.awt.Dimension;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import javax.swing.AbstractAction;
import javax.swing.JComponent;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.KeyStroke;
import javax.swing.ListSelectionModel;
import bibliothek.gui.dock.common.CControl;
import bibliothek.gui.dock.common.CGrid;
import bibliothek.gui.dock.common.theme.ThemeMap;
import bibliothek.gui.dock.control.relocator.DockRelocatorEvent;
import bibliothek.gui.dock.control.relocator.VetoableDockRelocatorAdapter;
import bibliothek.gui.dock.util.WindowProvider;
import bibliothek.gui.dock.util.WindowProviderListener;
import ca.odell.glazedlists.BasicEventList;
import ca.odell.glazedlists.EventList;
import ca.odell.glazedlists.swing.DefaultEventTableModel;
import de.schwarzrot.base.dock.BasicDockable;
import de.schwarzrot.base.util.AbstractDialog;
import de.schwarzrot.base.util.ApplicationServiceProvider;
import de.schwarzrot.control.table.PlayerDefinitionTableFormat;
import de.schwarzrot.control.table.ServerDefinitionTableFormat;
import de.schwarzrot.media.domain.AbstractMediaNode;
import de.schwarzrot.media.domain.Config;
import de.schwarzrot.media.domain.MediaServer;
import de.schwarzrot.media.domain.PlayerDefinition;


public class ConfigDialog extends AbstractDialog implements WindowProvider {
    private static final long serialVersionUID = 713L;
    private class TabbedVetoableDockRelocatorListener extends VetoableDockRelocatorAdapter {
        @Override
        public void grabbing(DockRelocatorEvent event) {
            event.forbid();
        }
    }


    public ConfigDialog(Window parent) {
        super(parent, true, DialogMode.CANCEL_APPROVE, Orientation.Right);
        config = ApplicationServiceProvider.getService(Config.class);
        listeners = new ArrayList<WindowProviderListener>();
        setFixedSize(new Dimension(520, 320));
    }


    @Override
    public void addWindowProviderListener(WindowProviderListener windowproviderlistener) {
        if (!listeners.contains(windowproviderlistener))
            listeners.add(windowproviderlistener);
    }


    public JComponent create_Old_ContentPane() {
        JTabbedPane rv = new JTabbedPane();

        rv.addTab("server", createServerTable());
        rv.addTab("player", createPlayerTable());

        return rv;
    }


    @Override
    public JComponent createContentPane() {
        CControl docking = new CControl(this);
        CGrid grid = new CGrid(docking);

        docking.setTheme(ThemeMap.KEY_ECLIPSE_THEME);
        docking.getController().getRelocator()
                .addVetoableDockRelocatorListener(new TabbedVetoableDockRelocatorListener());
        BasicDockable servers = new BasicDockable("servers", msgBundle.getMessage(getClass().getSimpleName()
                + ".servers"), createServerTable());
        BasicDockable players = new BasicDockable("players", msgBundle.getMessage(getClass().getSimpleName()
                + ".players"), createPlayerTable());

        servers.setMinimizable(false);
        servers.setExternalizable(false);
        servers.setMaximizable(false);
        players.setMinimizable(false);
        players.setExternalizable(false);
        players.setMaximizable(false);
        grid.add(0, 0, 1, 1, players);
        grid.add(0, 0, 1, 1, servers);
        docking.getContentArea().deploy(grid);

        return docking.getContentArea();
    }


    @Override
    public void removeWindowProviderListener(WindowProviderListener windowproviderlistener) {
        if (listeners.contains(windowproviderlistener))
            listeners.remove(windowproviderlistener);
    }


    @Override
    public Window searchWindow() {
        return this;
    }


    protected JComponent createPlayerTable() {
        playerDefinitions = new BasicEventList<PlayerDefinition>();
        for (AbstractMediaNode.SupportedMediaType mt : AbstractMediaNode.SupportedMediaType.values()) {
            if (mt == AbstractMediaNode.SupportedMediaType.Unknown)
                break;
            PlayerDefinition pd = (PlayerDefinition) config.getPlayerMap().get(mt).clone(); // so we can revert changes

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
        playerTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        return playerTableScrollPane;
    }


    protected void createServerDefinition() {
        serverDefinitions.add(new MediaServer());
    }


    protected JComponent createServerTable() {
        serverDefinitions = new BasicEventList<MediaServer>();
        for (MediaServer s : config.getKnownServers())
            serverDefinitions.add((MediaServer) s.clone());
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
        serverTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        return serverTableScrollPane;
    }


    @Override
    protected void performApprove() {
        System.out.println("should save config now!?!");
        List<MediaServer> cfgServers = config.getKnownServers();
        AbstractMediaNode.SupportedMediaType[] allTypes = AbstractMediaNode.SupportedMediaType.values();
        Map<AbstractMediaNode.SupportedMediaType, PlayerDefinition> cfgPlayers = config.getPlayerMap();
        int mx = allTypes.length - 1;

        cfgServers.clear();
        cfgServers.addAll(serverDefinitions);
        for (int i = 0; i < mx; ++i)
            cfgPlayers.put(allTypes[i], playerDefinitions.get(i));
    }

    private EventList<MediaServer> serverDefinitions;
    private EventList<PlayerDefinition> playerDefinitions;
    private List<WindowProviderListener> listeners;
    private Config config;
}
