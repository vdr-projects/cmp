/**
 * ======================== legal notice ======================
 * 
 * File:      MediaClient.java
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


import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableCellRenderer;
import ca.odell.glazedlists.EventList;
import ca.odell.glazedlists.FilterList;
import ca.odell.glazedlists.SortedList;
import ca.odell.glazedlists.swing.DefaultEventTableModel;
import ca.odell.glazedlists.swing.GlazedListsSwing;
import ca.odell.glazedlists.swing.TableComparatorChooser;
import ca.odell.glazedlists.swing.TextComponentMatcherEditor;
import de.schwarzrot.cmpc.app.IMediaPlayer;
import de.schwarzrot.cmpc.domain.Media;
import de.schwarzrot.cmpc.domain.PlayerDefinition;
import de.schwarzrot.cmpc.util.MediaClientExecutor;
import de.schwarzrot.cmpc.util.MediaComparator;
import de.schwarzrot.cmpc.util.MediaExecutor;
import de.schwarzrot.cmpc.util.MediaListLoader;
import de.schwarzrot.cmpc.util.MediaTableFormat;
import de.schwarzrot.cmpc.util.MediaTextFilterator;
import de.schwarzrot.cmpc.util.MediaTypeSelect;


public class MediaClient extends JComponent implements MediaClientExecutor {
    private static final long serialVersionUID = 713L;


    public MediaClient(String id, IMediaPlayer player) {
        this.myPanelName = id;
        this.player = player;
        setLayout(new BorderLayout());
        listLoader = new MediaListLoader();
        mediaPool = listLoader.getMediaPool();
    }


    @Override
    public String getName() {
        return myPanelName;
    }


    public boolean isActive() {
        return active;
    }


    @Override
    public void playMedia(Media m) {
        List<String> command = new ArrayList<String>();
        PlayerDefinition pd = player.getConfig().getPlayerMap().get(m.getType());
        StringBuilder sb = new StringBuilder("http://");

        sb.append(curHostName);
        sb.append(":");
        sb.append(curPort);
        sb.append(m.getPath());

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

            if (player.isDebug()) {
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


    public void setActive(boolean active) {
        this.active = active;
    }


    public void setup(final IMediaPlayer mp) {
        add(createClientPane(), BorderLayout.CENTER);
    }


    public void startConnection(String hostname, int port) {
        setHost(hostname);
        setPort(port);
        mediaPool.getReadWriteLock().writeLock().lock();
        mediaPool.clear();
        mediaPool.getReadWriteLock().writeLock().unlock();
        listLoader.loadMedia(curHostName, curPort);
    }


    protected JComponent createClientPane() {
        JPanel clientPane = new JPanel();

        loadImages();
        mediaPool.getReadWriteLock().readLock().lock();
        try {
            SortedList<Media> sortedMedias = new SortedList<Media>(GlazedListsSwing.swingThreadProxyList(mediaPool),
                    new MediaComparator());
            MediaTypeSelect mtSelect = new MediaTypeSelect(sortedMedias);
            FilterList<Media> filteredMedias = new FilterList<Media>(sortedMedias, mtSelect);
            JTextField filterEdit = new JTextField(30);
            FilterList<Media> textFilteredMedia = new FilterList<Media>(filteredMedias,
                    new TextComponentMatcherEditor<Media>(filterEdit, new MediaTextFilterator()));
            DefaultEventTableModel<Media> mediaTableModel = new DefaultEventTableModel<Media>(textFilteredMedia,
                    new MediaTableFormat());
            JTable mediaJTable = new JTable(mediaTableModel);
            @SuppressWarnings({ "unused", "rawtypes" })
            TableComparatorChooser tableSorter = TableComparatorChooser.install(mediaJTable, sortedMedias,
                    TableComparatorChooser.MULTIPLE_COLUMN_MOUSE_WITH_UNDO);
            JScrollPane mediaTableScrollPane = new JScrollPane(mediaJTable);
            JScrollPane mediaTypesScrollPane = new JScrollPane(mtSelect.getJList());
            JLabel filter = new JLabel(" Filter: ");
            JButton exitButton = new JButton(images[0]);
            JButton preferences = new JButton(images[1]);

            filter.setForeground(Color.GRAY);
            filterEdit.setBackground(Color.LIGHT_GRAY);
            exitButton.setBackground(Color.BLACK);
            preferences.setBackground(Color.BLACK);
            exitButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    player.selectApp();
                }
            });
            mediaTypesScrollPane.setPreferredSize(new Dimension(100, 100));
            mediaTypesScrollPane.setBackground(Color.BLACK);
            mediaJTable.getColumnModel().getColumn(0).setMaxWidth(80);
            mediaJTable.getColumnModel().getColumn(0).setCellRenderer(new DefaultTableCellRenderer());
            mediaJTable.getColumnModel().getColumn(1).setCellRenderer(new DefaultTableCellRenderer());
            mediaJTable.addMouseListener(new MediaExecutor(mediaJTable, textFilteredMedia, this));
            clientPane.setLayout(new GridBagLayout());

            clientPane.add(exitButton, new GridBagConstraints(0, 0, 1, 2, 0.0, 0.0, GridBagConstraints.CENTER,
                    GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
            clientPane.add(preferences, new GridBagConstraints(1, 0, 1, 2, 0.0, 0.0, GridBagConstraints.CENTER,
                    GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

            clientPane.add(mediaTypesScrollPane, new GridBagConstraints(0, 2, 2, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

            clientPane.add(filter, new GridBagConstraints(2, 0, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER,
                    GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 10, 0));

            clientPane.add(filterEdit, new GridBagConstraints(3, 0, 1, 1, 1.0, 0.0, GridBagConstraints.CENTER,
                    GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

            clientPane.add(mediaTableScrollPane, new GridBagConstraints(2, 1, 2, 2, 1.0, 1.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
            clientPane.setOpaque(true);
            clientPane.setBackground(Color.BLACK);
        } finally {
            mediaPool.getReadWriteLock().readLock().unlock();
        }
        return clientPane;
    }


    protected void loadImages() {
        BufferedImage img = null;
        ClassLoader cl = getClass().getClassLoader();
        URL url;

        images = new ImageIcon[iconFiles.length];
        for (int i = 0; i < iconFiles.length; ++i) {
            try {
                url = cl.getResource(iconFiles[i]);

                img = ImageIO.read(url);
                images[i] = new ImageIcon(img.getScaledInstance(64, 64, Image.SCALE_SMOOTH));
            } catch (Throwable t) {
                System.err.println("failed to read image from " + iconFiles[i]);
                t.printStackTrace();
            }
        }
    }


    protected void setHost(String hostname) {
        curHostName = hostname;
    }


    protected void setPort(Integer port) {
        curPort = port;
    }

    private IMediaPlayer player;
    private MediaListLoader listLoader;
    private EventList<Media> mediaPool;
    private String myPanelName;
    private int curPort;
    private String curHostName;
    private boolean active;
    private ImageIcon[] images;
    private static final String[] iconFiles;
    static {
        iconFiles = new String[] { "images/black_exit.png", "images/black_preferences.png" };
    }
}
