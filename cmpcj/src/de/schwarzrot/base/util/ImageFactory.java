/**
 * ======================== legal notice ======================
 * 
 * File:      ImageFactory.java
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
package de.schwarzrot.base.util;


import java.awt.Image;
import java.awt.image.BufferedImage;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;
import java.util.ResourceBundle;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;


public class ImageFactory {
    public ImageIcon getIcon(String key) {
        return getIcon(key, 16, 16);
    }


    public ImageIcon getIcon(String key, int width, int height) {
        if (!iconPool.containsKey(key))
            iconPool.put(key, new ImageIcon(getImage(key, width, height)));

        return iconPool.get(key);
    }


    public Image getImage(String key, int width, int height) {
        ClassLoader cl = getClass().getClassLoader();
        BufferedImage img = null;
        URL url;

        try {
            String imgPath = RESOURCE_BUNDLE.getString(key);
            url = cl.getResource(imgPath);
            img = ImageIO.read(url);

            return img.getScaledInstance(width, height, Image.SCALE_SMOOTH);
        } catch (Throwable t) {
            System.err.println("failed to read key: " + key);
            t.printStackTrace();
        }
        return null;
    }

    private Map<String, ImageIcon> iconPool = new HashMap<String, ImageIcon>();
    private final String BUNDLE_NAME = "de.schwarzrot.control.app.lang.images";
    private final ResourceBundle RESOURCE_BUNDLE = ResourceBundle.getBundle(BUNDLE_NAME);
}
