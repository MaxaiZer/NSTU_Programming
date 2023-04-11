package net;

import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class TCPClient extends ConnectionHandler {

    Socket socket;
    private boolean isConnected = true;
    Thread connectionThread;

    public TCPClient(String serverAddress, int serverPort) throws IOException {
        
        connectionThread = new Thread(() -> {
            
            System.out.println("Started client");
            
            while (true) {
                try {
                    socket = new Socket(serverAddress, serverPort);
                    System.out.println("Connected!");
                    break;
                } catch (IOException e) {
                    System.out.println("Connection failed. Retrying in 2 seconds...");
                    try {
                        Thread.sleep(2000);
                    } catch (InterruptedException ex) {
                        return;
                    }
                }
            }
            
            
            try {               
                inputStream = new ObjectInputStream(socket.getInputStream());
                outputStream = new ObjectOutputStream(socket.getOutputStream());
                
                while (isConnected) {
                    handleCommand(inputStream.readInt());
                }
            } 
            catch (EOFException ex) { }   
            catch (Exception ex) {
                listeners.forEach(obj -> obj.onException(ex));
            }
        });
        
        connectionThread.start();
    }

    @Override
    public void disconnect() throws IOException {
        connectionThread.interrupt();
        isConnected = false;
        if (socket != null)
            socket.close();
    }
}
