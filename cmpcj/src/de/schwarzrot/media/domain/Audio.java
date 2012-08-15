/**
 * ======================== legal notice ======================
 * 
 * File:      Audio.java
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


public class Audio extends Media {
    private static final long serialVersionUID = 713L;
    private static final Map<String, String> knownExtensions;


    public Audio(Genre parent, File path, String mimeType) {
        super(parent, SupportedMediaType.Audio, mimeType, path);
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
        knownExtensions.put("aif", "audio/x-aiff");
        knownExtensions.put("aiff", "audio/x-aiff");
        knownExtensions.put("aifc", "audio/x-aiff");
        knownExtensions.put("au", "audio/x-au");
        knownExtensions.put("fla", "audio/flac");
        knownExtensions.put("flac", "audio/flac");
        knownExtensions.put("oga", "audio/ogg");
        knownExtensions.put("ogg", "audio/ogg");
        knownExtensions.put("mka", "audio/x-matroska");
        knownExtensions.put("mp3", "audio/mpeg");
        knownExtensions.put("mp4", "audio/x-mpeg4");
        knownExtensions.put("m4a", "audio/x-m4");
        knownExtensions.put("mpp", "audio/x-musepack");
        knownExtensions.put("ram", "audio/x-realaudio");
    }
}
