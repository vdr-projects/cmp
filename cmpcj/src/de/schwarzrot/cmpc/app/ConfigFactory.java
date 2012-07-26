/**
 * ======================== legal notice ======================
 * 
 * File:      ConfigFactory.java
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
package de.schwarzrot.cmpc.app;


import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import de.schwarzrot.cmpc.domain.Config;
import de.schwarzrot.cmpc.domain.Media;
import de.schwarzrot.cmpc.domain.MediaServer;
import de.schwarzrot.cmpc.domain.PlayerDefinition;


public class ConfigFactory {
    protected static final Pattern SETUP_MASK = Pattern.compile("^\\s*(\\S+)\\s*=\\s*(.+)$");


    public ConfigFactory(File configDirectory) {
        baseDir = configDirectory;
    }


    public Config getConfig() {
        if (config == null) {
            config = readConfig();
        }
        return config;
    }


    protected Config readConfig() {
        File setupFile = new File(baseDir, "srclient.conf");
        BufferedReader br = null;
        Config rv = new Config();

        if (setupFile.exists()) {
            try {
                br = new BufferedReader(new FileReader(setupFile));
                String line, trimmedLine;

                while ((line = br.readLine()) != null) {
                    trimmedLine = line.trim();

                    if (trimmedLine.isEmpty() || trimmedLine.startsWith("#"))
                        continue;
                    Matcher m = SETUP_MASK.matcher(trimmedLine);

                    if (m.matches()) {
                        String key = m.group(1);
                        String value = m.group(2);

                        if (key.compareToIgnoreCase("server") == 0) {
                            String[] parts = value.split("\\s*\\:\\s*");
                            MediaServer ms = null;

                            if (parts.length > 1) {
                                ms = new MediaServer();
                                ms.setHostName(parts[0]);
                                ms.setPort(Integer.decode(parts[1]));

                                rv.addServer(ms);
                            }
                        } else if (key.compareToIgnoreCase("player") == 0) {
                            String[] parts = value.split("\\s*\\:\\s*");
                            PlayerDefinition pd = null;

                            if (parts.length > 1) {
                                pd = new PlayerDefinition();
                                String[] cmdline = parts[1].split("\\s+");

                                pd.setExecutable(cmdline[0]);

                                for (int i = 1; i < cmdline.length; ++i) {
                                    pd.addParameter(cmdline[i]);
                                }
                                if (parts[0].compareTo("*") == 0) {
                                    // default player
                                    for (Media.SupportedMediaType cmt : Media.SupportedMediaType.values())
                                        rv.putPlayer(cmt, pd);
                                } else {
                                    for (Media.SupportedMediaType cmt : Media.SupportedMediaType.values()) {
                                        if (parts[0].compareTo(cmt.name()) == 0)
                                            rv.putPlayer(cmt, pd);
                                    }
                                }
                            }
                        }
                    }
                }
            } catch (Throwable t) {
                t.printStackTrace();
            } finally {
                if (br != null) {
                    try {
                        br.close();
                    } catch (IOException e) {
                    }
                }
            }
        }
        return rv;
    }
    private Config config;
    private File baseDir;
}
