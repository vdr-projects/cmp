/**
 * ======================== legal notice ======================
 * 
 * File: AbstractDialog.java Created: 13. June 2012, 04:57 Author: <a
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
package de.schwarzrot.base.util;


import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JPanel;


public abstract class AbstractDialog extends JDialog {
    public static final int RESET_OPTION = -1;
    public static final int CLOSE_OPTION = 0;
    public static final int CANCEL_OPTION = 1;
    public static final int APPROVE_OPTION = 2;
    private static final long serialVersionUID = 713L;
    public enum DialogMode {
        CLOSE, CANCEL, CANCEL_APPROVE, RESET_CANCEL_APPROVE
    }
    public enum Orientation {
        Left, Center, Right
    };


    protected AbstractDialog(Window parent, boolean modal, DialogMode dialogMode, Orientation buttonOrientation) {
        super(parent, "dummy", modal ? JDialog.ModalityType.APPLICATION_MODAL : JDialog.ModalityType.MODELESS);
        msgBundle = ApplicationServiceProvider.getService(MessageBundle.class);
        setTitle(msgBundle.getMessage(getClass().getSimpleName() + ".title"));
        this.dialogMode = dialogMode;
        this.buttonOrientation = buttonOrientation;
    }


    public JComponent createButtons() {
        JPanel rv = new JPanel();
        JButton button = null;

        switch (buttonOrientation) {
        case Left:
            rv.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 5));
            break;

        case Right:
            rv.setLayout(new FlowLayout(FlowLayout.RIGHT, 10, 5));
            break;

        default:
            rv.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 5));
            break;
        }

        switch (dialogMode) {
        case RESET_CANCEL_APPROVE:
            button = createButton(".Reset");
            button.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent ae) {
                    result = RESET_OPTION;
                    performReset();
                    setVisible(false);
                }
            });
            rv.add(button);
        case CANCEL_APPROVE:
            button = createButton(".Approve");
            button.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent ae) {
                    result = APPROVE_OPTION;
                    performApprove();
                    setVisible(false);
                }
            });
            rv.add(button);
        case CANCEL:
            button = createButton(".Cancel");
            button.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent ae) {
                    result = CANCEL_OPTION;
                    performCancel();
                    setVisible(false);
                }
            });
            rv.add(button);
            break;
        default:
            button = createButton(".Close");
            button.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent ae) {
                    result = CLOSE_OPTION;
                    performClose();
                    setVisible(false);
                }
            });
            rv.add(button);
        }
        return rv;
    }


    public abstract JComponent createContentPane();


    public int showDialog(Window parent) {
        getContentPane().add(createContentPane(), BorderLayout.CENTER);
        getContentPane().add(createButtons(), BorderLayout.SOUTH);
        pack();
        if (fixedSize != null) {
            setSize(fixedSize);
            setResizable(false);
        }
        setLocationRelativeTo(parent);
        setVisible(true);
        dispose();

        return result;
    }


    protected JButton createButton(String buttonID) {
        JButton button = new JButton(msgBundle.getMessage(getClass().getSimpleName() + buttonID));

        return button;
    }


    protected void performApprove() {
    }


    protected void performCancel() {
    }


    protected void performClose() {
    }


    protected void performReset() {
    }


    protected void setFixedSize(Dimension size) {
        fixedSize = size;
    }

    protected final MessageBundle msgBundle;
    private int result = CLOSE_OPTION;
    private Dimension fixedSize;
    private DialogMode dialogMode;
    private Orientation buttonOrientation;
}
