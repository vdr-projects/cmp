/**
 * ======================== legal notice ======================
 * 
 * File:      Media.java
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
package de.schwarzrot.media.domain;


import java.io.File;


public class Media extends AbstractMediaNode {
    private static final long serialVersionUID = 713L;


    public Media() {
        super(null, SupportedMediaType.Unknown, null, null);
    }


    public Media(Genre parent, SupportedMediaType type, String mimeType, File path) {
        super(parent, type, mimeType, path);
        parent.addMedia(this);
    }


    public void setParent(Genre parent) {
        Genre oldParent = (Genre) getParent();

        super.setParent(parent);
        if (oldParent != null)
            oldParent.removeMedia(this);
        parent.addMedia(this);
    }
}
