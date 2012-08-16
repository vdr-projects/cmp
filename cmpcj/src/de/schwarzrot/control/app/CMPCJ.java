/**
 * ======================== legal notice ======================
 * 
 * File: MCC.java Created: 13. June 2012, 04:57 Author: <a
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
package de.schwarzrot.control.app;


import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import javax.swing.AbstractAction;
import javax.swing.DropMode;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.KeyStroke;
import javax.swing.UIManager;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeModel;
import bibliothek.gui.dock.common.CControl;
import bibliothek.gui.dock.common.CGrid;
import bibliothek.gui.dock.common.theme.ThemeMap;
import ca.odell.glazedlists.BasicEventList;
import ca.odell.glazedlists.EventList;
import ca.odell.glazedlists.FilterList;
import ca.odell.glazedlists.GlazedLists;
import ca.odell.glazedlists.SortedList;
import ca.odell.glazedlists.event.ListEvent;
import ca.odell.glazedlists.event.ListEventListener;
import ca.odell.glazedlists.swing.DefaultEventSelectionModel;
import ca.odell.glazedlists.swing.DefaultEventTableModel;
import ca.odell.glazedlists.swing.GlazedListsSwing;
import ca.odell.glazedlists.swing.TableComparatorChooser;
import ca.odell.glazedlists.swing.TextComponentMatcherEditor;
import de.schwarzrot.base.dock.BasicDockable;
import de.schwarzrot.base.table.PropertyTableFormat;
import de.schwarzrot.base.util.ActionManager;
import de.schwarzrot.base.util.ApplicationServiceProvider;
import de.schwarzrot.base.util.CallbackDefinition;
import de.schwarzrot.base.util.ImageFactory;
import de.schwarzrot.base.util.MessageBundle;
import de.schwarzrot.base.util.SuccessHandler;
import de.schwarzrot.control.client.CMPClient;
import de.schwarzrot.control.client.MediaClientExecutor;
import de.schwarzrot.control.config.ConfigDialog;
import de.schwarzrot.control.config.ConfigFactory;
import de.schwarzrot.control.dnd.ListSelectionSourceTransferHandler;
import de.schwarzrot.control.dnd.TreeSourceAndDestTransferHandler;
import de.schwarzrot.control.support.MediaTextFilterator;
import de.schwarzrot.control.support.MediaTypeSelector;
import de.schwarzrot.control.support.SelectedMedia;
import de.schwarzrot.control.support.TreeCellEditor;
import de.schwarzrot.control.support.TreeSelectionFilter;
import de.schwarzrot.control.table.MediaTableFormat;
import de.schwarzrot.media.domain.AbstractMediaNode;
import de.schwarzrot.media.domain.Config;
import de.schwarzrot.media.domain.Genre;
import de.schwarzrot.media.domain.Media;
import de.schwarzrot.media.domain.MediaServer;
import de.schwarzrot.media.domain.PlayerDefinition;
import de.schwarzrot.media.service.DataManager;
import de.schwarzrot.media.service.MediaExecutor;
import de.schwarzrot.media.util.ListLoader;
import de.schwarzrot.media.util.MedialistParser;


public class CMPCJ extends WindowAdapter implements PropertyChangeListener, SuccessHandler,
        ListEventListener<AbstractMediaNode>, MediaClientExecutor {
    private static final String PREFFERRED_LOOK_N_FEEL = "Nimbus"; //$NON-NLS-1$
    private static final String USER_HOME = "user.home"; //$NON-NLS-1$
    private static final String DOCKING_CONFIG = "srdocking.conf"; //$NON-NLS-1$
    enum Commands {
        SrvOpen, SrvRefresh, SrvClose, SrvShutdown, TransmitChanges, Preferences, HelpHelp, HelpAbout
    };


    public CMPCJ(String[] args, ConfigFactory configFactory) {
        nodeCache = new HashMap<File, DefaultMutableTreeNode>();
        changes = new BasicEventList<AbstractMediaNode>();
        rootNode = new DefaultMutableTreeNode(setupServices(args, configFactory));
        changes.addListEventListener(this);
    }


    public void createAndShow() {
        @SuppressWarnings("unchecked")
        ActionManager<Commands> am = ApplicationServiceProvider.getService(ActionManager.class);
        MessageBundle mb = ApplicationServiceProvider.getService(MessageBundle.class);

        mediaList = new SortedList<Media>(GlazedListsSwing.swingThreadProxyList(new BasicEventList<Media>()));
        try {
            String lookNFeel = UIManager.getSystemLookAndFeelClassName();

            for (UIManager.LookAndFeelInfo lfi : UIManager.getInstalledLookAndFeels()) {
                if (PREFFERRED_LOOK_N_FEEL.equals(lfi.getName()))
                    lookNFeel = lfi.getClassName();
            }
            UIManager.setLookAndFeel(lookNFeel);
        } catch (Exception e) {
            System.err.println(mb.getMessage(CMPMessageBundle.MCC_6));
        }
        am.addCallbackDefinition(new CallbackDefinition<Commands>(Commands.SrvOpen) {
            private static final long serialVersionUID = 713L;


            @Override
            public void actionPerformed(ActionEvent e) {
                doConnectServer();
            }
        });
        am.addCallbackDefinition(new CallbackDefinition<Commands>(Commands.SrvRefresh, false) {
            private static final long serialVersionUID = 713L;


            @Override
            public void actionPerformed(ActionEvent e) {
                doServerRescan();
            }
        });
        am.addCallbackDefinition(new CallbackDefinition<Commands>(Commands.SrvClose, false) {
            private static final long serialVersionUID = 713L;


            @Override
            public void actionPerformed(ActionEvent e) {
                doDisconnectServer();
            }
        });
        am.addCallbackDefinition(new CallbackDefinition<Commands>(Commands.SrvShutdown, false) {
            private static final long serialVersionUID = 713L;


            @Override
            public void actionPerformed(ActionEvent e) {
                doShutdownServer();
            }
        });
        am.addCallbackDefinition(new CallbackDefinition<Commands>(Commands.TransmitChanges, false) {
            private static final long serialVersionUID = 713L;


            @Override
            public void actionPerformed(ActionEvent e) {
                doTransmitChanges();
            }
        });
        am.addCallbackDefinition(new CallbackDefinition<Commands>(Commands.Preferences) {
            private static final long serialVersionUID = 713L;


            @Override
            public void actionPerformed(ActionEvent e) {
                doConfigureClient();
            }
        });
        am.addCallbackDefinition(new CallbackDefinition<Commands>(Commands.HelpHelp, false) {
            private static final long serialVersionUID = 713L;


            @Override
            public void actionPerformed(ActionEvent e) {
                doShowHelp();
            }
        });
        am.addCallbackDefinition(new CallbackDefinition<Commands>(Commands.HelpAbout) {
            private static final long serialVersionUID = 713L;


            @Override
            public void actionPerformed(ActionEvent e) {
                doShowAbout();
            }
        });
        JMenuBar menuBar = new JMenuBar();
        frame = new JFrame(mb.getMessage(CMPMessageBundle.MCC_7));
        control = new CControl(frame);
        control.setTheme(ThemeMap.KEY_ECLIPSE_THEME);
        frame.addWindowListener(this);
        frame.add(setupPerspective(frame));
        frame.setJMenuBar(menuBar);
        frame.pack();
        frame.setSize(1200, 800);
        frame.setLocationRelativeTo(null);
        restorePerspective();
        createMenu(menuBar);
        frame.setVisible(true);
    }


    @Override
    public void handleFailure(Throwable t) {
        // loading list from server failed ...
        if (t instanceof UnknownHostException) {
            //TODO: tell the user ...
        }
        t.printStackTrace();
        tree.updateUI();
        updateServerActions(false);
    }


    @Override
    public void handleSuccess() {
        // loading list from server was successful
        tree.updateUI();
        updateServerActions(true);
    }


    @Override
    public void listChanged(ListEvent<AbstractMediaNode> arg0) {
        // get rid of changes made by user
        @SuppressWarnings("unchecked")
        ActionManager<Commands> am = ApplicationServiceProvider.getService(ActionManager.class);
        boolean changesExists = changes.size() > 0;

        System.out.println("changes updated ...");
        am.getAction(Commands.TransmitChanges).setEnabled(changesExists);
    }


    @Override
    public void playMedia(Media m) {
        Config config = ApplicationServiceProvider.getService(Config.class);
        List<String> command = new ArrayList<String>();
        PlayerDefinition pd = config.getPlayerMap().get(m.getType());
        StringBuilder sb = new StringBuilder("http://");

        sb.append(clientStub.getServerDefinition().getHostName());
        sb.append(":");
        sb.append(clientStub.getServerDefinition().getPort());
        sb.append(m.getURI());

        command.add(pd.getExecutable());
        for (String param : pd.getParameters()) {
            command.add(param);
        }
        command.add(sb.toString());
        ProcessBuilder pb = new ProcessBuilder(command);

        pb.redirectErrorStream(true);
        try {
            Process proc = pb.start();
            BufferedReader br = new BufferedReader(new InputStreamReader(proc.getInputStream()));
            String line;

            if (config.isDebug()) {
                while ((line = br.readLine()) != null) {
                    System.err.println(line);
                }
            } else {
                while ((line = br.readLine()) != null)
                    ;
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
    }


    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        propertyList.getReadWriteLock().writeLock().lock();
        propertyList.clear();
        if (selectedMedia.getMedia() != null)
            propertyList.addAll(selectedMedia.getMedia().getProperties().entrySet());
        propertyList.getReadWriteLock().writeLock().unlock();
    }


    @Override
    public void windowClosing(WindowEvent e) {
        savePerspective();
        control.destroy();
        System.exit(0);
    }


    @Override
    public void windowOpened(WindowEvent e) {
        doConnectServer();
    }


    protected JComponent createMediaTableView() {
        MessageBundle mb = ApplicationServiceProvider.getService(MessageBundle.class);
        JTextField filterEdit = new JTextField(30);
        mediaTypeSelector = new MediaTypeSelector(mediaList);
        FilterList<Media> typeFilteredMedias = new FilterList<Media>(mediaList, mediaTypeSelector);
        FilterList<Media> filteredMedias = new FilterList<Media>(typeFilteredMedias, new TreeSelectionFilter(tree));
        FilterList<Media> textFilteredMedias = new FilterList<Media>(filteredMedias,
                new TextComponentMatcherEditor<Media>(filterEdit, new MediaTextFilterator()));
        MediaTableFormat mtf = new MediaTableFormat();
        DefaultEventTableModel<Media> mediaTableModel = new DefaultEventTableModel<Media>(textFilteredMedias, mtf);
        selectedMedia = new SelectedMedia(textFilteredMedias);
        DefaultEventSelectionModel<Media> selectionModel = new DefaultEventSelectionModel<Media>(textFilteredMedias);
        JTable mediaJTable = new JTable(mediaTableModel);

        selectedMedia.addPropertyChangeListener(this);
        selectionModel.addListSelectionListener(selectedMedia);
        mediaJTable.setDragEnabled(true);
        mediaJTable.setTransferHandler(new ListSelectionSourceTransferHandler(selectionModel));
        mediaJTable.setSelectionModel(selectionModel);
        mediaJTable.addMouseListener(new MediaExecutor(mediaJTable, textFilteredMedias, this));
        @SuppressWarnings({ "rawtypes", "unused" })
        TableComparatorChooser tableSorter = TableComparatorChooser.install(mediaJTable, mediaList,
                TableComparatorChooser.MULTIPLE_COLUMN_MOUSE_WITH_UNDO);
        JScrollPane mediaTableScrollPane = new JScrollPane(mediaJTable);
        int mx = mediaJTable.getColumnModel().getColumnCount();

        for (int i = 0; i < mx; ++i) {
            int cw = mtf.getColumnWidth(i);

            if (cw > 0)
                mediaJTable.getColumnModel().getColumn(i).setMaxWidth(cw);
        }
        JPanel tablePane = new JPanel();
        JLabel lFilter = new JLabel(mb.getMessage(CMPMessageBundle.MCC_18));

        tablePane.setLayout(new GridBagLayout());
        tablePane.add(lFilter, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER,
                GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
        tablePane.add(filterEdit, new GridBagConstraints(1, 0, 1, 1, 1.0, 0.0, GridBagConstraints.CENTER,
                GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
        tablePane.add(mediaTableScrollPane, new GridBagConstraints(0, 1, 2, 1, 1.0, 1.0, GridBagConstraints.CENTER,
                GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

        return tablePane;
    }


    protected JComponent createMediaTypeList() {
        JPanel rv = new JPanel();

        return rv;
    }


    protected void createMenu(JMenuBar menuBar) {
        MessageBundle mb = ApplicationServiceProvider.getService(MessageBundle.class);
        @SuppressWarnings("unchecked")
        ActionManager<Commands> am = ApplicationServiceProvider.getService(ActionManager.class);
        JMenu mServer = new JMenu(mb.getMessage(CMPMessageBundle.MCC_19));
        JMenu mEdit = new JMenu(mb.getMessage(CMPMessageBundle.MCC_20));
        JMenu mWindow = new JMenu(mb.getMessage(CMPMessageBundle.MCC_21));
        JMenu mHelp = new JMenu(mb.getMessage(CMPMessageBundle.MCC_22));

        mServer.add(new JMenuItem(am.getAction(Commands.SrvOpen)));
        mServer.add(new JMenuItem(am.getAction(Commands.SrvRefresh)));
        mServer.add(new JMenuItem(am.getAction(Commands.SrvClose)));
        mServer.add(new JSeparator());
        mServer.add(new JMenuItem(am.getAction(Commands.SrvShutdown)));
        mEdit.add(new JMenuItem(am.getAction(Commands.TransmitChanges)));
        mEdit.add(new JSeparator());
        mEdit.add(new JMenuItem(am.getAction(Commands.Preferences)));
        mWindow.add(cdGenreTree.createMenuItem());
        mWindow.add(cdMediaTypes.createMenuItem());
        mWindow.add(cdProperties.createMenuItem());
        //TODO: not yet
        //        mHelp.add(new JMenuItem(getAction(Commands.HelpHelp)));
        //        mHelp.add(new JSeparator());
        mHelp.add(new JMenuItem(am.getAction(Commands.HelpAbout)));

        menuBar.add(mServer);
        menuBar.add(mEdit);
        menuBar.add(mWindow);
        menuBar.add(mHelp);
    }


    protected JComponent createPropertyView() {
        if (selectedMedia.getMedia() != null)
            propertyList = GlazedLists.eventList(selectedMedia.getMedia().getProperties().entrySet());
        else
            propertyList = new BasicEventList<Map.Entry<String, Object>>();
        SortedList<Map.Entry<String, Object>> psl = new SortedList<Map.Entry<String, Object>>(propertyList,
                new Comparator<Map.Entry<String, Object>>() {
                    @Override
                    public int compare(Entry<String, Object> a, Entry<String, Object> b) {
                        return a.getKey().compareToIgnoreCase(b.getKey());
                    }
                });
        PropertyTableFormat ptf = new PropertyTableFormat();
        DefaultEventTableModel<Map.Entry<String, Object>> tm = new DefaultEventTableModel<Map.Entry<String, Object>>(
                psl, ptf);
        JTable propertyTable = new JTable(tm);
        JScrollPane psp = new JScrollPane(propertyTable);
        int mx = propertyTable.getColumnModel().getColumnCount();

        for (int i = 0; i < mx; ++i) {
            int cw = ptf.getColumnWidth(i);

            if (cw > 0)
                propertyTable.getColumnModel().getColumn(i).setMaxWidth(cw);
        }
        return psp;
    }


    protected JComponent createTreeView() {
        TreeModel tm = new DefaultTreeModel(rootNode);
        tree = new JTree(tm);
        tree.setDragEnabled(true);
        tree.setEditable(true);
        tree.getActionMap().put("removeGenre", new AbstractAction() { //$NON-NLS-1$
                    private static final long serialVersionUID = 713L;


                    @Override
                    public void actionPerformed(ActionEvent e) {
                        doRemoveGenre();
                    }
                });
        tree.getActionMap().put("createGenre", new AbstractAction() { //$NON-NLS-1$
                    private static final long serialVersionUID = 713L;


                    @Override
                    public void actionPerformed(ActionEvent e) {
                        doCreateGenre();
                    }
                });
        tree.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_DELETE, 0), "removeGenre"); //$NON-NLS-1$
        tree.getInputMap().put(KeyStroke.getKeyStroke(KeyEvent.VK_INSERT, 0), "createGenre"); //$NON-NLS-1$
        tree.setTransferHandler(new TreeSourceAndDestTransferHandler(tree, nodeCache, changes));
        tree.setDropMode(DropMode.USE_SELECTION);
        tree.setCellEditor(new TreeCellEditor(tree, changes));
        JScrollPane treeView = new JScrollPane(tree);

        return treeView;
    }


    protected void doConfigureClient() {
        ConfigDialog cd = new ConfigDialog(frame);

        cd.showDialog(frame);
    }


    protected void doConnectServer() {
        MessageBundle mb = ApplicationServiceProvider.getService(MessageBundle.class);
        Config config = ApplicationServiceProvider.getService(Config.class);
        Object ms = JOptionPane.showInputDialog(frame, mb.getMessage(CMPMessageBundle.MCC_12), mb
                .getMessage(CMPMessageBundle.MCC_13), JOptionPane.PLAIN_MESSAGE, null, config.getKnownServers()
                .toArray(), mb.getMessage(CMPMessageBundle.MCC_14));

        if (ms instanceof MediaServer) {
            System.out.println(mb.getMessage(CMPMessageBundle.MCC_15) + ((MediaServer) ms).getHostName()
                    + mb.getMessage(CMPMessageBundle.MCC_16) + ((MediaServer) ms).getPort());

            clientStub = new CMPClient((MediaServer) ms);
            ApplicationServiceProvider.registerService(ListLoader.class, clientStub);
            DataManager dm = ApplicationServiceProvider.getService(DataManager.class);

            dm.load(rootNode, mediaList, this);
        }
    }


    // respond to tree action
    protected void doCreateGenre() {
        MessageBundle mb = ApplicationServiceProvider.getService(MessageBundle.class);

        System.out.println(mb.getMessage(CMPMessageBundle.MCC_17));

        //TODO: ask user for genre name and create node and cache entries
        tree.updateUI();
    };


    protected void doDisconnectServer() {
        ApplicationServiceProvider.registerService(MediaServer.class, null);
        mediaList.getReadWriteLock().writeLock().lock();
        mediaList.clear();
        mediaList.getReadWriteLock().writeLock().unlock();
        ((DefaultMutableTreeNode) tree.getModel().getRoot()).removeAllChildren();
        tree.updateUI();
        selectedMedia.clear();
        updateServerActions(false);
        clientStub = null;
    }


    // respond to tree action
    protected void doRemoveGenre() {
        MessageBundle mb = ApplicationServiceProvider.getService(MessageBundle.class);

        System.out.println(mb.getMessage(CMPMessageBundle.MCC_0));
        DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getSelectionPath().getLastPathComponent();
        if (node == null)
            return;
        Genre g = (Genre) node.getUserObject();

        if (g.getMediaList().size() > 0 || g.getChildren().size() > 0) {
            //TODO: ask user and/or pop some warning
        } else {
            nodeCache.remove(g.getRealPath());
            ((DefaultMutableTreeNode) node.getParent()).remove(node);
            tree.updateUI();
        }
    }


    protected void doServerRescan() {
        clientStub.execServerRescan();
    }


    protected void doShowAbout() {
        AboutDialog dlgAbout = new AboutDialog(frame);

        dlgAbout.showDialog(frame);
    }


    protected void doShowHelp() {
    }


    protected void doShutdownServer() {
        clientStub.execServerShutdown();
        doDisconnectServer();
    }


    protected void doTransmitChanges() {
        clientStub.transmitChanges(changes);
    }


    protected void restoreAppStatus() {
        Config config = ApplicationServiceProvider.getService(Config.class);

        try {
            if (config != null) {
                if (config.getMainWidth() > 0 && config.getMainHeight() > 0)
                    frame.setSize(config.getMainWidth(), config.getMainHeight());

                if (config.getPosX() > 0 || config.getPosY() > 0)
                    frame.setLocation(config.getPosX(), config.getPosY());
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
    }


    protected void restorePerspective() {
        File dockableSettings = new File(configDirectory, DOCKING_CONFIG);

        try {
            if (dockableSettings.exists() && dockableSettings.canRead())
                control.getResources().readFile(dockableSettings);
        } catch (Throwable t) {
            t.printStackTrace();
        }
        restoreAppStatus();
    }


    protected void saveAppStatus() {
        Config config = ApplicationServiceProvider.getService(Config.class);
        ConfigFactory cf = ApplicationServiceProvider.getService(ConfigFactory.class);

        try {
            Dimension mainDim = frame.getSize();
            Point mainPos = frame.getLocation();

            config.setMainWidth(mainDim.width);
            config.setMainHeight(mainDim.height);
            config.setPosX(mainPos.x);
            config.setPosY(mainPos.y);

            cf.putConfig(config);
        } catch (Throwable t) {
            t.printStackTrace();
        }
    }


    protected void savePerspective() {
        File dockableSettings = new File(configDirectory, DOCKING_CONFIG);

        try {
            if (!dockableSettings.exists())
                dockableSettings.getParentFile().mkdirs();
            control.getResources().writeFile(dockableSettings);
        } catch (Throwable t) {
            t.printStackTrace();
        }
        saveAppStatus();
    }


    protected JComponent setupPerspective(JFrame frame) {
        MessageBundle mb = ApplicationServiceProvider.getService(MessageBundle.class);

        cdGenreTree = new BasicDockable("genreTree", mb.getMessage(CMPMessageBundle.MCC_29), createTreeView()); //$NON-NLS-1$ 
        cdMediaList = new BasicDockable("mediaList", mb.getMessage(CMPMessageBundle.MCC_31), createMediaTableView()); //$NON-NLS-1$ 
        cdMediaTypes = new BasicDockable(
                "mediaTypes", mb.getMessage(CMPMessageBundle.MCC_33), mediaTypeSelector.getComponent()); //$NON-NLS-1$ 
        cdProperties = new BasicDockable("properties", mb.getMessage(CMPMessageBundle.MCC_35), createPropertyView()); //$NON-NLS-1$ 
        CGrid grid = new CGrid(control);

        grid.add(0, 0, 1, 2, cdGenreTree);
        grid.add(1, 0, 1, 1, cdMediaList);
        grid.add(2, 0, 1, 2, cdMediaTypes);
        grid.add(1, 1, 1, 1, cdProperties);

        cdMediaList.setStackable(false);
        cdMediaList.setExternalizable(false);
        cdMediaList.setMinimizable(false);
        control.getContentArea().deploy(grid);

        return control.getContentArea();
    }


    protected Genre setupServices(String[] args, ConfigFactory configFactory) {
        MessageBundle mb = new CMPMessageBundle();
        configDirectory = configFactory.getConfigDirectory();
        ApplicationServiceProvider.registerService(Config.class, configFactory.getConfig());
        ApplicationServiceProvider.registerService(ConfigFactory.class, configFactory);
        ApplicationServiceProvider.registerService(MessageBundle.class, mb);
        if (args.length > 0) {
            File tmp = new File(args[0]);

            if (tmp.exists() && tmp.canRead()) {
                System.out.println(mb.getMessage(CMPMessageBundle.MCC_4) + " " + tmp.getAbsolutePath()
                        + mb.getMessage(CMPMessageBundle.MCC_5));

                input = tmp;
            }
        }
        ApplicationServiceProvider.registerService(ActionManager.class, new ActionManager<Commands>());
        ApplicationServiceProvider.registerService(DataManager.class, new DataManager(input, nodeCache));
        ApplicationServiceProvider.registerService(ImageFactory.class, new ImageFactory());
        ApplicationServiceProvider.registerService(MedialistParser.class, new MedialistParser());

        File base = new File("/"); //$NON-NLS-1$
        Genre root = new Genre(base);

        //        ApplicationServiceProvider.registerService(FilesystemListLoader.class, new FilesystemListLoader(base));

        return root;
    }


    protected void updateServerActions(boolean connected) {
        @SuppressWarnings("unchecked")
        ActionManager<Commands> am = ApplicationServiceProvider.getService(ActionManager.class);

        am.getAction(Commands.SrvOpen).setEnabled(!connected);
        am.getAction(Commands.SrvClose).setEnabled(connected);
        am.getAction(Commands.SrvRefresh).setEnabled(connected);
        am.getAction(Commands.SrvShutdown).setEnabled(connected);
    }


    public static void main(final String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                File configDir = new File(System.getProperty(USER_HOME), ".cmp"); //$NON-NLS-1$
                CMPCJ app = new CMPCJ(args, new ConfigFactory(configDir, "CMPCJ"));

                app.createAndShow();
            }
        });
    }

    private DefaultMutableTreeNode rootNode;
    private SortedList<Media> mediaList;
    private SelectedMedia selectedMedia;
    private EventList<AbstractMediaNode> changes;
    private Map<File, DefaultMutableTreeNode> nodeCache;
    private EventList<Map.Entry<String, Object>> propertyList;
    private MediaTypeSelector mediaTypeSelector;
    private CMPClient clientStub;
    private CControl control;
    private JFrame frame;
    private BasicDockable cdMediaList;
    private BasicDockable cdGenreTree;
    private BasicDockable cdMediaTypes;
    private BasicDockable cdProperties;
    private File configDirectory;
    private JTree tree;
    private File input;
}
