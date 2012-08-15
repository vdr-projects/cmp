/**
 * ======================== legal notice ======================
 * 
 * File:      VdrRecording.java
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


public class VdrRecording extends Movie {
    private static final long serialVersionUID = 713L;
    protected static final String DEFAULT_MIME_TYPE = "video/mpeg";
    protected static final String KEY_FILE = "00001.vdr";


    public VdrRecording(Genre parent, File path) {
        this(parent, SupportedMediaType.VdrRecording, DEFAULT_MIME_TYPE, path);
    }


    protected VdrRecording(Genre parent, SupportedMediaType type, String mimeType, File path) {
        super(parent, type, mimeType, path);
    }


    @Override
    public String getName() {
        return getRealPath().getParentFile().getName();
    }


    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(getName());

        sb.append(" (").append(super.getName()).append(")");

        return sb.toString();
    }


    public static boolean isKeyFile(File file2Check) {
        return file2Check.getName().equals(KEY_FILE);
    }
}
