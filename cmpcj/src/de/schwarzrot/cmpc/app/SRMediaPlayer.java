/**
 * ======================== legal notice ======================
 * 
 * File: SRMediaPlayer.java Created: Author: <a
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
package de.schwarzrot.cmpc.app;


import java.awt.CardLayout;
import java.awt.Container;
import java.io.File;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;
import de.schwarzrot.cmpc.domain.Config;
import de.schwarzrot.cmpc.ui.AppSelector;
import de.schwarzrot.cmpc.ui.MediaClient;


public class SRMediaPlayer implements IMediaPlayer {
    private static final String DEFAULT_TITLE = "client";
    private static final String USER_HOME = "user.home";
    private static final String TITLE_MASK = "Compound Media Player (%s)";
    private static final String MAIN = "MediaServerSelector";
    private static final String CLIENT = "MediaClient";


    public SRMediaPlayer(String[] args, ConfigFactory cf) {
        for (String a : args) {
            if (a.compareTo("-d") == 0 || a.compareTo("--debug") == 0)
                debug = true;
        }
        configFactory = cf;
    }


    public void createAndShowGUI() {
        JFrame.setDefaultLookAndFeelDecorated(false);

        config = configFactory.getConfig();
        try {
            for (LookAndFeelInfo lfi : UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(lfi.getName())) {
                    UIManager.setLookAndFeel(lfi.getClassName());
                    JFrame.setDefaultLookAndFeelDecorated(true);
                }
            }
        } catch (Throwable t) {
            t.printStackTrace();
            System.exit(-1);
        }
        mainFrame = new JFrame("JMediaPlayer");

        //Add components to it.
        Container contentPane = mainFrame.getContentPane();
        setupMainView(contentPane);

        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle(DEFAULT_TITLE);
        mainFrame.setSize(1000, 700);
        mainFrame.setLocationRelativeTo(null); //center it
        mainFrame.setVisible(true);
    }


    @Override
    public Config getConfig() {
        return config;
    }


    public ConfigFactory getConfigFactory() {
        return configFactory;
    }


    @Override
    public String getCurrentMediaCenter() {
        return currentMediaCenter;
    }


    @Override
    public boolean isDebug() {
        return debug;
    }


    @Override
    public void selectApp() {
        setTitle(DEFAULT_TITLE);
        switchView(MAIN);
    }


    public void setConfigFactory(ConfigFactory configFactory) {
        this.configFactory = configFactory;
    }


    @Override
    public void startApp(String name, int port) {
        currentMediaCenter = name;
        setTitle(name);
        switchView(CLIENT);
        try {
            mediaClientPane.startConnection(name, port);
        } catch (Throwable t) {
            mediaClientPane.setActive(false);
            switchView(MAIN);
        }
    }


    protected void setTitle(String title) {
        mainFrame.setTitle(String.format(TITLE_MASK, title));
    }


    protected void setupMainView(Container clientArea) {
        stakker = new CardLayout();
        switchingPane = new JPanel(stakker);
        mediaClientPane = new MediaClient(CLIENT, this);
        appSelectorPane = new AppSelector(MAIN, config.getKnownServers());

        mediaClientPane.setup(this);
        appSelectorPane.setup(this);

        switchingPane.add(appSelectorPane, MAIN);
        switchingPane.add(mediaClientPane, CLIENT);
        clientArea.add(switchingPane);
    }


    protected void switchView(String name) {
        stakker.show(switchingPane, name);
    }


    public static void main(final String[] args) {
        appInfo();
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                File configDir = new File(System.getProperty(USER_HOME), ".cmp");
                SRMediaPlayer app = new SRMediaPlayer(args, new ConfigFactory(configDir));
                app.createAndShowGUI();
            }
        });
    }


    protected static void appInfo() {
        System.err.println("cmpcj - the java frontend of CMP (compound media player)");
        System.err.println(" serves to browse a medialist from remote systems and to start a player");
        System.err.println(" for selected media.");
        System.err.println(" (c) 2012 - Reinhard Mantey - some rights reserved.");
        System.err.println(" CMP is published as open source under Creative Commons by-sa");
    }
    private boolean debug = false;
    private JFrame mainFrame;
    private Config config;
    private CardLayout stakker;
    private JPanel switchingPane;
    private MediaClient mediaClientPane;
    private AppSelector appSelectorPane;
    private ConfigFactory configFactory;
    private String currentMediaCenter;
}
