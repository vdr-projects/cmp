/**
 * ======================== legal notice ======================
 * 
 * File:      SelectedMedia.java
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


import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import ca.odell.glazedlists.EventList;
import ca.odell.glazedlists.swing.DefaultEventSelectionModel;
import de.schwarzrot.media.domain.Media;


public class SelectedMedia implements ListSelectionListener {
    public static final String MEDIA_PROPERTY = "media";


    public SelectedMedia(EventList<Media> source) {
        pcs = new PropertyChangeSupport(this);
        mediaList = source;
    }


    public void addPropertyChangeListener(PropertyChangeListener listener) {
        pcs.addPropertyChangeListener(listener);
    }


    public void clear() {
        pcs.firePropertyChange(MEDIA_PROPERTY, this.media, this.media = null);
    }


    public Media getMedia() {
        return media;
    }


    public void removePropertyChangeListener(PropertyChangeListener listener) {
        pcs.removePropertyChangeListener(listener);
    }


    @Override
    public void valueChanged(ListSelectionEvent e) {
        if (e.getValueIsAdjusting())
            return;
        if (e.getSource() instanceof DefaultEventSelectionModel) {
            @SuppressWarnings("unchecked")
            DefaultEventSelectionModel<Media> sm = (DefaultEventSelectionModel<Media>) e.getSource();

            if (sm.isSelectionEmpty())
                return;
            pcs.firePropertyChange(MEDIA_PROPERTY, this.media, this.media = mediaList.get(sm.getLeadSelectionIndex()));
        }
    }

    private Media media;
    private PropertyChangeSupport pcs;
    private EventList<Media> mediaList;
}
