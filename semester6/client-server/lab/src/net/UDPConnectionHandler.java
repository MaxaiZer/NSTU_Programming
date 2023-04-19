package net;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;

public abstract class UDPConnectionHandler extends ConnectionHandler {
    
    protected DatagramSocket socket;
    protected DatagramPacket sendPacket;
    
    UDPConnectionHandler(int listenPort, int responsePort) throws IOException {
        socket = new DatagramSocket(listenPort);
        byte[] receiveData = new byte[0];
        sendPacket = new DatagramPacket(receiveData, 0, 
                InetAddress.getByName("127.0.0.1"), responsePort);
    }
    
    @Override
    public void sendClearObjectsRequest() throws IOException {
        
        ByteArrayOutputStream bis = new ByteArrayOutputStream();
        ObjectOutputStream outputStream = new ObjectOutputStream(bis);   
        
        outputStream.writeInt(NetCommand.clearObjectsRequest); 
        outputStream.flush();
        
        sendPacket.setData( bis.toByteArray());
        socket.send(sendPacket);
    }

    @Override
    public void sendObjectByIdRequest(int id) throws IOException {
        
        ByteArrayOutputStream bis = new ByteArrayOutputStream();
        ObjectOutputStream outputStream = new ObjectOutputStream(bis);   
        
        outputStream.writeInt(NetCommand.objectByIdRequest); 
        outputStream.writeInt(id);
        outputStream.flush();
        
        sendPacket.setData( bis.toByteArray());
        socket.send(sendPacket); 
    }

    @Override
    public void sendObjectCountRequest(int count) throws IOException {
        ByteArrayOutputStream bis = new ByteArrayOutputStream();
        ObjectOutputStream outputStream = new ObjectOutputStream(bis);   
        
        outputStream.writeInt(NetCommand.objectCountRequest); 
        outputStream.flush();
        
        sendPacket.setData(bis.toByteArray());
        socket.send(sendPacket); 
    }

    @Override
    public void sendObjectNamesRequest() throws IOException {
        
        ByteArrayOutputStream bis = new ByteArrayOutputStream();
        ObjectOutputStream outputStream = new ObjectOutputStream(bis);   
        
        outputStream.writeInt(NetCommand.objectNamesRequest); 
        outputStream.flush();

        sendPacket.setData(bis.toByteArray());
        socket.send(sendPacket); 
    }

    @Override
    public void sendCloseConnectionRequest() throws IOException {
        ByteArrayOutputStream bis = new ByteArrayOutputStream();
        ObjectOutputStream outputStream = new ObjectOutputStream(bis);   
        
        outputStream.writeInt(NetCommand.closeConnectionRequest); 
        outputStream.flush();
        
        sendPacket.setData(bis.toByteArray());
        socket.send(sendPacket); 
    }

    @Override
    public void sendObject(Object object) throws IOException {
        ByteArrayOutputStream bis = new ByteArrayOutputStream();
        ObjectOutputStream outputStream = new ObjectOutputStream(bis);   
        
        outputStream.writeInt(NetCommand.objectTransfer); 
        outputStream.writeObject(object);
        outputStream.flush();
        
        sendPacket.setData(bis.toByteArray());
        socket.send(sendPacket); 
    }

    @Override
    public void sendObjectNames(ArrayList<String> names) throws IOException {
        ByteArrayOutputStream bis = new ByteArrayOutputStream();
        ObjectOutputStream outputStream = new ObjectOutputStream(bis);   
        
        outputStream.writeInt(NetCommand.objectNamesTransfer); 
        outputStream.writeObject(names);
        outputStream.flush();
        
        sendPacket.setData(bis.toByteArray());
        socket.send(sendPacket); 
    }

    @Override
    public void sendObjectCount(int count) throws IOException {
        ByteArrayOutputStream bis = new ByteArrayOutputStream();
        ObjectOutputStream outputStream = new ObjectOutputStream(bis);   
        
        outputStream.writeInt(NetCommand.objectCountTransfer); 
        outputStream.writeInt(count);
        outputStream.flush();
        
        sendPacket.setData(bis.toByteArray());
        socket.send(sendPacket); 
    }
 
    protected void handleCommand(int command, ObjectInputStream inputStream) throws IOException, ClassNotFoundException {
        
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
