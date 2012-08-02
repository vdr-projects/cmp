/**
 * ======================== legal notice ======================
 * 
 * File: Media.java Created: Author: <a
 * href="mailto:geronimo013@gmx.de">Geronimo</a> Project: cmpc - a java frontend
 * (client) part of compound media player uses external players to play the
 * media
 * 
 * CMP - compound media player
 * 
 * is a client/server mediaplayer intended to play any media from any
 * workstation without the need to export or mount shares. cmps is an easy to
 * use backend with a (ready to use) HTML-interface. Additionally the backend
 * supports authentication via HTTP-digest authorization. cmpc is a client with
 * vdr-like osd-menues.
 * 
 * Copyright (c) 2012 Reinhard Mantey, some rights reserved! published under
 * Creative Commons by-sa For details see
 * http://creativecommons.org/licenses/by-sa/3.0/
 * 
 * The cmp project's homepage is at
 * http://projects.vdr-developer.org/projects/cmp
 * 
 * --------------------------------------------------------------
 */
package de.schwarzrot.cmpc.domain;


import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;


public class Media {
    public enum SupportedMediaType {
        Invalid, Audio, Movie, IMovie, DVDImage, IDVDImage, LegacyVdrRecording, ILegacyVdrRecording, VdrRecording, IVdrRecording, Picture, Unknown
    };


    public String getFormat() {
        return format;
    }


    public int getHeight() {
        return height;
    }


    public String getName() {
        return name;
    }


    public String getPath() {
        return path;
    }


    public String getSearch() {
        return search;
    }


    public SupportedMediaType getType() {
        return type;
    }


    public int getWidth() {
        return width;
    }


    public boolean isHD() {
        return height > 576;
    }


    public void setFormat(String format) {
        this.format = format;
    }


    public void setHeight(int height) {
        this.height = height;
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
        if (type == SupportedMediaType.Audio.ordinal())
            this.type = SupportedMediaType.Audio;
        else if (type == SupportedMediaType.Movie.ordinal())
            this.type = SupportedMediaType.Movie;
        else if (type == SupportedMediaType.IMovie.ordinal())
            this.type = SupportedMediaType.IMovie;
        else if (type == SupportedMediaType.DVDImage.ordinal())
            this.type = SupportedMediaType.DVDImage;
        else if (type == SupportedMediaType.IDVDImage.ordinal())
            this.type = SupportedMediaType.IDVDImage;
        else if (type == SupportedMediaType.LegacyVdrRecording.ordinal())
            this.type = SupportedMediaType.LegacyVdrRecording;
        else if (type == SupportedMediaType.ILegacyVdrRecording.ordinal())
            this.type = SupportedMediaType.ILegacyVdrRecording;
        else if (type == SupportedMediaType.VdrRecording.ordinal())
            this.type = SupportedMediaType.VdrRecording;
        else if (type == SupportedMediaType.IVdrRecording.ordinal())
            this.type = SupportedMediaType.IVdrRecording;
        else if (type == SupportedMediaType.Picture.ordinal())
            this.type = SupportedMediaType.Picture;
        else
            this.type = SupportedMediaType.Invalid;
    }


    public void setWidth(int width) {
        this.width = width;
    }

    private String name;
    private SupportedMediaType type;
    private String format;
    private String path;
    private String search;
    private int width;
    private int height;
}
