package net;

import java.util.List;
import objects.GraphicObject;

public interface NetworkEventListener {
    
    public void onReceiveObject(GraphicObject obj);
    
    public void onReceiveObjects(List<GraphicObject> objects);
    
    public void onReceiveObjectNames(List<String> names);
    
    public void onError(String message);
}
