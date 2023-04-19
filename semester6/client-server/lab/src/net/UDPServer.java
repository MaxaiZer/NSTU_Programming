package net;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.DatagramPacket;

public class UDPServer extends UDPConnectionHandler implements Runnable {

    public UDPServer(int listenPort, int responsePort) throws IOException {
        super(listenPort, responsePort);
   
        System.out.println("Server is listening on port " + listenPort);
    }

    @Override
    public void run() {

        byte[] receiveData = new byte[1024];
        
        try {

            while (true) {
                DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                socket.receive(receivePacket);

                System.out.println("Received packet from port " + receivePacket.getPort());

                ByteArrayInputStream bis = new ByteArrayInputStream(receiveData);
                ObjectInputStream inputStream = new ObjectInputStream(bis);   
                
                handleCommand(inputStream.readInt(), inputStream);
            }

        } 
        catch (Exception ex) {
            listeners.forEach(obj -> obj.onException(ex));
        }
    }

    @Override
    public void disconnect() throws IOException {
        sendCloseConnectionRequest();
    }
}
