import java.io.IOException;
import java.util.ArrayList;
import javax.swing.JOptionPane;
import net.ConnectionEventListener;
import net.ConnectionHandler;
import objects.GraphicObject;

public class FrameConnectionListener implements ConnectionEventListener {
      
    private final ObjectsPanel objectsPanel;
    
    public FrameConnectionListener(ObjectsPanel objectsPanel) {
        this.objectsPanel = objectsPanel;
    }
    
    @Override
    public void onReceiveObject(Object obj) {
        objectsPanel.addObject((GraphicObject) obj);
    }

    @Override
    public void onReceiveObjectNames(ArrayList<String> names) {
        
        String message = "";       
        for (String name: names) 
            message += name + "\n";
        
        JOptionPane.showMessageDialog(null, message);   
    }

    @Override
    public void onReceiveObjectCount(int count) {       
        String format = "Получено кол-во объектов: %d";
        JOptionPane.showMessageDialog(null, 
                String.format(format, count));   
    }

    @Override
    public void onRequestClearObjects() {
        objectsPanel.clearObjects();
    }

    @Override
    public void onRequestObjectCount(ConnectionHandler sender) {       
        try {
            sender.sendObjectCount(objectsPanel.getObjectsCount());
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, 
                    "Error send object count: " + ex.getMessage());
        }
    }

    @Override
    public void onRequestObjectNames(ConnectionHandler sender) {
        try {
            sender.sendObjectNames(objectsPanel.getObjectNames());
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, 
                    "Error send object names: " + ex.getMessage());
        }
    }

    @Override
    public void onRequestObjectById(ConnectionHandler sender, int id) {      
        try {
            sender.sendObject(objectsPanel.getObjectById(id).get());          
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, 
                    "Object by invalid id request", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    @Override
    public void onException(Exception ex) {
         JOptionPane.showMessageDialog(null, ex.getMessage(), 
                 "Exception", JOptionPane.ERROR_MESSAGE);
    }
    
}
