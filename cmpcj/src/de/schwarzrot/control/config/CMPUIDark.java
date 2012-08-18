package de.schwarzrot.control.config;


import java.awt.Color;
import java.util.HashMap;
import java.util.Map;
import javax.swing.UIManager;
import de.schwarzrot.control.app.UIDefaults;


public class CMPUIDark implements UIDefaults {
    private static final Color DarkBlue;
    private static final Map<String, Color> theme;


    public void apply() {
        for (String key : theme.keySet())
            UIManager.put(key, theme.get(key));
    }


    public Color getColor(String key) {
        if (theme.containsKey(key))
            return theme.get(key);
        Object rv = UIManager.get(key);

        if (rv instanceof Color)
            return (Color) rv;
        return Color.GRAY;
    }

    static {
        DarkBlue = new Color(0, 0, 50);
        theme = new HashMap<String, Color>();

        theme.put("control", Color.BLACK); // Dialog, Panel, defaults
        theme.put("nimbusBase", Color.BLUE);
        theme.put("nimbusBlueGrey", Color.DARK_GRAY);
        theme.put("nimbusBorder", Color.BLACK);
        theme.put("nimbusFocus", Color.CYAN);
        theme.put("nimbusLightBackground", Color.BLACK); // Tree, Textfield
        theme.put("Table.alternateRowColor", DarkBlue);
        theme.put("Table[Enabled+Selected].textForeground", Color.CYAN);
        theme.put("Tree.selectionForeground", Color.CYAN); // Tree selected Text
        theme.put("info", Color.BLUE); // info background
        theme.put("text", Color.WHITE); // inactive dockable tabs foreground (includes textForeground, menuText, infoText)
        theme.put("menu", Color.DARK_GRAY); // inactive dockable tabs background
        theme.put("nimbusSelectionBackground", Color.BLUE);
        theme.put("nimbusSelection", Color.BLUE); // active dockable tabs background
        theme.put("menuText", Color.YELLOW); // inactive dockable tabs foreground 
        theme.put("textForeground", Color.WHITE); // standard Text
    }
}
