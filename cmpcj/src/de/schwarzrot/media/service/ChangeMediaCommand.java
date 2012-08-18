package de.schwarzrot.media.service;


import de.schwarzrot.media.domain.AbstractMediaNode;


public class ChangeMediaCommand extends AbstractMediaChangeCommand {
    public ChangeMediaCommand(AbstractMediaNode mediaNode) {
        super(mediaNode, "M");
    }
}
