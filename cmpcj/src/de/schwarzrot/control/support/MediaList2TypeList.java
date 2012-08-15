/**
 * ======================== legal notice ======================
 * 
 * File:      MediaList2TypeList.java
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
package de.schwarzrot.control.support;


import ca.odell.glazedlists.EventList;
import ca.odell.glazedlists.TransformedList;
import ca.odell.glazedlists.event.ListEvent;
import de.schwarzrot.media.domain.AbstractMediaNode;
import de.schwarzrot.media.domain.Media;


public class MediaList2TypeList extends TransformedList<Media, AbstractMediaNode.SupportedMediaType> {
    public MediaList2TypeList(EventList<Media> source) {
        super(source);
        source.addListEventListener(this);
    }


    @Override
    public Media.SupportedMediaType get(int index) {
        Media m = source.get(index);

        return m.getType();
    }


    @Override
    public void listChanged(ListEvent<Media> listChanges) {
        updates.forwardEvent(listChanges);
    }


    @Override
    protected boolean isWritable() {
        return false;
    }
}
