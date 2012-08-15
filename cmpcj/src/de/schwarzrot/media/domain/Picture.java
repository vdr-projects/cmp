/**
 * ======================== legal notice ======================
 * 
 * File:      Picture.java
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


public class Picture extends Media {
    private static final long serialVersionUID = 713L;
    private static final Map<String, String> knownExtensions;


    public Picture(Genre parent, File path, String mimeType) {
        super(parent, SupportedMediaType.Picture, mimeType, path);
    }


    public static String getContentType(String extension) {
        return knownExtensions.get(extension);
    }


    public static boolean isSupportedExtension(String extension) {
        return knownExtensions.containsKey(extension);
    }

    static {
        knownExtensions = new HashMap<String, String>();

        knownExtensions.put("aac", "audio/aac");
        knownExtensions.put("bmp", "image/x-windows-bmp");
        knownExtensions.put("gif", "image/gif");
        knownExtensions.put("jff", "image/jpeg");
        knownExtensions.put("jfif", "image/jpeg");
        knownExtensions.put("jif", "image/jpeg");
        knownExtensions.put("jp2", "image/jp2");
        knownExtensions.put("jpe", "image/jpeg");
        knownExtensions.put("jpeg", "image/jpeg");
        knownExtensions.put("jpg", "image/jpeg");
        knownExtensions.put("jpm", "image/jpm");
        knownExtensions.put("jpx", "image/jpx");
        knownExtensions.put("pbm", "image/x-portable-bitmap");
        knownExtensions.put("pct", "image/x-pict");
        knownExtensions.put("pcx", "image/x-pcx");
        knownExtensions.put("png", "image/png");
        knownExtensions.put("pnm", "image/x-portable-anymap");
        knownExtensions.put("ppm", "image/x-portable-pixmap");
        knownExtensions.put("qti", "image/quicktime");
        knownExtensions.put("ras", "image/x-cmu-raster");
        knownExtensions.put("rgb", "image/x-rgb");
    }
}
