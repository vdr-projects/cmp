package de.schwarzrot.cmpc.util;


import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import org.junit.Test;
import com.google.gson.stream.JsonReader;
import de.schwarzrot.cmpc.domain.Media;
import de.schwarzrot.cmpc.domain.MediaType;
import de.schwarzrot.cmpc.domain.PlayList;


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


    @Test
    public void testJSonParsing() {
        FileInputStream fis = null;

        try {
            fis = new FileInputStream(new File("test.json"));
            parseListChunk(fis);
            fis.close();
            fis = null;
        } catch (Throwable t) {
            t.printStackTrace();
        } finally {
            if (fis != null) {
                try {
                    fis.close();
                } catch (Throwable t) {
                }
            }
        }
    }


    protected Media readMedia(JsonReader reader) {
        Media rv = new Media();

        try {
            reader.beginObject();
            while (reader.hasNext()) {
                String name = reader.nextName();

                if ("name".equals(name)) {
                    rv.setName(reader.nextString());
                } else if ("type".equals(name)) {
                    rv.setType(reader.nextInt());
                } else if ("format".equals(name)) {
                    rv.setFormat(reader.nextString());
                } else if ("width".equals(name)) {
                    rv.setWidth(reader.nextInt());
                } else if ("height".equals(name)) {
                    rv.setHeight(reader.nextInt());
                } else if ("path".equals(name)) {
                    rv.setPath(reader.nextString());
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

                if ("name".equals(name)) {
                    rv.setName(reader.nextString());
                } else if ("start".equals(name)) {
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

                if ("total".equals(name)) {
                    rv.setTotal(reader.nextLong());
                } else if ("types".equals(name)) {
                    rv.setTypes(readTypeArray(reader));
                } else if ("results".equals(name)) {
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
