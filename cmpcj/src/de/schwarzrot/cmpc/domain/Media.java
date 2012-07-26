/**
 * ======================== legal notice ======================
 * 
 * File:      Media.java
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
package de.schwarzrot.cmpc.domain;


import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;


public class Media {
    public enum SupportedMediaType {
        Invalid, Audio, Movie, DVDImage, LegacyVdrRecording, VdrRecording, Picture, Unknown
    };


    public String getName() {
        return name;
    }


    public String getPath() {
        return path;
    }


    public String getSearch() {
        return search;
    }


    public int getType() {
        return type;
    }


    public void setName(String name) {
        this.name = name;
    }


    public void setPath(String path) {
        this.path = path;
        try {
            search = URLDecoder.decode(path, "utf8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }


    public void setType(int type) {
        this.type = type;
    }

    private String name;
    private int type;
    private String path;
    private String search;
}
