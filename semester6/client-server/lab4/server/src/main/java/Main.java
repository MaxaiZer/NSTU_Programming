import java.util.Scanner;
import org.apache.log4j.BasicConfigurator;

public class Main {

    public static void main(String[] args) {
        BasicConfigurator.configure();
        Server server;
        try {
            server = new Server();
            server.start();
        } catch (Exception ex) {
            System.out.println("Error start server: " + ex.getMessage());
            return;
        }
        
        Scanner scanner = new Scanner(System.in);
        System.out.println("Input anything to stop server:");
        String input = scanner.nextLine();    
    }
}
