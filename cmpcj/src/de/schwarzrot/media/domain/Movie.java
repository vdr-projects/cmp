/**
 * ======================== legal notice ======================
 * 
 * File:      Movie.java
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
import java.util.HashMap;
import java.util.Map;


public class Movie extends Media {
    private static final long serialVersionUID = 713L;
    private static final Map<String, String> knownExtensions;


    public Movie(Genre parent, File path, String mimeType) {
        this(parent, SupportedMediaType.Movie, mimeType, path);
    }


    public Movie(Genre parent, SupportedMediaType type, String mimeType, File path) {
        super(parent, type, mimeType, path);
    }


    public boolean isInterlaced() {
        return interlaced;
    }


    public void setInterlaced(boolean interlaced) {
        this.interlaced = interlaced;
        setType(getType().ordinal() + 1);
    }


    public static String getContentType(String extension) {
        return knownExtensions.get(extension);
    }


    public static boolean isSupportedExtension(String extension) {
        return knownExtensions.containsKey(extension);
    }

    boolean interlaced;
    static {
        knownExtensions = new HashMap<String, String>();

        knownExtensions.put("aac", "audio/aac");
        knownExtensions.put("asd", "video/x-ms-asf");
        knownExtensions.put("asf", "video/x-ms-asf");
        knownExtensions.put("avi", "video/x-msvideo");
        knownExtensions.put("dv", "video/x-dv");
        knownExtensions.put("flv", "video/x-flv");
        knownExtensions.put("gl", "video/x-gl");
        knownExtensions.put("iso", "application/x-iso9660-image");
        knownExtensions.put("ogv", "video/ogg");
        knownExtensions.put("mkv", "video/x-matroska");
        knownExtensions.put("mov", "video/quicktime");
        knownExtensions.put("mpg", "video/mpeg");
        knownExtensions.put("mpeg", "video/mpeg");
        knownExtensions.put("swf", "application/x-shockwave-flash");
    }
}
