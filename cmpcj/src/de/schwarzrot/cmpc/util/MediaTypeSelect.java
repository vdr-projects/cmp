/**
 * ======================== legal notice ======================
 * 
 * File:      MediaTypeSelect.java
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
package de.schwarzrot.cmpc.util;


import java.awt.Color;
import java.awt.Component;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.net.URL;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.ListCellRenderer;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import ca.odell.glazedlists.EventList;
import ca.odell.glazedlists.UniqueList;
import ca.odell.glazedlists.matchers.AbstractMatcherEditor;
import ca.odell.glazedlists.matchers.Matcher;
import ca.odell.glazedlists.swing.DefaultEventListModel;
import ca.odell.glazedlists.swing.DefaultEventSelectionModel;
import de.schwarzrot.cmpc.domain.Media;


public class MediaTypeSelect extends AbstractMatcherEditor<Media> implements ListSelectionListener {
    public class MediaTypeCellRenderer extends JLabel implements ListCellRenderer {
        private static final long serialVersionUID = 713L;


        public MediaTypeCellRenderer() {
            loadImages();
        }


        @Override
        public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected,
                boolean cellHasFocus) {
            if (isSelected) {
                setBackground(list.getSelectionBackground());
                setForeground(list.getSelectionForeground());
            } else {
                setBackground(list.getBackground());
                setForeground(list.getForeground());
            }
            ImageIcon icon = images[((Media.SupportedMediaType) value).ordinal()];
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
            BufferedImage img = null;
            ClassLoader cl = getClass().getClassLoader();
            URL url;

            images = new ImageIcon[iconFiles.length];
            for (int i = 0; i < iconFiles.length; ++i) {
                try {
                    url = cl.getResource(iconFiles[i]);

                    img = ImageIO.read(url);
                    images[i] = new ImageIcon(img.getScaledInstance(110, 110, Image.SCALE_SMOOTH));
                } catch (Throwable t) {
                    System.err.println("failed to read image from " + iconFiles[i]);
                    t.printStackTrace();
                }
            }
        }

        ImageIcon[] images;
    }


    public MediaTypeSelect(EventList<Media> source) {
        EventList<Media.SupportedMediaType> mediaTypeNonUnique = new MediaPool2TypeList(source);

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
    }


    public JList getJList() {
        return mediaTypeJList;
    }


    @Override
    public void valueChanged(ListSelectionEvent e) {
        Matcher<Media> newMatcher = new MediaForTypeMatcher(selectedTypes);

        fireChanged(newMatcher);
    }

    private EventList<Media.SupportedMediaType> mediaTypeList;
    private EventList<Media.SupportedMediaType> selectedTypes;
    private JList mediaTypeJList;
    private static final String[] iconFiles;
    static {
        iconFiles = new String[] { "images/folder_black.png", "images/folder_black_music.png",
                "images/folder_black_movies.png", "images/folder_black_dvd.png", "images/folder_black_vdr_old.png",
                "images/folder_black_vdr.png", "images/folder_black_photos.png", "images/folder_black.png" };
    }
}
