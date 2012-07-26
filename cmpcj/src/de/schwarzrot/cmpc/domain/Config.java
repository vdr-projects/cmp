/**
 * ======================== legal notice ======================
 * 
 * File:      Config.java
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


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class Config {
    public Config() {
        knownServers = new ArrayList<MediaServer>();
        playerMap = new HashMap<Media.SupportedMediaType, PlayerDefinition>();
    }


    public void addServer(MediaServer ms) {
        knownServers.add(ms);
    }


    public List<MediaServer> getKnownServers() {
        return knownServers;
    }


    public Map<Media.SupportedMediaType, PlayerDefinition> getPlayerMap() {
        return playerMap;
    }


    public void putPlayer(Media.SupportedMediaType type, PlayerDefinition pd) {
        playerMap.put(type, pd);
    }


    public void setKnownServers(List<MediaServer> knownServers) {
        this.knownServers = knownServers;
    }


    public void setPlayerMap(Map<Media.SupportedMediaType, PlayerDefinition> playerMap) {
        this.playerMap = playerMap;
    }

    private List<MediaServer> knownServers;
    private Map<Media.SupportedMediaType, PlayerDefinition> playerMap;
}
