import static java.awt.FileDialog.SAVE;
import java.io.IOException;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import net.ConnectionHandler;
import net.UDPClient;
import net.UDPServer;

public class MainFrame extends javax.swing.JFrame {
   
    private ConnectionHandler connectionHandler = null;
    private Thread serverThread = null;
    private FrameConnectionListener connectionListener = null;
    
    public MainFrame() {
        initComponents();
        
        connectionListener = new FrameConnectionListener(objectsPanel);
        
        try {
            startClient();
        } catch (IOException ex) {
            showError(ex.getMessage());
        }
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
        jOptionPane = new javax.swing.JOptionPane();
        netButtonsPanel = new javax.swing.JPanel();
        startServerButton = new javax.swing.JRadioButton();
        disconnectButton = new javax.swing.JButton();
        requestClearButton = new javax.swing.JButton();
        requestObjectButton = new javax.swing.JButton();
        requestCountButton = new javax.swing.JButton();
        requestNamesButton = new javax.swing.JButton();
        sendObjectButton = new javax.swing.JButton();
        inputDigitPane = new javax.swing.JOptionPane();
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
            .addGroup(objectsPanelLayout.createSequentialGroup()
                .addGap(154, 154, 154)
                .addComponent(jOptionPane, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(154, Short.MAX_VALUE))
        );
        objectsPanelLayout.setVerticalGroup(
            objectsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(objectsPanelLayout.createSequentialGroup()
                .addGap(130, 130, 130)
                .addComponent(jOptionPane, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(130, Short.MAX_VALUE))
        );

        startServerButton.setText("Сервер");
        startServerButton.setToolTipText("");
        startServerButton.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                startServerButtonItemStateChanged(evt);
            }
        });

        disconnectButton.setText("Закрыть соединение");
        disconnectButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                disconnectButtonMouseClicked(evt);
            }
        });

        requestClearButton.setText("Запросить \nочистку\n");
        requestClearButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                requestClearButtonMouseClicked(evt);
            }
        });

        requestObjectButton.setText("Запросить объект по id");
        requestObjectButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                requestObjectButtonMouseClicked(evt);
            }
        });

        requestCountButton.setText("Запросить кол-во");
        requestCountButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                requestCountButtonMouseClicked(evt);
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

        javax.swing.GroupLayout netButtonsPanelLayout = new javax.swing.GroupLayout(netButtonsPanel);
        netButtonsPanel.setLayout(netButtonsPanelLayout);
        netButtonsPanelLayout.setHorizontalGroup(
            netButtonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(requestClearButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(requestObjectButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(requestCountButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(requestNamesButton, javax.swing.GroupLayout.DEFAULT_SIZE, 199, Short.MAX_VALUE)
            .addComponent(disconnectButton, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(netButtonsPanelLayout.createSequentialGroup()
                .addComponent(startServerButton, javax.swing.GroupLayout.PREFERRED_SIZE, 83, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, Short.MAX_VALUE))
            .addComponent(sendObjectButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        netButtonsPanelLayout.setVerticalGroup(
            netButtonsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(netButtonsPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(startServerButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(requestClearButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(requestObjectButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(requestCountButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(requestNamesButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(sendObjectButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(disconnectButton)
                .addGap(17, 17, 17))
        );

        inputDigitPane.setToolTipText("Введите число:");
        inputDigitPane.setWantsInput(true);

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
                    .addContainerGap(228, Short.MAX_VALUE)))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(buttonsPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(objectsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(netButtonsPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGap(160, 160, 160)
                    .addComponent(inputDigitPane, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(140, Short.MAX_VALUE)))
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

    private void startServerButtonItemStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_startServerButtonItemStateChanged
        try {
            if (evt.getStateChange() == java.awt.event.ItemEvent.SELECTED)
                startServer();
            else if (evt.getStateChange() == java.awt.event.ItemEvent.DESELECTED)
                startClient();
            
        } catch (IOException ex) {
            showError("Error: " + ex.getMessage());
        }
    }//GEN-LAST:event_startServerButtonItemStateChanged

    private void disconnectButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_disconnectButtonMouseClicked
        try {
            connectionHandler.sendCloseConnectionRequest();
         //   connectionHandler.disconnect();  
        } catch (Exception ex) {
            showError("Error disconnect: " + ex.getMessage());
        }         
    }//GEN-LAST:event_disconnectButtonMouseClicked

    private void sendObjectButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_sendObjectButtonMouseClicked
        int id = getDigitFromUser();
        try {
            connectionHandler.sendObject(objectsPanel.getObjectById(id).get());
        } catch (Exception ex) {
            showError("Error request object by id: " + ex.getMessage());
        }    
    }//GEN-LAST:event_sendObjectButtonMouseClicked

    private void requestNamesButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_requestNamesButtonMouseClicked
        try {   
            connectionHandler.sendObjectNamesRequest();
        } catch (IOException ex) {
            showError("Error request object names: " + ex.getMessage());
        }  
    }//GEN-LAST:event_requestNamesButtonMouseClicked

    private void requestCountButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_requestCountButtonMouseClicked
        try {   
            connectionHandler.sendObjectCountRequest(ABORT);
        } catch (IOException ex) {
            showError("Error request object count: " + ex.getMessage());
        }  
    }//GEN-LAST:event_requestCountButtonMouseClicked

    private void requestObjectButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_requestObjectButtonMouseClicked
        try {
            connectionHandler.sendObjectByIdRequest(getDigitFromUser());
        } catch (IOException ex) {
            showError("Error request object by id: " + ex.getMessage());
        }   
    }//GEN-LAST:event_requestObjectButtonMouseClicked

    private void requestClearButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_requestClearButtonMouseClicked
        try {
            connectionHandler.sendClearObjectsRequest();
        } catch (IOException ex) {
            showError("Error request clear objects: " + ex.getMessage());
        }   
    }//GEN-LAST:event_requestClearButtonMouseClicked

    private int getDigitFromUser() {
        String input = inputDigitPane.showInputDialog(null, "Введите число:");
        return Integer.parseInt(input);
    }
    
    private void startServer() throws IOException {
        
        if (connectionHandler != null)
            connectionHandler.disconnect();
        
        var server = new UDPServer(7003, 7001);
        connectionHandler = server;
        connectionHandler.addListener(connectionListener);
        serverThread = new Thread(server);
        serverThread.start(); 
    }
    
    private void startClient() throws IOException {
        if (serverThread != null) {
            serverThread.interrupt();
            serverThread = null;
        }
        
        if (connectionHandler != null)
            connectionHandler.disconnect();

        connectionHandler = new UDPClient(7001, 7003);
        connectionHandler.addListener(connectionListener);
    }
    
    private void showError(String message) {
        JOptionPane.showMessageDialog(null, message, "Error", JOptionPane.ERROR_MESSAGE);
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton addButton;
    private javax.swing.JPanel buttonsPanel;
    private javax.swing.JButton deleteButton;
    private javax.swing.JButton disconnectButton;
    private javax.swing.JOptionPane inputDigitPane;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JOptionPane jOptionPane;
    private javax.swing.JPanel netButtonsPanel;
    private ObjectsPanel objectsPanel;
    private javax.swing.JMenuItem openFileButton;
    private javax.swing.JButton requestClearButton;
    private javax.swing.JButton requestCountButton;
    private javax.swing.JButton requestNamesButton;
    private javax.swing.JButton requestObjectButton;
    private javax.swing.JButton resumeAllButton;
    private javax.swing.JButton resumeButton;
    private javax.swing.JMenuItem saveAsFileButton;
    private javax.swing.JButton sendObjectButton;
    private javax.swing.JRadioButton startServerButton;
    private javax.swing.JButton stopAllButton;
    private javax.swing.JButton stopButton;
    // End of variables declaration//GEN-END:variables
}
