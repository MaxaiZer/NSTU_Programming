import java.util.List;
import javax.swing.JOptionPane;
import net.NetworkEventListener;
import objects.GraphicObject;

public class FrameNetworkListener implements NetworkEventListener {
      
    private final ObjectsPanel objectsPanel;
    
    public FrameNetworkListener(ObjectsPanel objectsPanel) {
        this.objectsPanel = objectsPanel;
    }
    
    @Override
    public void onReceiveObject(GraphicObject obj) {
        objectsPanel.addObject(obj);
    }

    @Override
    public void onReceiveObjects(List<GraphicObject> objects) {
        objects.forEach(obj -> objectsPanel.addObject(obj));
    }
    
    @Override
    public void onReceiveObjectNames(List<String> names) {
        
        String message = "";       
        for (String name: names) 
            message += name + "\n";
        
        JOptionPane.showMessageDialog(null, message);   
    }

    @Override
    public void onError(String message) {
         JOptionPane.showMessageDialog(null, message, 
                 "Exception", JOptionPane.ERROR_MESSAGE);
    }
    
}
