package net;

import java.io.IOException;
import java.util.ArrayList;

public abstract class ConnectionHandler {
    
    protected ArrayList<ConnectionEventListener> listeners = new ArrayList<>(); 
    
    public void addListener(ConnectionEventListener listener) {
        listeners.add(listener);
    }
    
    public void removeListener(ConnectionEventListener listener) {
        listeners.remove(listeners);
    }
    
    public abstract void sendClearObjectsRequest() throws IOException;
    
    public abstract void sendObjectByIdRequest(int id) throws IOException;
    
    public abstract void sendObjectCountRequest(int count) throws IOException;
    
    public abstract void sendObjectNamesRequest() throws IOException;
    
    public abstract void sendCloseConnectionRequest() throws IOException;
    
    public abstract void sendObject(Object object) throws IOException;
    
    public abstract void sendObjectNames(ArrayList<String> names) throws IOException;
    
    public abstract void sendObjectCount(int count) throws IOException;
    
    public abstract void disconnect() throws IOException;
}
