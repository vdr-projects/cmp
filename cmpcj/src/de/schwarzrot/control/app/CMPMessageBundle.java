/**
 * ======================== legal notice ======================
 * 
 * File: MCCMessageBundle.java Created: 13. June 2012, 04:57 Author: <a
 * href="mailto:geronimo013@gmx.de">Geronimo</a> Project: cmpc - a java frontend
 * (client) part of compound media player uses external players to play the
 * media
 * 
 * CMP - compound media player
 * 
 * is a client/server mediaplayer intended to play any media from any
 * workstation without the need to export or mount shares. cmps is an easy to
 * use backend with a (ready to use) HTML-interface. Additionally the backend
 * supports authentication via HTTP-digest authorization. cmpc is a client with
 * vdr-like osd-menues.
 * 
 * Copyright (c) 2012 Reinhard Mantey, some rights reserved! published under
 * Creative Commons by-sa For details see
 * http://creativecommons.org/licenses/by-sa/3.0/
 * 
 * The cmp project's homepage is at
 * http://projects.vdr-developer.org/projects/cmp
 * 
 * --------------------------------------------------------------
 */
package de.schwarzrot.control.app;


import java.util.MissingResourceException;
import java.util.ResourceBundle;
import de.schwarzrot.base.util.MessageBundle;


public class CMPMessageBundle implements MessageBundle {
    public static final String MCC_0 = "MCC_0";
    public static final String MCC_1 = "MCC_1";
    public static final String MCC_2 = "MCC_2";
    public static final String MCC_3 = "MCC_3";
    public static final String MCC_4 = "MCC_4";
    public static final String MCC_5 = "MCC_5";
    public static final String MCC_6 = "MCC_6";
    public static final String MCC_7 = "MCC_7";
    public static final String MCC_8 = "MCC_8";
    public static final String MCC_9 = "MCC_9";
    public static final String MCC_12 = "MCC_12";
    public static final String MCC_13 = "MCC_13";
    public static final String MCC_14 = "MCC_14";
    public static final String MCC_15 = "MCC_15";
    public static final String MCC_16 = "MCC_16";
    public static final String MCC_17 = "MCC_17";
    public static final String MCC_18 = "MCC_18";
    public static final String MCC_19 = "MCC_19";
    public static final String MCC_20 = "MCC_20";
    public static final String MCC_21 = "MCC_21";
    public static final String MCC_22 = "MCC_22";
    public static final String MCC_29 = "MCC_29";
    public static final String MCC_31 = "MCC_31";
    public static final String MCC_33 = "MCC_33";
    public static final String MCC_35 = "MCC_35";
    public static final String PTF_0 = "PTF_0";
    public static final String PTF_1 = "PTF_1";
    public static final String MTF_0 = "MTF_0";
    public static final String MTF_1 = "MTF_1";
    public static final String MTF_2 = "MTF_2";


    @Override
    public String getMessage(String key) {
        try {
            return RESOURCE_BUNDLE.getString(key);
        } catch (MissingResourceException e) {
            return '!' + key + '!';
        }
    }

    private final String BUNDLE_NAME = "de.schwarzrot.control.app.lang.messages"; //$NON-NLS-1$
    private final ResourceBundle RESOURCE_BUNDLE = ResourceBundle.getBundle(BUNDLE_NAME);
}
