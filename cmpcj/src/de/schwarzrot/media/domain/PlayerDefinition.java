/**
 * ======================== legal notice ======================
 * 
 * File:      PlayerDefinition.java
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
import java.util.List;


public class PlayerDefinition {
    public PlayerDefinition() {
        parameters = new ArrayList<String>();
    }


    public void addParameter(String parameter) {
        parameters.add(parameter);
    }


    public String getCommandLine() {
        if (commandLine == null)
            assembleCommandLine();
        return commandLine;
    }


    public String getExecutable() {
        return executable;
    }


    public AbstractMediaNode.SupportedMediaType getMediaType() {
        return mediaType;
    }


    public List<String> getParameters() {
        return parameters;
    }


    public void setCommandLine(String commandLine) {
        this.commandLine = commandLine;
        decodeCommandLine();
    }


    public void setExecutable(String executable) {
        this.executable = executable;
        assembleCommandLine();
    }


    public void setMediaType(AbstractMediaNode.SupportedMediaType mediaType) {
        this.mediaType = mediaType;
    }


    public void setParameters(List<String> parameters) {
        this.parameters = parameters;
        assembleCommandLine();
    }


    protected void assembleCommandLine() {
        if (executable == null || parameters == null || parameters.size() < 1)
            return;
        StringBuilder sb = new StringBuilder(executable);

        for (String p : parameters) {
            sb.append(" ").append(p);
        }
        commandLine = sb.toString();
    }


    protected void decodeCommandLine() {
        String[] parts = commandLine.split("\\s+");

        executable = parts[0];
        parameters.clear();
        for (int i = 1; i < parts.length; ++i) {
            parameters.add(parts[i]);
        }
    }

    private AbstractMediaNode.SupportedMediaType mediaType;
    private String executable;
    private String commandLine;
    private List<String> parameters;
}
