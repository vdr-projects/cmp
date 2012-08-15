/**
 * ======================== legal notice ======================
 * 
 * File:      CallbackDefinition.java
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


import javax.swing.AbstractAction;


public abstract class CallbackDefinition<E extends Enum<E>> extends AbstractAction {
    private static final long serialVersionUID = 713L;
    private static final String IDENTIFIER = "CBIdentifier";


    public CallbackDefinition(E key) {
        this(key, true);
    }


    public CallbackDefinition(E key, boolean enabled) {
        MessageBundle mb = ApplicationServiceProvider.getService(MessageBundle.class);
        String actionKey = key.getClass().getSimpleName() + "." + key.name();

        putValue(IDENTIFIER, key);
        putValue(ACTION_COMMAND_KEY, actionKey);
        putValue(NAME, mb.getMessage(actionKey));
        putValue(LARGE_ICON_KEY, null);
        putValue(SMALL_ICON, null);
        putValue(SHORT_DESCRIPTION, mb.getMessage(actionKey + ".short.desc"));
        putValue(LONG_DESCRIPTION, mb.getMessage(actionKey + ".long.desc"));
        putValue(ACCELERATOR_KEY, null);
        setEnabled(enabled);
    }


    @SuppressWarnings("unchecked")
    public E getCallbackKey() {
        return (E) getValue(IDENTIFIER);
    }
}
