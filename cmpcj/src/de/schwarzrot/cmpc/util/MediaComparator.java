/**
 * ======================== legal notice ======================
 * 
 * File:      MediaComparator.java
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
package de.schwarzrot.cmpc.util;


import java.util.Comparator;
import de.schwarzrot.cmpc.domain.Media;


public class MediaComparator implements Comparator<Media> {
    @Override
    public int compare(Media a, Media b) {
        if (a.getType() == b.getType())
            return a.getName().compareToIgnoreCase(b.getName());
        return a.getType() - b.getType();
    }
}
