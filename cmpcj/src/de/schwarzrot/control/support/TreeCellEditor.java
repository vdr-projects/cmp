package de.schwarzrot.control.support;


import java.util.List;
import javax.swing.JTree;
import javax.swing.event.CellEditorListener;
import javax.swing.event.ChangeEvent;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellEditor;
import javax.swing.tree.DefaultTreeCellRenderer;
import de.schwarzrot.media.domain.Genre;
import de.schwarzrot.media.service.AbstractMediaChangeCommand;
import de.schwarzrot.media.service.ChangeMediaCommand;


public class TreeCellEditor extends DefaultTreeCellEditor implements CellEditorListener {
    public TreeCellEditor(JTree tree, List<AbstractMediaChangeCommand> changes) {
        super(tree, (DefaultTreeCellRenderer) tree.getCellRenderer());
        this.changes = changes;
        addCellEditorListener(this);
    }


    @Override
    public void editingCanceled(ChangeEvent e) {
        System.out.println("editing cancelled");
    }


    @Override
    public void editingStopped(ChangeEvent e) {
        System.out.println("editing stopped");
        Genre genre = (Genre) editedNode.getUserObject();

        genre.setName((String) editedValue);
        if (!changes.contains(genre))
            changes.add(new ChangeMediaCommand(genre));
    }


    @Override
    public Object getCellEditorValue() {
        editedValue = super.getCellEditorValue();
        editedNode = (DefaultMutableTreeNode) lastPath.getLastPathComponent();
        Genre genre = (Genre) editedNode.getUserObject();

        return genre;
    }

    private Object editedValue;
    private DefaultMutableTreeNode editedNode;
    private List<AbstractMediaChangeCommand> changes;
}
