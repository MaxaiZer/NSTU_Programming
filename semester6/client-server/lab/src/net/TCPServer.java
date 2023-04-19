package net;

import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer extends TCPConnectionHandler implements Runnable {
    
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private Thread connectionThread;
            
    public TCPServer(int port) throws IOException {
        serverSocket = new ServerSocket(port);
        System.out.println("Server running on port " + port);
    }

    @Override
    public void run() {
        
        try {
            
            clientSocket = serverSocket.accept();
            outputStream = new ObjectOutputStream(clientSocket.getOutputStream());
            inputStream = new ObjectInputStream(clientSocket.getInputStream());

            System.out.println("Accepted connection from " + clientSocket.getInetAddress().getHostName());

            connectionThread = new Thread(() -> {
                try {
                    while (true) {
                        handleCommand(inputStream.readInt());
                    }
                } 
                catch (EOFException ex) { }            
                catch (Exception ex) {
                    listeners.forEach(obj -> obj.onException(ex));
                }
            });

            connectionThread.start();
        } catch (IOException ex) {
            listeners.forEach(obj -> obj.onException(ex));
        }
    }
    
    @Override
    public void disconnect() throws IOException {
        connectionThread.interrupt();
        if (clientSocket != null)
            clientSocket.close();
    }
    
}
