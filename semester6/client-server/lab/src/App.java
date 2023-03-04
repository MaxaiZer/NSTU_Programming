import java.awt.event.ActionEvent;
import javax.swing.Timer;

public class App {

    public static void main(String[] args) {
        var mainFrame = new MainFrame();
        mainFrame.setVisible(true);
        
        int targetFps = 60;
        var timer = new Timer(1000 / targetFps, (ActionEvent ae) -> {
            mainFrame.update();
        });
        
         timer.setRepeats(true);
         timer.start();
    }  
}
