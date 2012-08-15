/**
 * ======================== legal notice ======================
 * 
 * File:      TreeSourceAndDestTransferHandler.java
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
package de.schwarzrot.control.dnd;


import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.io.File;
import java.util.List;
import java.util.Map;
import javax.swing.JComponent;
import javax.swing.JTree;
import javax.swing.TransferHandler;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreePath;
import ca.odell.glazedlists.EventList;
import de.schwarzrot.media.domain.AbstractMediaNode;
import de.schwarzrot.media.domain.Genre;
import de.schwarzrot.media.domain.Media;


public class TreeSourceAndDestTransferHandler extends TransferHandler {
    private static final long serialVersionUID = 713L;


    public TreeSourceAndDestTransferHandler(JTree tree, Map<File, DefaultMutableTreeNode> cache,
            EventList<AbstractMediaNode> changes) {
        this.tree = tree;
        nodeCache = cache;
        this.changes = changes;
    }


    // dest
    @Override
    public boolean canImport(TransferHandler.TransferSupport support) {
        if (!support.isDrop())
            return false;
        support.setShowDropLocation(true);

        if (support.isDataFlavorSupported(TreePathTransferable.TreePathFlavor) && support.getDropAction() == MOVE)
            return true;
        if (support.isDataFlavorSupported(DataFlavor.javaFileListFlavor))
            return true;

        return false;
    }


    // source
    @Override
    public Transferable createTransferable(JComponent c) {
        if (c != tree)
            return null;
        TreePath selectionPath = tree.getSelectionPath();

        return new TreePathTransferable(selectionPath);
    }


    // source
    @Override
    public void exportDone(JComponent c, Transferable data, int action) {
        tree.updateUI();
    }


    // source
    @Override
    public int getSourceActions(JComponent c) {
        return MOVE;
    }


    // dest
    @Override
    public boolean importData(TransferHandler.TransferSupport support) {
        if (!canImport(support))
            return false;
        JTree.DropLocation dl = (JTree.DropLocation) support.getDropLocation();
        TreePath targetPath = tree.getClosestPathForLocation(dl.getDropPoint().x, dl.getDropPoint().y);
        DefaultMutableTreeNode targetNode = (DefaultMutableTreeNode) targetPath.getLastPathComponent();

        if (support.isDataFlavorSupported(TreePathTransferable.TreePathFlavor)) {
            // move a genre in tree
            try {
                TreePath sourcePath = (TreePath) support.getTransferable().getTransferData(
                        TreePathTransferable.TreePathFlavor);
                DefaultMutableTreeNode transferNode = (DefaultMutableTreeNode) sourcePath.getLastPathComponent();
                DefaultMutableTreeNode sourceParentNode = (DefaultMutableTreeNode) transferNode.getParent();
                Genre target = (Genre) targetNode.getUserObject();
                Genre transfer = (Genre) transferNode.getUserObject();

                //                System.out.println("importData() targetPath: " + targetPath);
                //                System.out.println("importData() sourcePath: " + sourcePath);

                sourceParentNode.remove(transferNode);
                targetNode.add(transferNode);
                nodeCache.remove(transfer.getRealPath());
                //                System.out.println("old path of genre to move: " + transfer.getRealPath().getAbsolutePath());
                transfer.setParent(target);
                //                System.out.println("new path of moved genre: " + transfer.getRealPath().getAbsolutePath());
                nodeCache.put(transfer.getRealPath(), transferNode);
                transfer.update();
                refreshNodeCache();
                if (!changes.contains(transfer)) {
                    changes.getReadWriteLock().writeLock().lock();
                    changes.add(transfer);
                    changes.getReadWriteLock().writeLock().unlock();
                }
            } catch (Throwable t) {
                t.printStackTrace();
            }
        } else if (support.isDataFlavorSupported(DataFlavor.javaFileListFlavor)) {
            // move media files from one genre to another (no visible tree change)
            try {
                @SuppressWarnings("unchecked")
                List<File> fileList = (List<File>) support.getTransferable().getTransferData(
                        DataFlavor.javaFileListFlavor);

                for (File f : fileList)
                    move2TargetNode(targetNode, f); // each media can have different parent, so don't optimize here                
            } catch (Throwable t) {
                t.printStackTrace();
            }
        }
        return false;
    }


    protected void cacheNode(DefaultMutableTreeNode node) {
        Genre g = (Genre) node.getUserObject();

        nodeCache.put(g.getRealPath(), node);
        for (int i = 0; i < node.getChildCount(); ++i) {
            DefaultMutableTreeNode sub = (DefaultMutableTreeNode) node.getChildAt(i);

            cacheNode(sub);
        }
    }


    protected void move2TargetNode(DefaultMutableTreeNode targetNode, File mediaPath) {
        if (targetNode == null || mediaPath == null)
            return;
        Genre targetGenre = (Genre) targetNode.getUserObject();
        DefaultMutableTreeNode node = nodeCache.get(mediaPath.getParentFile());

        if (targetGenre != null && node != null) {
            Media transferMedia = null;
            Genre sourceGenre = (Genre) node.getUserObject();

            for (Media m : sourceGenre.getMediaList()) {
                if (m.getRealPath().equals(mediaPath)) {
                    transferMedia = m;
                    break;
                }
            }

            if (transferMedia != null) {
                System.out.println("old path of media to transfer: " + transferMedia.getRealPath().getAbsolutePath());
                transferMedia.setParent(targetGenre);
                System.out.println("new path of transferred media: " + transferMedia.getRealPath().getAbsolutePath());
                if (!changes.contains(transferMedia)) {
                    changes.getReadWriteLock().writeLock().lock();
                    changes.add(transferMedia);
                    changes.getReadWriteLock().writeLock().unlock();
                }
            }
        }
    }


    protected void refreshNodeCache() {
        nodeCache.clear();
        DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getModel().getRoot();

        cacheNode(node);
    }

    private JTree tree;
    private EventList<AbstractMediaNode> changes;
    private Map<File, DefaultMutableTreeNode> nodeCache;
}
