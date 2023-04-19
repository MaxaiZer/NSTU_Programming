package net;

import java.io.ByteArrayInputStream;
import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.DatagramPacket;

public class UDPClient extends UDPConnectionHandler {
    
    Thread connectionThread;

    public UDPClient(int listenPort, int responsePort) throws IOException {
        super(listenPort, responsePort);
   
        System.out.println("Client is listening on port " + listenPort);

        connectionThread = new Thread(() -> {

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

            } catch (EOFException ex) { } 
              catch (Exception ex) {
                listeners.forEach(obj -> obj.onException(ex));
            }
        });

        connectionThread.start();
    }

    @Override
    public void disconnect() throws IOException {
        connectionThread.interrupt();
        if (socket != null)
           socket.close();
    }
}
