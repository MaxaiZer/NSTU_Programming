package net;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public abstract class TCPConnectionHandler extends ConnectionHandler  {
    
    ObjectInputStream inputStream;
    ObjectOutputStream outputStream;
    
    @Override
    public void sendClearObjectsRequest() throws IOException {
        outputStream.writeInt(NetCommand.clearObjectsRequest);
        outputStream.flush();
    }
    
    @Override
    public void sendObjectByIdRequest(int id) throws IOException {
        outputStream.writeInt(NetCommand.objectByIdRequest);
        outputStream.writeInt(id);
        outputStream.flush();
    } 
    
    @Override
    public void sendObjectCountRequest(int count) throws IOException {
        outputStream.writeInt(NetCommand.objectCountRequest);
        outputStream.flush();
    }
    
    @Override
    public void sendObjectNamesRequest() throws IOException {
        outputStream.writeInt(NetCommand.objectNamesRequest);
        outputStream.flush();
    }
    
    @Override
    public void sendCloseConnectionRequest() throws IOException {
        outputStream.writeInt(NetCommand.closeConnectionRequest);
        outputStream.flush();
    }
    
    @Override
    public void sendObject(Object object) throws IOException {
        outputStream.writeInt(NetCommand.objectTransfer);
        outputStream.writeObject(object);
        outputStream.flush();
    }
    
    @Override
    public void sendObjectNames(ArrayList<String> names) throws IOException {
        outputStream.writeInt(NetCommand.objectNamesTransfer);
        outputStream.writeObject(names);       
        outputStream.flush();
    }
    
    @Override
    public void sendObjectCount(int count) throws IOException {
        outputStream.writeInt(NetCommand.objectCountTransfer);
        outputStream.writeInt(count);
        outputStream.flush();
    }
  
    protected void handleCommand(int command) throws IOException, ClassNotFoundException {
        
        System.out.println("Received command " + command);
        
        if (command == NetCommand.clearObjectsRequest) {                       
            listeners.forEach(listener -> listener.onRequestClearObjects());     
            
        } else if (command == NetCommand.closeConnectionRequest) {           
            disconnect();    
            
        } else if (command == NetCommand.objectCountRequest) {
            listeners.forEach(listener -> listener.onRequestObjectCount(this));   
            
        } else if (command == NetCommand.objectByIdRequest) {            
            int id = inputStream.readInt();
            listeners.forEach(listener -> listener.onRequestObjectById(this, id));   
            
        } else if (command == NetCommand.objectNamesRequest) {          
            listeners.forEach(listener -> listener.onRequestObjectNames(this));    
            
        } else if (command == NetCommand.objectTransfer) {
            Object obj = inputStream.readObject();
            listeners.forEach(listener -> listener.onReceiveObject(obj));

        } else if (command == NetCommand.objectCountTransfer) {
            int count = inputStream.readInt();
            listeners.forEach(listener -> listener.onReceiveObjectCount(count));
        
        } else if (command == NetCommand.objectNamesTransfer) {           
            var names = (ArrayList<String>)inputStream.readObject();
            listeners.forEach(listener -> listener.onReceiveObjectNames(names));           
            
        } else {
            throw new IllegalArgumentException();
        }
    }
}
