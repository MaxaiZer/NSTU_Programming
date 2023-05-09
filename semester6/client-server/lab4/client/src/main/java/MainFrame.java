import static java.awt.FileDialog.SAVE;
import java.io.IOException;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import net.NetworkRepository;
import net.RESTNetworkRepository;

public class MainFrame extends javax.swing.JFrame {
   
    private NetworkRepository repository = new RESTNetworkRepository();
    private FrameNetworkListener networkListener = null;
    
    public MainFrame() {
        initComponents();      
        networkListener = new FrameNetworkListener(objectsPanel);
        repository.addListener(networkListener);
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
        netButtonsPanel = new javax.swing.JPanel();
        removeObjectButton = new javax.swing.JButton();
        requestObjectButton = new javax.swing.JButton();
        requestNamesButton = new javax.swing.JButton();
        sendObjectButton = new javax.swing.JButton();
        requestObjectsButton = new javax.swing.JButton();
        inputDigitPane = new javax.swing.JOptionPane();
        objectsPanel = new ObjectsPanel();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu2 = new javax.swing.JMenu();
        openFileButton = new javax.swing.JMenuItem();
        saveAsFileButton = new javax.swing.JMenuItem();

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
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(addButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(deleteButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
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
                .addGap(8, 8, 8)
                .addGroup(buttonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(resumeButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(resumeAllButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(stopAllButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(stopButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(deleteButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(addButton, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                .addContainerGap(10, Short.MAX_VALUE))
        );

        removeObjectButton.setText("Удалить объект по id");
        removeObjectButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                removeObjectButtonMouseClicked(evt);
            }
        });

        requestObjectButton.setText("Запросить объект по id");
        requestObjectButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                requestObjectButtonMouseClicked(evt);
            }
        });

        requestNamesButton.setText("Запросить список имён");
        requestNamesButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                requestNamesButtonMouseClicked(evt);
            }
        });

        sendObjectButton.setText("Отправить объект по id");
        sendObjectButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                sendObjectButtonMouseClicked(evt);
            }
        });

        requestObjectsButton.setText("Запросить объекты");
        requestObjectsButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                requestObjectsButtonMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout netButtonsPanelLayout = new javax.swing.GroupLayout(netButtonsPanel);
        netButtonsPanel.setLayout(netButtonsPanelLayout);
        netButtonsPanelLayout.setHorizontalGroup(
            netButtonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(removeObjectButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(requestNamesButton, javax.swing.GroupLayout.DEFAULT_SIZE, 199, Short.MAX_VALUE)
            .addComponent(sendObjectButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(requestObjectButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(requestObjectsButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        netButtonsPanelLayout.setVerticalGroup(
            netButtonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(netButtonsPanelLayout.createSequentialGroup()
                .addComponent(requestObjectsButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(requestObjectButton)
                .addGap(11, 11, 11)
                .addComponent(requestNamesButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(sendObjectButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(removeObjectButton)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        inputDigitPane.setToolTipText("Введите число:");
        inputDigitPane.setWantsInput(true);

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
            .addGap(0, 572, Short.MAX_VALUE)
        );
        objectsPanelLayout.setVerticalGroup(
            objectsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 330, Short.MAX_VALUE)
        );

        jMenu2.setText("Файл");

        openFileButton.setText("открыть");
        openFileButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                openFileButtonActionPerformed(evt);
            }
        });
        jMenu2.add(openFileButton);

        saveAsFileButton.setText("сохранить");
        saveAsFileButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                saveAsFileButtonActionPerformed(evt);
            }
        });
        jMenu2.add(saveAsFileButton);

        jMenuBar1.add(jMenu2);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(buttonsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(netButtonsPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(objectsPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGap(263, 263, 263)
                    .addComponent(inputDigitPane, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(230, Short.MAX_VALUE)))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(buttonsPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(netButtonsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(objectsPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 22, Short.MAX_VALUE)))
                .addContainerGap())
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGap(160, 160, 160)
                    .addComponent(inputDigitPane, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(142, Short.MAX_VALUE)))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents
 
    public void update() {
        objectsPanel.moveAllObjects();
        repaint();
    }
    
    private void addButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_addButtonMouseClicked
        objectsPanel.onAddButtonClick();
    }//GEN-LAST:event_addButtonMouseClicked

    private void deleteButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_deleteButtonMouseClicked
        objectsPanel.onDeleteButtonClick();
    }//GEN-LAST:event_deleteButtonMouseClicked

    private void resumeButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_resumeButtonMouseClicked
        objectsPanel.onResumeButtonClick();
    }//GEN-LAST:event_resumeButtonMouseClicked

    private void resumeAllButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_resumeAllButtonMouseClicked
         objectsPanel.onResumeAllButtonClick();
    }//GEN-LAST:event_resumeAllButtonMouseClicked

    private void stopButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_stopButtonMouseClicked
        objectsPanel.onStopButtonClick();
    }//GEN-LAST:event_stopButtonMouseClicked
  
    private void stopAllButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_stopAllButtonMouseClicked
        objectsPanel.onStopAllButtonClick();
    }//GEN-LAST:event_stopAllButtonMouseClicked

    private void objectsPanelMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_objectsPanelMouseClicked
        objectsPanel.onMouseClicked(evt);
    }//GEN-LAST:event_objectsPanelMouseClicked

    private void openFileButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_openFileButtonActionPerformed
        var fc = new JFileChooser();
        
        int result = fc.showOpenDialog(jMenu2);
        if (result != fc.APPROVE_OPTION) return;
        
        var file = fc.getSelectedFile();
        try {
            objectsPanel.open(file);
        } catch (IOException ex) { 
            showError("Error read from file, message: " + ex.getMessage());
        } catch (ClassNotFoundException ex) {
            showError("Deserialization error, message: " + ex.getMessage());
        }
    }//GEN-LAST:event_openFileButtonActionPerformed

    private void saveAsFileButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_saveAsFileButtonActionPerformed
        var fc = new JFileChooser();
        fc.setDialogType(SAVE);
        
        int result = fc.showOpenDialog(jMenu2);
        if (result != fc.APPROVE_OPTION) return;
        
        var file = fc.getSelectedFile();
        try {
            objectsPanel.save(file);
        } catch (IOException ex) {
            showError("Error write to file, message: " + ex.getMessage());
        }
    }//GEN-LAST:event_saveAsFileButtonActionPerformed

    private void sendObjectButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_sendObjectButtonMouseClicked
        int id = getDigitFromUser();
        var obj = objectsPanel.getObjectById(id);
        
        if (obj.isPresent())
            repository.sendObject(obj.get());
        else
            showError("Invalid id");    
    }//GEN-LAST:event_sendObjectButtonMouseClicked

    private void requestNamesButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_requestNamesButtonMouseClicked
         repository.requestObjectsListNames();
    }//GEN-LAST:event_requestNamesButtonMouseClicked

    private void requestObjectButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_requestObjectButtonMouseClicked
        int id = getDigitFromUser();
        repository.requestObjectByIndex(id); 
    }//GEN-LAST:event_requestObjectButtonMouseClicked

    private void requestObjectsButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_requestObjectsButtonMouseClicked
        repository.requestObjectsList();
    }//GEN-LAST:event_requestObjectsButtonMouseClicked

    private void removeObjectButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_removeObjectButtonMouseClicked
        int id = getDigitFromUser();
        repository.removeObjectByIndex(id); 
    }//GEN-LAST:event_removeObjectButtonMouseClicked

    private int getDigitFromUser() {
        String input = inputDigitPane.showInputDialog(null, "Введите число:");
        return Integer.parseInt(input);
    }
    
    private void showError(String message) {
        JOptionPane.showMessageDialog(null, message, "Error", JOptionPane.ERROR_MESSAGE);
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton addButton;
    private javax.swing.JPanel buttonsPanel;
    private javax.swing.JButton deleteButton;
    private javax.swing.JOptionPane inputDigitPane;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JPanel netButtonsPanel;
    private ObjectsPanel objectsPanel;
    private javax.swing.JMenuItem openFileButton;
    private javax.swing.JButton removeObjectButton;
    private javax.swing.JButton requestNamesButton;
    private javax.swing.JButton requestObjectButton;
    private javax.swing.JButton requestObjectsButton;
    private javax.swing.JButton resumeAllButton;
    private javax.swing.JButton resumeButton;
    private javax.swing.JMenuItem saveAsFileButton;
    private javax.swing.JButton sendObjectButton;
    private javax.swing.JButton stopAllButton;
    private javax.swing.JButton stopButton;
    // End of variables declaration//GEN-END:variables
}
