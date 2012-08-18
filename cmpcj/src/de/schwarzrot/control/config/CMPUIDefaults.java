package de.schwarzrot.control.config;


import java.awt.Color;
import java.util.HashMap;
import java.util.Map;
import javax.swing.UIManager;
import de.schwarzrot.control.app.UIDefaults;


public class CMPUIDefaults implements UIDefaults {
    private static final Map<String, Color> theme;


    @Override
    public void apply() {
        for (String key : theme.keySet())
            UIManager.put(key, theme.get(key));
    }


    @Override
    public Color getColor(String key) {
        if (theme.containsKey(key))
            return theme.get(key);
        Object rv = UIManager.get(key);

        if (rv instanceof Color)
            return (Color) rv;
        return Color.GRAY;
    }

    static {
        theme = new HashMap<String, Color>();
    }
}
