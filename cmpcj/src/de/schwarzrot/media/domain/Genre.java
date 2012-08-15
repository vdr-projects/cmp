/**
 * ======================== legal notice ======================
 * 
 * File: Genre.java Created: 13. June 2012, 04:57 Author: <a
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
package de.schwarzrot.media.domain;


import java.io.File;
import java.util.ArrayList;
import java.util.List;


public class Genre extends AbstractMediaNode {
    private static final long serialVersionUID = 713L;
    private static final String MIME_TYPE = "text/plain";


    public Genre(File path) {
        this(null, path);
    }


    public Genre(Genre parent, File path) {
        super(parent, SupportedMediaType.Genre, MIME_TYPE, path);
        mediaList = new ArrayList<Media>();
        children = new ArrayList<Genre>();
        if (parent != null)
            parent.addGenre(this);
    }


    public void addGenre(Genre g) {
        children.add(g);
    }


    public void addMedia(Media m) {
        mediaList.add(m);
    }


    public List<Genre> getChildren() {
        return children;
    }


    public List<Media> getMediaList() {
        return mediaList;
    }


    @Override
    public void refresh() {
        super.refresh();
        update();
    }


    public void removeGenre(Genre g) {
        children.remove(g);
    }


    public void removeMedia(Media m) {
        mediaList.remove(m);
    }


    public void setChildren(List<Genre> children) {
        this.children = children;
    }


    public void setMediaList(List<Media> mediaList) {
        this.mediaList = mediaList;
    }


    public void setParent(Genre parent) {
        Genre oldParent = (Genre) getParent();

        super.setParent(parent);
        if (oldParent != null)
            oldParent.removeGenre(this);
        parent.addGenre(this);
    }


    @Override
    public String toString() {
        return getName();
    }


    public void update() {
        // instances has moved, so all children and media members must be updated
        if (children != null) {
            for (Genre g : children) {
                g.refresh();
                g.update();
            }
        }
        if (mediaList != null) {
            for (Media m : mediaList)
                m.refresh();
        }
    }

    private List<Media> mediaList;
    private List<Genre> children;
}
