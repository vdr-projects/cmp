/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractMediaNode.java
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
import java.io.Serializable;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URLDecoder;
import java.util.Map;
import java.util.TreeMap;


public abstract class AbstractMediaNode implements Serializable, Comparable<AbstractMediaNode> {
    public static final String FORMAT_PROPERTY = "format";
    public static final String NAME_PROPERTY = "name";
    public static final String PATH_PROPERTY = "path";
    public static final String TYPE_PROPERTY = "type";
    public static final String SEARCH_PROPERTY = "search";
    private static final long serialVersionUID = 713L;
    public enum SupportedMediaType {
        Genre, // 
        Audio, //
        Movie, IMovie, DVDImage, IDVDImage, //
        LegacyVdrRecording, ILegacyVdrRecording, VdrRecording, IVdrRecording, //
        Picture, //
        Unknown
    }


    protected AbstractMediaNode(AbstractMediaNode parent, SupportedMediaType type, String mimeType, File path) {
        properties = new TreeMap<String, Object>();
        setParent(parent);
        setType(type);
        setMimeType(mimeType);
        setRealPath(path);
        originalPath = realPath;
    }


    @Override
    public int compareTo(AbstractMediaNode o) {
        if (o == null)
            return -1;

        if (this != o) {
            int rv = type.ordinal() - o.getType().ordinal();

            if (rv == 0)
                rv = getName().compareToIgnoreCase(o.getName());

            return rv;
        }
        return 0;
    }


    public String getFormat() {
        return format;
    }


    public String getMimeType() {
        return mimeType;
    }


    public String getName() {
        return name;
    }


    public File getOriginalPath() {
        return originalPath;
    }


    public AbstractMediaNode getParent() {
        return parent;
    }


    public Map<String, Object> getProperties() {
        return properties;
    }


    public File getRealPath() {
        return realPath;
    }


    public String getSearch() {
        return search;
    }


    public SupportedMediaType getType() {
        return type;
    }


    public URI getURI() {
        return uri;
    }


    public void setFormat(String format) {
        this.format = format;
        properties.put(FORMAT_PROPERTY, format);
    }


    public void setMimeType(String mimeType) {
        this.mimeType = mimeType;
    }


    public void setName(String name) {
        this.name = name;
        properties.put(NAME_PROPERTY, name);
    }


    public void setParent(AbstractMediaNode parent) {
        if ((this.parent = parent) != null)
            refresh();
    }


    public void setPath(String path) {
        if (uri == null) {
            try {
                //                properties.put(PATH_PROPERTY, path);
                uri = new URI(path);
                properties.put(PATH_PROPERTY, uri.toString());
            } catch (URISyntaxException e) {
                e.printStackTrace();
            }
        }
        try {
            File tmp = new File(URLDecoder.decode(path, "UTF-8"));

            if (path != null && originalPath == null)
                originalPath = tmp;
            setRealPath(tmp);
        } catch (Throwable t) {
            t.printStackTrace();
        }
    }


    public void setProperty(String key, Object value) {
        properties.put(key, value);
    }


    public void setRealPath(File realPath) {
        this.realPath = realPath;
        if (name == null && realPath != null)
            setName(realPath.getName());
    }


    public void setSearch(String search) {
        this.search = search;
        properties.put(SEARCH_PROPERTY, search);
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
            throw new EnumConstantNotPresentException(SupportedMediaType.class, "unknown ordinal #" + type);
        properties.put(TYPE_PROPERTY, this.type);
    }


    @Override
    public String toString() {
        return getName();
    }


    protected void refresh() {
        if (parent != null && realPath != null)
            realPath = new File(parent.getRealPath(), realPath.getName());
    }


    protected void setType(SupportedMediaType type) {
        this.type = type;
        properties.put(TYPE_PROPERTY, this.type);
    }

    private File realPath;
    private File originalPath;
    private URI uri;
    private SupportedMediaType type;
    private AbstractMediaNode parent;
    private String name;
    private String mimeType;
    private String search;
    private String format;
    private Map<String, Object> properties;
}
