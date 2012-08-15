/**
 * ======================== legal notice ======================
 * 
 * File:      PlayerDefinitionTableFormat.java
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
package de.schwarzrot.control.table;


import ca.odell.glazedlists.gui.WritableTableFormat;
import de.schwarzrot.base.util.ApplicationServiceProvider;
import de.schwarzrot.base.util.MessageBundle;
import de.schwarzrot.media.domain.PlayerDefinition;


public class PlayerDefinitionTableFormat implements WritableTableFormat<PlayerDefinition> {
    private static MessageBundle bundle;
    protected static final String KEY_0 = PlayerDefinitionTableFormat.class.getSimpleName() + ".col0";
    protected static final String KEY_1 = PlayerDefinitionTableFormat.class.getSimpleName() + ".col1";


    @Override
    public int getColumnCount() {
        return 2;
    }


    @Override
    public String getColumnName(int column) {
        if (bundle == null)
            bundle = ApplicationServiceProvider.getService(MessageBundle.class);

        switch (column) {
        case 0:
            return bundle.getMessage(KEY_0);
        case 1:
            return bundle.getMessage(KEY_1);
        default:
            throw new IndexOutOfBoundsException();
        }
    }


    @Override
    public Object getColumnValue(PlayerDefinition pd, int column) {
        switch (column) {
        case 0:
            return pd.getMediaType().name();
        case 1:
            return pd.getCommandLine();
        default:
            throw new IndexOutOfBoundsException();
        }
    }


    public int getColumnWidth(int column) {
        switch (column) {
        case 0:
            return 150;
        case 1:
            return -1;
        default:
            throw new IndexOutOfBoundsException();
        }
    }


    @Override
    public boolean isEditable(PlayerDefinition pd, int column) {
        switch (column) {
        case 0:
            return false;
        case 1:
            return true;
        default:
            throw new IndexOutOfBoundsException();
        }
    }


    @Override
    public PlayerDefinition setColumnValue(PlayerDefinition pd, Object value, int column) {
        switch (column) {
        case 0:
            break;
        case 1:
            pd.setCommandLine(value.toString());
            break;
        default:
            throw new IndexOutOfBoundsException();
        }
        return pd;
    }
}
