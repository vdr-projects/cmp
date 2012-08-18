package de.schwarzrot.media.service;


import de.schwarzrot.media.domain.AbstractMediaNode;


public class RemoveMediaCommand extends AbstractMediaChangeCommand {
    public RemoveMediaCommand(AbstractMediaNode mediaNode) {
        super(mediaNode, "R");
    }
}
