package objects;

import java.awt.*;
import java.awt.image.*;
import java.io.*;
import static java.lang.Math.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
//import org.imgscalr.Scalr;

public class Image extends GraphicObject implements Serializable {

    private transient BufferedImage image;
    private String path;

    private double curAngle = 0;
    private int originalWidth = 0;
    
    public Image() { super();  };
    
    public Image(int x, int y, Color color, String path) throws IOException {
        super(x, y, color);
        
        this.path = path;
        image = ImageIO.read(new File(path));
        
        width = image.getWidth() + 2;
        height = image.getHeight() + 2;

        originalWidth = width;
    }

    @Override
    public void draw(Graphics graphics) {
        
        if (image == null) {
            try {
                image = ImageIO.read(new File(path));
            } catch (IOException ex) {
                Logger.getLogger(Image.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        int newWidth = (int)(sin(curAngle) * 20) + originalWidth;
        
     //   BufferedImage resized = Scalr.resize(image, newWidth);     
      //  width = resized.getWidth() + 2;
      //  height = resized.getHeight() + 2;

      //  graphics.drawImage(resized, center.x - resized.getWidth() / 2, center.y - resized.getHeight() / 2, color, null);
        graphics.drawImage(image, center.x - image.getWidth() / 2, center.y - image.getHeight() / 2, color, null);
    }

    @Override
    public void move() {
        if (!canMove) return;  
        
        curAngle += 0.1;
    }

    private void readObject(ObjectInputStream stream) throws IOException, ClassNotFoundException {
        stream.defaultReadObject();
        image = ImageIO.read(new File(path));    
    }
}
