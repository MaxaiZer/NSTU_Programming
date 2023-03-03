import Objects.*;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class MainFrame extends javax.swing.JFrame {

    private java.util.List<GraphicObject> objects = new ArrayList<>();
    private Graphics objectsPanelGraphics;
    
    boolean editorModeEnabled = false;   
    ClickHandler panelClickHandler = (e) -> {};  
    
    public MainFrame() {
        initComponents();
        objectsPanelGraphics = ObjectsPanel.getGraphics();
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        ObjectsPanel = new javax.swing.JPanel();
        ButtonsPanel = new javax.swing.JPanel();
        StopButton = new javax.swing.JButton();
        StopAllButton = new javax.swing.JButton();
        ResumeAllButton = new javax.swing.JButton();
        ResumeButton = new javax.swing.JButton();
        AddButton = new javax.swing.JButton();
        DeleteButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        ObjectsPanel.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        ObjectsPanel.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                ObjectsPanelMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout ObjectsPanelLayout = new javax.swing.GroupLayout(ObjectsPanel);
        ObjectsPanel.setLayout(ObjectsPanelLayout);
        ObjectsPanelLayout.setHorizontalGroup(
            ObjectsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        ObjectsPanelLayout.setVerticalGroup(
            ObjectsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 378, Short.MAX_VALUE)
        );

        StopButton.setText("Остановить");
        StopButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        StopButton.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        StopButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        StopButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                StopButtonMouseClicked(evt);
            }
        });

        StopAllButton.setText("Остановить все");
        StopAllButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        StopAllButton.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        StopAllButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        StopAllButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                StopAllButtonMouseClicked(evt);
            }
        });

        ResumeAllButton.setText("Возобновить все");
        ResumeAllButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        ResumeAllButton.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        ResumeAllButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        ResumeAllButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                ResumeAllButtonMouseClicked(evt);
            }
        });

        ResumeButton.setText("Возобновить");
        ResumeButton.setToolTipText("");
        ResumeButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        ResumeButton.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        ResumeButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        ResumeButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                ResumeButtonMouseClicked(evt);
            }
        });

        AddButton.setText("Добавить");
        AddButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        AddButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                AddButtonMouseClicked(evt);
            }
        });

        DeleteButton.setText("Удалить");
        DeleteButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        DeleteButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                DeleteButtonMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout ButtonsPanelLayout = new javax.swing.GroupLayout(ButtonsPanel);
        ButtonsPanel.setLayout(ButtonsPanelLayout);
        ButtonsPanelLayout.setHorizontalGroup(
            ButtonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(ButtonsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(AddButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(DeleteButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 104, Short.MAX_VALUE)
                .addComponent(ResumeButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(ResumeAllButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(StopButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(StopAllButton)
                .addContainerGap())
        );
        ButtonsPanelLayout.setVerticalGroup(
            ButtonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(ButtonsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(ButtonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(ButtonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(AddButton)
                        .addComponent(DeleteButton))
                    .addGroup(ButtonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(ResumeButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(ResumeAllButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(StopAllButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(StopButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(8, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(ObjectsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addContainerGap())
                    .addComponent(ButtonsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(ButtonsPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(ObjectsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents
 
    private void AddButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_AddButtonMouseClicked
        panelClickHandler = ((e) -> { 
            
        GraphicObject obj = null;
            
        var r = new Random();
        if (r.nextInt() % 2 == 0)
            obj = new Polygon(e.getX(), e.getY(), Color.BLUE, 5, 30);
        else {
            try {
                obj = new Image(e.getX(), e.getY(), null, "dur1.png");
            } catch (IOException ex) {
                System.out.println("Oops!");
            }
        }
        objects.add(obj);
        });
    }//GEN-LAST:event_AddButtonMouseClicked

    private void DeleteButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_DeleteButtonMouseClicked
       
        editorModeEnabled = true;
        panelClickHandler = (e) -> { GetPickedObject(e).ifPresent(
                (obj) -> {objects.remove(obj);}
        ); };
    }//GEN-LAST:event_DeleteButtonMouseClicked

    private void ResumeButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_ResumeButtonMouseClicked

        editorModeEnabled = true;
        panelClickHandler = (e) -> { GetPickedObject(e).ifPresent(
                (obj) -> {obj.canMove = true;}
        ); };
    }//GEN-LAST:event_ResumeButtonMouseClicked

    private void ResumeAllButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_ResumeAllButtonMouseClicked
        editorModeEnabled = false;
        objects.forEach(obj -> obj.canMove = true);
    }//GEN-LAST:event_ResumeAllButtonMouseClicked

    private void StopButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_StopButtonMouseClicked
        
        editorModeEnabled = true;
        panelClickHandler = (e) -> { GetPickedObject(e).ifPresent(
                (obj) -> {obj.canMove = false;}
        ); };
    }//GEN-LAST:event_StopButtonMouseClicked
  
    private void StopAllButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_StopAllButtonMouseClicked
        editorModeEnabled = false;
        objects.forEach(obj -> obj.canMove = false);
    }//GEN-LAST:event_StopAllButtonMouseClicked

    private void ObjectsPanelMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_ObjectsPanelMouseClicked
        panelClickHandler.OnClick(evt);
    }//GEN-LAST:event_ObjectsPanelMouseClicked

    private Optional<GraphicObject> GetPickedObject(MouseEvent e) {
         
        Point p = e.getPoint();      
        GraphicObject picked = null;
        
        for(GraphicObject obj: objects) {
            if (obj.Contains(p.x, p.y)) {
                picked = obj;
                break;
            }
        }

        return Optional.ofNullable(picked);
    }
    
    public void Update() {
        objects.forEach(obj -> obj.Move());
        
        var dim = ObjectsPanel.getBounds();     
        var img = createImage(dim.width, dim.height);
        
        var imgGraphics = img.getGraphics();
        imgGraphics.setColor(ObjectsPanel.getBackground());
        imgGraphics.fillRect(0, 0, dim.width, dim.height);
      //  this.repaint();
        
        for (int i = 0; i < objects.size(); i++) {
            
            if (editorModeEnabled)
                 objects.get(i).DrawRectangle(imgGraphics, Color.GRAY);
            
            objects.get(i).Draw(imgGraphics);          
        }
        objectsPanelGraphics.drawImage(img, -10, 14, ObjectsPanel);
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton AddButton;
    private javax.swing.JPanel ButtonsPanel;
    private javax.swing.JButton DeleteButton;
    private javax.swing.JPanel ObjectsPanel;
    private javax.swing.JButton ResumeAllButton;
    private javax.swing.JButton ResumeButton;
    private javax.swing.JButton StopAllButton;
    private javax.swing.JButton StopButton;
    // End of variables declaration//GEN-END:variables
}
