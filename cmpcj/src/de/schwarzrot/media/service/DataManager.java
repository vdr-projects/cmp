/**
 * ======================== legal notice ======================
 * 
 * File:      DataManager.java
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
package de.schwarzrot.media.service;


import java.io.File;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;
import javax.swing.SwingUtilities;
import javax.swing.tree.DefaultMutableTreeNode;
import ca.odell.glazedlists.EventList;
import de.schwarzrot.base.util.ApplicationServiceProvider;
import de.schwarzrot.base.util.SuccessHandler;
import de.schwarzrot.media.domain.AbstractMediaNode;
import de.schwarzrot.media.domain.Genre;
import de.schwarzrot.media.domain.Media;
import de.schwarzrot.media.util.ElementConsumer;
import de.schwarzrot.media.util.ListLoader;


public class DataManager implements Runnable, ElementConsumer<Media> {
    public DataManager(File input) {
        this.input = input;
        nodeCache = new HashMap<File, DefaultMutableTreeNode>();
    }


    @Override
    public void consumeElement(Media m) {
        if (m.getParent() == null)
            m.setParent(getGenre(m.getRealPath().getParentFile()));

        mediaList.getReadWriteLock().writeLock().lock();
        mediaList.add(m);
        mediaList.getReadWriteLock().writeLock().unlock();
    }


    public void load(DefaultMutableTreeNode root, EventList<Media> mediaList, SuccessHandler successHandler) {
        Thread backgroundThread = new Thread(this);

        nodeCache.clear();
        resultHandler = successHandler;
        rootNode = root;
        nodeCache.put(new File("/"), rootNode);
        this.mediaList = mediaList;
        backgroundThread.setName("load media list");
        backgroundThread.setDaemon(true);
        backgroundThread.start();
    }


    @Override
    public void run() {
        @SuppressWarnings("unchecked")
        ListLoader<Media> ll = ApplicationServiceProvider.getService(ListLoader.class);

        try {
            long[] info = ll.loadFirst(this);
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    resultHandler.handleSuccess(); // feedback to main thread
                }
            });
            ll.loadRest(info, this);
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    resultHandler.handleSuccess(); // feedback to main thread
                }
            });
        } catch (final Throwable t) {
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    resultHandler.handleFailure(t); // feedback to main thread
                }
            });
        }
    }


    protected void createGenre(File path) {
        File tmp = path;
        Stack<File> unknownGenres = new Stack<File>();

        while (tmp != null && !nodeCache.containsKey(tmp)) {
            unknownGenres.push(tmp);
            tmp = tmp.getParentFile();
        }
        DefaultMutableTreeNode treeNode = tmp == null ? rootNode : nodeCache.get(tmp);
        AbstractMediaNode media = (AbstractMediaNode) treeNode.getUserObject();
        DefaultMutableTreeNode subNode = null;
        Genre g = null;

        if (media != null && media instanceof Genre)
            g = (Genre) media;

        while (unknownGenres.size() > 0) {
            tmp = unknownGenres.pop();
            g = new Genre(g, tmp);
            subNode = new DefaultMutableTreeNode(g);
            nodeCache.put(tmp, subNode);
            treeNode.add(subNode);
            treeNode = subNode;
        }
    }


    protected Genre getGenre(File path) {
        if (!nodeCache.containsKey(path))
            createGenre(path);
        DefaultMutableTreeNode n = nodeCache.get(path);
        AbstractMediaNode rv = (AbstractMediaNode) n.getUserObject();

        if (rv instanceof Genre)
            return (Genre) rv;
        return null;
    }

    @SuppressWarnings("unused")
    private File input;
    private SuccessHandler resultHandler;
    private DefaultMutableTreeNode rootNode;
    private EventList<Media> mediaList;
    private Map<File, DefaultMutableTreeNode> nodeCache;
}
