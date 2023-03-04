import Objects.*;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class MainFrame extends javax.swing.JFrame {
   
    public MainFrame() {
        initComponents();
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buttonsPanel = new javax.swing.JPanel();
        stopButton = new javax.swing.JButton();
        stopAllButton = new javax.swing.JButton();
        resumeAllButton = new javax.swing.JButton();
        resumeButton = new javax.swing.JButton();
        addButton = new javax.swing.JButton();
        deleteButton = new javax.swing.JButton();
        objectsPanel = new ObjectsPanel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        stopButton.setText("Остановить");
        stopButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        stopButton.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        stopButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        stopButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                stopButtonMouseClicked(evt);
            }
        });

        stopAllButton.setText("Остановить все");
        stopAllButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        stopAllButton.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        stopAllButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        stopAllButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                stopAllButtonMouseClicked(evt);
            }
        });

        resumeAllButton.setText("Возобновить все");
        resumeAllButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        resumeAllButton.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        resumeAllButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        resumeAllButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                resumeAllButtonMouseClicked(evt);
            }
        });

        resumeButton.setText("Возобновить");
        resumeButton.setToolTipText("");
        resumeButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        resumeButton.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);
        resumeButton.setVerticalTextPosition(javax.swing.SwingConstants.BOTTOM);
        resumeButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                resumeButtonMouseClicked(evt);
            }
        });

        addButton.setText("Добавить");
        addButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        addButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                addButtonMouseClicked(evt);
            }
        });

        deleteButton.setText("Удалить");
        deleteButton.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        deleteButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                deleteButtonMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout buttonsPanelLayout = new javax.swing.GroupLayout(buttonsPanel);
        buttonsPanel.setLayout(buttonsPanelLayout);
        buttonsPanelLayout.setHorizontalGroup(
            buttonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(buttonsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(addButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(deleteButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 104, Short.MAX_VALUE)
                .addComponent(resumeButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(resumeAllButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(stopButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(stopAllButton)
                .addContainerGap())
        );
        buttonsPanelLayout.setVerticalGroup(
            buttonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(buttonsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(buttonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(buttonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(addButton)
                        .addComponent(deleteButton))
                    .addGroup(buttonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(resumeButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(resumeAllButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(stopAllButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(stopButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(8, Short.MAX_VALUE))
        );

        objectsPanel.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        objectsPanel.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                objectsPanelMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout objectsPanelLayout = new javax.swing.GroupLayout(objectsPanel);
        objectsPanel.setLayout(objectsPanelLayout);
        objectsPanelLayout.setHorizontalGroup(
            objectsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        objectsPanelLayout.setVerticalGroup(
            objectsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 378, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(objectsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addContainerGap())
                    .addComponent(buttonsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(buttonsPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(objectsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents
 
    private void addButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_addButtonMouseClicked
        objectsPanel.switchEditMode(ObjectsPanel.EditMode.Add);
    }//GEN-LAST:event_addButtonMouseClicked

    private void deleteButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_deleteButtonMouseClicked
        objectsPanel.switchEditMode(ObjectsPanel.EditMode.Delete);
    }//GEN-LAST:event_deleteButtonMouseClicked

    private void resumeButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_resumeButtonMouseClicked
        objectsPanel.switchEditMode(ObjectsPanel.EditMode.Resume);
    }//GEN-LAST:event_resumeButtonMouseClicked

    private void resumeAllButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_resumeAllButtonMouseClicked
        objectsPanel.resumeAllObjects();
    }//GEN-LAST:event_resumeAllButtonMouseClicked

    private void stopButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_stopButtonMouseClicked
        objectsPanel.switchEditMode(ObjectsPanel.EditMode.Stop);
    }//GEN-LAST:event_stopButtonMouseClicked
  
    private void stopAllButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_stopAllButtonMouseClicked
        objectsPanel.stopAllObjects();
    }//GEN-LAST:event_stopAllButtonMouseClicked

    private void objectsPanelMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_objectsPanelMouseClicked
        objectsPanel.onMouseClicked(evt);
    }//GEN-LAST:event_objectsPanelMouseClicked
   
    public void update() {
        objectsPanel.moveAllObjects();
        repaint();
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton addButton;
    private javax.swing.JPanel buttonsPanel;
    private javax.swing.JButton deleteButton;
    private ObjectsPanel objectsPanel;
    private javax.swing.JButton resumeAllButton;
    private javax.swing.JButton resumeButton;
    private javax.swing.JButton stopAllButton;
    private javax.swing.JButton stopButton;
    // End of variables declaration//GEN-END:variables
}
