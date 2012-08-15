/**
 * ======================== legal notice ======================
 * 
 * File:      MediaFactory.java
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
package de.schwarzrot.media.service;


import java.io.File;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;
import de.schwarzrot.media.domain.AbstractMediaNode;
import de.schwarzrot.media.domain.Audio;
import de.schwarzrot.media.domain.DVDImage;
import de.schwarzrot.media.domain.Genre;
import de.schwarzrot.media.domain.LegacyVdrRecording;
import de.schwarzrot.media.domain.Media;
import de.schwarzrot.media.domain.Movie;
import de.schwarzrot.media.domain.Picture;
import de.schwarzrot.media.domain.VdrRecording;


public class MediaFactory {
    public MediaFactory(File baseDir) {
        this.baseDir = baseDir;
        prefix = baseDir.getAbsolutePath();
        mediaCache = new HashMap<File, AbstractMediaNode>();
        mediaCache.put(baseDir, new Genre(baseDir));
    }


    //TODO: 
    // here we can't rely on file system information.
    // may be we got files from remote system ...
    // so instead to use lookahead for multifile movies, we need to go back 
    // from keyfiles
    public Media createMedia(File mayBeMedia) {
        if (!mayBeMedia.getAbsolutePath().startsWith(prefix))
            return null;
        String xt = mayBeMedia.getName().substring(mayBeMedia.getName().lastIndexOf(".") + 1);
        Genre parent = null;
        Media rv = null;

        if (VdrRecording.isKeyFile(mayBeMedia)) {
            parent = getGenre(mayBeMedia.getParentFile().getParentFile().getParentFile());

            rv = new VdrRecording(parent, mayBeMedia.getParentFile());
        } else if (LegacyVdrRecording.isKeyFile(mayBeMedia)) {
            parent = getGenre(mayBeMedia.getParentFile().getParentFile().getParentFile());

            rv = new LegacyVdrRecording(parent, mayBeMedia.getParentFile());
        } else if (DVDImage.isKeyFile(mayBeMedia)) {
            parent = getGenre(mayBeMedia.getParentFile().getParentFile().getParentFile());

            rv = new DVDImage(parent, mayBeMedia.getParentFile().getParentFile());
        } else if (Movie.isSupportedExtension(xt)) {
            parent = getGenre(mayBeMedia.getParentFile());
            rv = new Movie(parent, mayBeMedia, Movie.getContentType(xt));
        } else if (Audio.isSupportedExtension(xt)) {
            parent = getGenre(mayBeMedia.getParentFile());
            rv = new Audio(parent, mayBeMedia, Audio.getContentType(xt));
        } else if (Picture.isSupportedExtension(xt)) {
            parent = getGenre(mayBeMedia.getParentFile());
            rv = new Picture(parent, mayBeMedia, Picture.getContentType(xt));
        }
        if (rv != null)
            mediaCache.put(mayBeMedia, rv);

        return rv;
    }


    public Map<File, AbstractMediaNode> getCache() {
        return mediaCache;
    }


    public Genre getGenre(File mayBeGenre) {
        if (!mayBeGenre.isDirectory())
            return null;

        if (!mediaCache.containsKey(mayBeGenre))
            createGenre(mayBeGenre);
        AbstractMediaNode rv = mediaCache.get(mayBeGenre);

        if (rv instanceof Genre)
            return (Genre) rv;
        return null;
    }


    protected void createGenre(File shouldBeGenre) {
        File tmp = shouldBeGenre;
        Stack<File> unknownGenres = new Stack<File>();

        while (tmp != null && !mediaCache.containsKey(tmp)) {
            unknownGenres.push(tmp);
            tmp = tmp.getParentFile();
        }
        AbstractMediaNode node = mediaCache.get(tmp != null ? tmp : baseDir);
        Genre g = null;

        if (node != null && node instanceof Genre)
            g = (Genre) node;

        while (unknownGenres.size() > 0) {
            tmp = unknownGenres.pop();
            g = new Genre(g, tmp);
            mediaCache.put(tmp, g);
        }
    }

    private Map<File, AbstractMediaNode> mediaCache;
    private File baseDir;
    private String prefix;
}
