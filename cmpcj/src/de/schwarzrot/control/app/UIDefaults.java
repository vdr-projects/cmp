package de.schwarzrot.control.app;


import java.awt.Color;


public interface UIDefaults {
    public void apply();


    public Color getColor(String key);
}