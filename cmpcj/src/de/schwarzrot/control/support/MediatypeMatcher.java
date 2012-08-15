/**
 * ======================== legal notice ======================
 * 
 * File:      MediatypeMatcher.java
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


import java.util.Collection;
import java.util.HashSet;
import java.util.Set;
import ca.odell.glazedlists.matchers.Matcher;
import de.schwarzrot.media.domain.AbstractMediaNode;
import de.schwarzrot.media.domain.Media;


public class MediatypeMatcher implements Matcher<Media> {
    public MediatypeMatcher(Collection<AbstractMediaNode.SupportedMediaType> mediaTypes) {
        this.mediaTypes.addAll(mediaTypes);
    }


    @Override
    public boolean matches(Media m) {
        if (m == null)
            return false;
        if (mediaTypes.isEmpty())
            return true;
        Media.SupportedMediaType mt = m.getType();

        return mediaTypes.contains(mt);
    }

    private Set<AbstractMediaNode.SupportedMediaType> mediaTypes = new HashSet<Media.SupportedMediaType>();
}
