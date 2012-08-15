/**
 * ======================== legal notice ======================
 * 
 * File:      MedialistParser.java
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
package de.schwarzrot.media.util;


import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import com.google.gson.stream.JsonReader;
import de.schwarzrot.media.domain.Media;
import de.schwarzrot.media.domain.MediaType;
import de.schwarzrot.media.domain.PlayList;


public class MedialistParser {
    public PlayList parseListChunk(InputStream is) {
        JsonReader reader = null;
        PlayList rv = null;

        try {
            reader = new JsonReader(new InputStreamReader(is, "UTF-8"));

            rv = readPlayList(reader);
        } catch (Throwable t) {
            t.printStackTrace();
        } finally {
            try {
                reader.close();
            } catch (Throwable t) {
            }
        }
        return rv;
    }


    protected Media readMedia(JsonReader reader) {
        Media rv = new Media();

        try {
            reader.beginObject();
            while (reader.hasNext()) {
                String name = reader.nextName();

                if (Media.NAME_PROPERTY.equals(name)) {
                    rv.setName(reader.nextString());
                } else if (Media.TYPE_PROPERTY.equals(name)) {
                    rv.setType(reader.nextInt());
                } else if (Media.FORMAT_PROPERTY.equals(name)) {
                    rv.setFormat(reader.nextString());
                } else if (Media.PATH_PROPERTY.equals(name)) {
                    rv.setPath(reader.nextString());
                } else {
                    rv.setProperty(name, reader.nextString());
                }
            }
            reader.endObject();
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return rv;
    }


    protected List<Media> readMediaArray(JsonReader reader) {
        List<Media> rv = new ArrayList<Media>();

        try {
            reader.beginArray();
            while (reader.hasNext()) {
                rv.add(readMedia(reader));
            }
            reader.endArray();
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return rv;
    }


    protected MediaType readMediaType(JsonReader reader) {
        MediaType rv = new MediaType();

        try {
            reader.beginObject();
            while (reader.hasNext()) {
                String name = reader.nextName();

                if (MediaType.NAME_PROPERTY.equals(name)) {
                    rv.setName(reader.nextString());
                } else if (MediaType.START_PROPERTY.equals(name)) {
                    rv.setStart(reader.nextLong());
                } else {
                    reader.skipValue();
                }
            }
            reader.endObject();
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return rv;
    }


    protected PlayList readPlayList(JsonReader reader) {
        PlayList rv = new PlayList();

        try {
            reader.beginObject();
            while (reader.hasNext()) {
                String name = reader.nextName();

                if (PlayList.TOTAL_PROPERTY.equals(name)) {
                    rv.setTotal(reader.nextLong());
                } else if (PlayList.TYPES_PROPERTY.equals(name)) {
                    rv.setTypes(readTypeArray(reader));
                } else if (PlayList.RESULTS_PROPERTY.equals(name)) {
                    rv.setResults(readMediaArray(reader));
                } else {
                    reader.skipValue();
                }
            }
            reader.endObject();
        } catch (Throwable t) {
            t.printStackTrace();
            rv = null;
        }
        return rv;
    }


    protected List<MediaType> readTypeArray(JsonReader reader) {
        List<MediaType> rv = new ArrayList<MediaType>();

        try {
            reader.beginArray();
            while (reader.hasNext()) {
                rv.add(readMediaType(reader));
            }
            reader.endArray();
        } catch (Throwable t) {
            t.printStackTrace();
        }
        return rv;
    }
}
