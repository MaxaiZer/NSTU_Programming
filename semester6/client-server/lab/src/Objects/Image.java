package Objects;

import com.thoughtworks.xstream.annotations.XStreamOmitField;
import java.awt.*;
import java.awt.image.*;
import java.io.*;
import static java.lang.Math.*;
import javax.imageio.ImageIO;
import org.imgscalr.Scalr;

public class Image extends GraphicObject implements Serializable {

    @XStreamOmitField 
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
        int newWidth = (int)(sin(curAngle) * 20) + originalWidth;
        
        BufferedImage resized = Scalr.resize(image, newWidth);
        width = resized.getWidth();
        height = resized.getHeight();
        
        graphics.drawImage(resized, center.x - width / 2, center.y - height / 2, color, null);
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
