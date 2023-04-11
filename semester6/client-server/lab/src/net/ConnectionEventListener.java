package net;

import java.util.ArrayList;

public interface ConnectionEventListener {
    
    public void onReceiveObject(Object obj);
    
    public void onReceiveObjectNames(ArrayList<String> names);
    
    public void onReceiveObjectCount(int count);
    
    public void onRequestClearObjects();
    
    public void onRequestObjectCount(ConnectionHandler sender);
    
    public void onRequestObjectNames(ConnectionHandler sender);
    
    public void onRequestObjectById(ConnectionHandler sender, int id);
    
    public void onException(Exception ex);
}
