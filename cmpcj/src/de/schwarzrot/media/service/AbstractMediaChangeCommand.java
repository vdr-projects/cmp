package de.schwarzrot.media.service;


import de.schwarzrot.media.domain.AbstractMediaNode;


public abstract class AbstractMediaChangeCommand {
    protected AbstractMediaChangeCommand(AbstractMediaNode media, String type) {
        mediaNode = media;
        commandType = type;
    }


    public String getCommandType() {
        return commandType;
    }


    public AbstractMediaNode getMediaNode() {
        return mediaNode;
    }

    private AbstractMediaNode mediaNode;
    private String commandType;
}
