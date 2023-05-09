package net;

import java.util.ArrayList;
import objects.GraphicObject;

public abstract class NetworkRepository {
    
    protected ArrayList<NetworkEventListener> listeners = new ArrayList<>(); 
    
    public void addListener(NetworkEventListener listener) {
        listeners.add(listener);
    }
    
    public void removeListener(NetworkEventListener listener) {
        listeners.remove(listener);
    }   
    
    abstract public void sendObject(GraphicObject object);

    abstract public void requestObjectByIndex(int index);

    abstract public void requestObjectsList();

    abstract public void requestObjectsListNames();

    abstract public void removeObjectByIndex(int index);
}