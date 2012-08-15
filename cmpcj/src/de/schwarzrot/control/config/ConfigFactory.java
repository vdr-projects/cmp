/**
 * ======================== legal notice ======================
 * 
 * File:      ConfigFactory.java
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
package de.schwarzrot.control.config;


import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import de.schwarzrot.media.domain.Config;
import de.schwarzrot.media.domain.Media;
import de.schwarzrot.media.domain.MediaServer;
import de.schwarzrot.media.domain.PlayerDefinition;


public class ConfigFactory {
    protected static final Pattern SETUP_MASK = Pattern.compile("^\\s*(\\S+)\\s*=\\s*(.+)$");


    public ConfigFactory(File configDirectory, String applicationID) {
        baseDir = configDirectory;
        appID = applicationID;
    }


    public Config getConfig() {
        if (config == null) {
            config = readConfig();
        }
        return config;
    }


    public File getConfigDirectory() {
        return baseDir;
    }


    public void putConfig(Config config) {
        if (config != null)
            writeConfig(config);
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
                        } else if (key.compareToIgnoreCase("size") == 0) {
                            String[] parts = value.split("\\s*x\\s*");

                            if (parts.length > 1) {
                                try {
                                    rv.setMainWidth(Integer.decode(parts[0]));
                                } catch (Throwable t) {
                                }
                                try {
                                    rv.setMainHeight(Integer.decode(parts[1]));
                                } catch (Throwable t) {
                                }
                            }
                        } else if (key.compareToIgnoreCase("pos") == 0) {
                            String[] parts = value.split("\\s*\\/\\s*");

                            if (parts.length > 1) {
                                try {
                                    rv.setPosX(Integer.decode(parts[0]));
                                } catch (Throwable t) {
                                }
                                try {
                                    rv.setPosY(Integer.decode(parts[1]));
                                } catch (Throwable t) {
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


    protected void writeConfig(Config config) {
        File setupFile = new File(baseDir, "srclient.conf");
        PrintWriter out = null;
        StringBuilder sb = null;

        if (!setupFile.exists())
            setupFile.getParentFile().mkdirs();
        try {
            out = new PrintWriter(new FileWriter(setupFile));

            sb = new StringBuilder("#\n# configuration for ");
            sb.append(appID).append("\n#");
            out.println(sb.toString());
            for (MediaServer server : config.getKnownServers()) {
                sb = new StringBuilder("server = ");
                sb.append(server.getHostName()).append(":").append(server.getPort());
                out.println(sb.toString());
            }
            out.println();
            sb = new StringBuilder("#\n# currently supported media types (");
            sb.append(Media.SupportedMediaType.LegacyVdrRecording.name());
            sb.append(" is the old PES format):\n");
            sb.append("# ");
            sb.append("#");
            out.println(sb.toString());
            for (Media.SupportedMediaType mt : config.getPlayerMap().keySet()) {
                PlayerDefinition player = config.getPlayerMap().get(mt);

                sb = new StringBuilder("player = ");
                sb.append(mt.name()).append(" : ").append(player.getExecutable());
                for (String p : player.getParameters()) {
                    sb.append(" ").append(p);
                }
                out.println(sb.toString());
            }
            out.println();
            sb = new StringBuilder("size = ");
            sb.append(config.getMainWidth()).append(" x ").append(config.getMainHeight());
            out.println(sb.toString());

            sb = new StringBuilder("pos = ");
            sb.append(config.getPosX()).append(" / ").append(config.getPosY());
            out.println(sb.toString());
        } catch (Throwable t) {
            t.printStackTrace();
        } finally {
            if (out != null)
                out.close();
        }
    }
    private Config config;
    private File baseDir;
    private final String appID;
}
