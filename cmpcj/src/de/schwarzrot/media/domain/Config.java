/**
 * ======================== legal notice ======================
 * 
 * File:      Config.java
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


    public int getMainHeight() {
        return mainHeight;
    }


    public int getMainWidth() {
        return mainWidth;
    }


    public Map<Media.SupportedMediaType, PlayerDefinition> getPlayerMap() {
        return playerMap;
    }


    public int getPosX() {
        return posX;
    }


    public int getPosY() {
        return posY;
    }


    public boolean isDebug() {
        return debug;
    }


    public void putPlayer(Media.SupportedMediaType type, PlayerDefinition pd) {
        playerMap.put(type, pd);
    }


    public void setDebug(boolean debug) {
        this.debug = debug;
    }


    public void setKnownServers(List<MediaServer> knownServers) {
        this.knownServers = knownServers;
    }


    public void setMainHeight(int mainHeight) {
        this.mainHeight = mainHeight;
    }


    public void setMainWidth(int mainWidth) {
        this.mainWidth = mainWidth;
    }


    public void setPlayerMap(Map<Media.SupportedMediaType, PlayerDefinition> playerMap) {
        this.playerMap = playerMap;
    }


    public void setPosX(int posX) {
        this.posX = posX;
    }


    public void setPosY(int posY) {
        this.posY = posY;
    }

    private List<MediaServer> knownServers;
    private Map<Media.SupportedMediaType, PlayerDefinition> playerMap;
    private boolean debug;
    private int posX;
    private int posY;
    private int mainWidth;
    private int mainHeight;
}
