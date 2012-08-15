/**
 * ======================== legal notice ======================
 * 
 * File:      CMPClient.java
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
package de.schwarzrot.control.client;


import java.net.ConnectException;
import java.net.URL;
import java.net.URLConnection;
import java.net.UnknownHostException;
import java.util.Date;
import ca.odell.glazedlists.EventList;
import de.schwarzrot.base.util.ApplicationServiceProvider;
import de.schwarzrot.media.domain.AbstractMediaNode;
import de.schwarzrot.media.domain.Media;
import de.schwarzrot.media.domain.MediaServer;
import de.schwarzrot.media.domain.PlayList;
import de.schwarzrot.media.util.ElementConsumer;
import de.schwarzrot.media.util.ListLoader;
import de.schwarzrot.media.util.MedialistParser;


public class CMPClient implements ListLoader<Media> {
    public CMPClient(MediaServer serverDefinition) {
        server = serverDefinition;
    }


    public void execServerRescan() {
        try {
            URL request = new URL("http", server.getHostName(), server.getPort(), "/refresh");
            URLConnection conn = request.openConnection();

            conn.connect();
            conn.getContentLength();
        } catch (Throwable t) {
            throw new RuntimeException(t);
        }
    }


    public void execServerShutdown() {
        try {
            URL request = new URL("http", server.getHostName(), server.getPort(), "/stop");
            URLConnection conn = request.openConnection();

            conn.connect();
            conn.getContentLength();
        } catch (Throwable t) {
            throw new RuntimeException(t);
        }
    }


    public MediaServer getServerDefinition() {
        return server;
    }


    @Override
    public long[] loadFirst(ElementConsumer<Media> consumer) {
        MedialistParser jsonParser = ApplicationServiceProvider.getService(MedialistParser.class);
        URL request = null;
        Date start, end;
        long[] rv = new long[2];

        try {
            start = new Date();
            request = new URL("http", server.getHostName(), server.getPort(), "/?format=json");
            URLConnection conn = request.openConnection();
            final PlayList firstPlaylist = jsonParser.parseListChunk(conn.getInputStream());

            for (Media m : firstPlaylist.getResults())
                consumer.consumeElement(m);

            end = new Date();
            rv[0] = firstPlaylist.getResults().size();
            rv[1] = firstPlaylist.getTotal();
            System.out.println("processing of first playlist-part took " + (end.getTime() - start.getTime()) + " ms.");
        } catch (UnknownHostException uhe) {
            throw new RuntimeException("failed to connect to " + server.getHostName(), uhe);
        } catch (ConnectException ce) {
            throw new RuntimeException("connection failure with " + server.getHostName(), ce);
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return rv;
    }


    @Override
    public long loadRest(long[] listInfo, ElementConsumer<Media> consumer) {
        MedialistParser jsonParser = ApplicationServiceProvider.getService(MedialistParser.class);
        URL request = null;
        Date start, end;
        long rv = 0;

        try {
            PlayList next;
            URLConnection conn;
            long total = listInfo[1];
            long n = listInfo[0];
            long elementsRead = 0;
            String uri;

            start = new Date();
            try {
                while (n < total) {
                    uri = String.format("/?start=%d&limit=%d&format=json", n, 100);
                    request = new URL("http", server.getHostName(), server.getPort(), uri);
                    conn = request.openConnection();
                    next = jsonParser.parseListChunk(conn.getInputStream());
                    for (Media m : next.getResults())
                        consumer.consumeElement(m);
                    elementsRead = next.getResults().size();
                    n += elementsRead;
                    rv += elementsRead;
                    Thread.sleep(10);
                }
            } catch (UnknownHostException uhe) {
                throw new RuntimeException("failed to connect to " + server.getHostName(), uhe);
            } catch (ConnectException ce) {
                throw new RuntimeException("connection failure with " + server.getHostName(), ce);
            } catch (Throwable t) {
                System.err.println("Error on chunk #" + n);
                t.printStackTrace();
            }
            end = new Date();
            System.out.println("processing of rest of playlist took " + (end.getTime() - start.getTime()) + " ms.");
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return rv;
    }


    public void transmitChanges(EventList<AbstractMediaNode> changes) {
        for (AbstractMediaNode n : changes) {
            System.out.println("geänderter Eintrag: " + n.getClass().getSimpleName() + " - " + n.getName()); //$NON-NLS-1$ 
            System.out.println("\tverschieben von " + n.getOriginalPath().getAbsolutePath() + " nach "
                    + n.getRealPath().getAbsolutePath());

            //TODO: really create jobs for changes, so backend can participate on work

        }
    }

    private MediaServer server;
}
