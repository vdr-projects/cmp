package de.schwarzrot.media.service;


import de.schwarzrot.media.domain.AbstractMediaNode;


public class CreateMediaCommand extends AbstractMediaChangeCommand {
    public CreateMediaCommand(AbstractMediaNode mediaNode) {
        super(mediaNode, "C");
    }
}
