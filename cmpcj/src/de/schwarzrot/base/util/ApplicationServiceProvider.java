/**
 * ======================== legal notice ======================
 * 
 * File:      ApplicationServiceProvider.java
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


public class ApplicationServiceProvider {
    private static Map<Class<?>, Object> knownServices = new HashMap<Class<?>, Object>();


    @SuppressWarnings("unchecked")
    public static <S extends Object> S getService(Class<S> clazz) {
        return (S) knownServices.get(clazz);
    }


    public static <S extends Object> boolean hasService(Class<S> clazz) {
        return knownServices.containsKey(clazz);
    }


    public static <S extends Object> void registerService(Class<S> clazz, S service) {
        knownServices.put(clazz, service);
    }
}
