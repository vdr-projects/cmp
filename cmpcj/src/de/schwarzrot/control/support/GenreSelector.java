/**
 * ======================== legal notice ======================
 * 
 * File:      GenreSelector.java
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
package de.schwarzrot.control.support;


import ca.odell.glazedlists.matchers.Matcher;
import de.schwarzrot.media.domain.Genre;
import de.schwarzrot.media.domain.Media;


public class GenreSelector implements Matcher<Media> {
    public GenreSelector(Genre genre) {
        g = genre;
    }


    @Override
    public boolean matches(Media m) {
        return m.getRealPath().getAbsolutePath().startsWith(g.getRealPath().getAbsolutePath());
    }

    private Genre g;
}