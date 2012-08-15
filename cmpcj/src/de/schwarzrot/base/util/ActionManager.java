/**
 * ======================== legal notice ======================
 * 
 * File:      ActionManager.java
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


import java.util.HashMap;
import java.util.Map;
import javax.swing.Action;
import javax.swing.JMenuItem;


public class ActionManager<E extends Enum<E>> {
    public ActionManager() {
        knownCallbacks = new HashMap<Enum<E>, CallbackDefinition<E>>();
    }


    public void addCallbackDefinition(CallbackDefinition<E> callbackDefinition) {
        knownCallbacks.put(callbackDefinition.getCallbackKey(), callbackDefinition);
    }


    public JMenuItem createMenuItem(Enum<E> cmd) {
        return null;
    }


    public Action getAction(Enum<E> cmd) {
        Action rv = null;

        if (knownCallbacks.containsKey(cmd))
            rv = knownCallbacks.get(cmd);

        return rv;
    }

    private Map<Enum<E>, CallbackDefinition<E>> knownCallbacks;
}
