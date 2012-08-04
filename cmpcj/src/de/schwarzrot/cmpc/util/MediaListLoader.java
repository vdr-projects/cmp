/**
 * ======================== legal notice ======================
 * 
 * File: MediaListLoader.java Created: Author: <a
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
package de.schwarzrot.cmpc.util;


import java.net.ConnectException;
import java.net.URL;
import java.net.URLConnection;
import java.util.Date;
import ca.odell.glazedlists.BasicEventList;
import ca.odell.glazedlists.EventList;
import de.schwarzrot.cmpc.domain.Media;
import de.schwarzrot.cmpc.domain.PlayList;


public class MediaListLoader implements Runnable {
    public EventList<Media> getMediaPool() {
        return mediaPool;
    }


    public void loadMedia(String hostname, int port) {
        this.hostName = hostname;
        this.port = port;

        Thread backgroundThread = new Thread(this);

        backgroundThread.setName("load media list from " + hostName);
        backgroundThread.setDaemon(true);
        backgroundThread.start();
    }


    @Override
    public void run() {
        URL request = null;
        Date start, end;

        try {
            start = new Date();
            request = new URL("http", hostName, port, "/?format=json");
            URLConnection conn = request.openConnection();
            final PlayList firstPlaylist = jsonParser.parseListChunk(conn.getInputStream());

            mediaPool.getReadWriteLock().writeLock().lock();
            for (Media m : firstPlaylist.getResults()) {
                mediaPool.add(m);
            }
            mediaPool.getReadWriteLock().writeLock().unlock();

            end = new Date();
            System.out.println("processing of first playlist-part took " + (end.getTime() - start.getTime()) + " ms.");
            PlayList next;
            long total = firstPlaylist.getTotal();
            long n = firstPlaylist.getResults().size();
            String uri;

            start = new Date();
            try {
                while (n < total) {
                    uri = String.format("/?start=%d&limit=%d&format=json", n, 100);
                    request = new URL("http", hostName, port, uri);
                    conn = request.openConnection();
                    next = jsonParser.parseListChunk(conn.getInputStream());
                    mediaPool.getReadWriteLock().writeLock().lock();
                    for (Media m : next.getResults()) {
                        mediaPool.add(m);
                    }
                    mediaPool.getReadWriteLock().writeLock().unlock();
                    n += next.getResults().size();
                    Thread.sleep(10);
                }
            } catch (Throwable t) {
                System.out.println("Oups, media list contains now #" + mediaPool.size() + " entries.");
                System.err.println("Error on chunk #" + n);
                t.printStackTrace();
            } finally {
                try {
                    mediaPool.getReadWriteLock().writeLock().unlock();
                } catch (Throwable t) {
                }
            }
            end = new Date();
            System.out.println("processing of rest of playlist took " + (end.getTime() - start.getTime()) + " ms.");
        } catch (ConnectException ce) {
            System.out.println("media server " + hostName + " is not available ...");
        } catch (Throwable t) {
            t.printStackTrace();
        } finally {
            try {
                mediaPool.getReadWriteLock().writeLock().unlock();
            } catch (Throwable t) {
            }
        }
    }

    private String hostName;
    private int port;
    private MedialistParser jsonParser = new MedialistParser();
    private EventList<Media> mediaPool = new BasicEventList<Media>();
}
