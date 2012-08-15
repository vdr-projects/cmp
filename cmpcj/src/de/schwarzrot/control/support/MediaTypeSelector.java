/**
 * ======================== legal notice ======================
 * 
 * File:      MediaTypeSelector.java
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


import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.ListCellRenderer;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import ca.odell.glazedlists.EventList;
import ca.odell.glazedlists.UniqueList;
import ca.odell.glazedlists.matchers.AbstractMatcherEditor;
import ca.odell.glazedlists.matchers.Matcher;
import ca.odell.glazedlists.swing.DefaultEventListModel;
import ca.odell.glazedlists.swing.DefaultEventSelectionModel;
import de.schwarzrot.base.util.ApplicationServiceProvider;
import de.schwarzrot.base.util.ImageFactory;
import de.schwarzrot.media.domain.Media;


public class MediaTypeSelector extends AbstractMatcherEditor<Media> implements ListSelectionListener {
    public class MediaTypeCellRenderer extends JLabel implements ListCellRenderer {
        private static final long serialVersionUID = 713L;


        public MediaTypeCellRenderer() {
            loadImages();
        }


        @Override
        public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected,
                boolean cellHasFocus) {
            ImageIcon icon = null;

            if (isSelected) {
                setBackground(list.getSelectionBackground());
                setForeground(list.getSelectionForeground());
                icon = selImages[((Media.SupportedMediaType) value).ordinal()];
            } else {
                setBackground(list.getBackground());
                setForeground(list.getForeground());
                icon = stdImages[((Media.SupportedMediaType) value).ordinal()];
            }
            setSize(110, 110);
            setHorizontalAlignment(JLabel.CENTER);

            if (icon != null) {
                setIcon(icon);
                setText("");
            } else {
                setText(value.toString());
            }
            return this;
        }


        protected void loadImages() {
            ImageFactory imgFak = ApplicationServiceProvider.getService(ImageFactory.class);
            int i = 0;

            stdImages = new ImageIcon[Media.SupportedMediaType.values().length];
            for (Media.SupportedMediaType smt : Media.SupportedMediaType.values()) {
                StringBuilder sb = new StringBuilder(smt.getClass().getSimpleName());

                sb.append(".").append(smt.name()).append(".default");
                stdImages[i++] = imgFak.getIcon(sb.toString(), 110, 110);
            }

            i = 0;
            selImages = new ImageIcon[Media.SupportedMediaType.values().length];
            for (Media.SupportedMediaType smt : Media.SupportedMediaType.values()) {
                StringBuilder sb = new StringBuilder(smt.getClass().getSimpleName());

                sb.append(".").append(smt.name()).append(".active");
                selImages[i++] = imgFak.getIcon(sb.toString(), 110, 110);
            }
        }

        ImageIcon[] stdImages;
        ImageIcon[] selImages;
    }


    public MediaTypeSelector(EventList<Media> source) {
        EventList<Media.SupportedMediaType> mediaTypeNonUnique = new MediaList2TypeList(source);

        mediaTypeList = new UniqueList<Media.SupportedMediaType>(mediaTypeNonUnique);
        DefaultEventListModel<Media.SupportedMediaType> mediaTypeListModel = new DefaultEventListModel<Media.SupportedMediaType>(
                mediaTypeList);

        mediaTypeJList = new JList(mediaTypeListModel);
        DefaultEventSelectionModel<Media.SupportedMediaType> mediaTypeSelectionModel = new DefaultEventSelectionModel<Media.SupportedMediaType>(
                mediaTypeList);

        mediaTypeJList.setSelectionModel(mediaTypeSelectionModel);
        selectedTypes = mediaTypeSelectionModel.getSelected();
        mediaTypeJList.addListSelectionListener(this);
        mediaTypeJList.setCellRenderer(new MediaTypeCellRenderer());
        mediaTypeJList.setBackground(Color.BLACK);
        mediaTypeJList.setMinimumSize(new Dimension(100, 100));
        mediaTypeComponent = new JScrollPane(mediaTypeJList);
    }


    public JComponent getComponent() {
        return mediaTypeComponent;
    }


    public JList getJList() {
        return mediaTypeJList;
    }


    @Override
    public void valueChanged(ListSelectionEvent e) {
        Matcher<Media> newMatcher = new MediatypeMatcher(selectedTypes);

        fireChanged(newMatcher);
    }

    private EventList<Media.SupportedMediaType> mediaTypeList;
    private EventList<Media.SupportedMediaType> selectedTypes;
    private JList mediaTypeJList;
    private JScrollPane mediaTypeComponent;
}
