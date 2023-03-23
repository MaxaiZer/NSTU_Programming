package Objects;

import com.thoughtworks.xstream.annotations.XStreamOmitField;
import java.awt.*;
import java.awt.image.*;
import java.io.*;
import java.util.Random;
import javax.imageio.ImageIO;
import javax.vecmath.Vector2d;

public class Image extends GraphicObject implements Serializable {

    @XStreamOmitField 
    private transient BufferedImage image;
    private String path;

    private Vector2d direction;
    private float speed;
    
    public Image() { super();  };
    
    public Image(int x, int y, Color color, String path) throws IOException {
        super(x, y, color);
        
        this.path = path;
        image = ImageIO.read(new File(path));
        
        width = image.getWidth() + 2;
        height = image.getHeight() + 2;
        
        var r = new Random();
        direction = new Vector2d(r.nextInt() % 10 + 5, r.nextInt() % 10 + 5);
        speed = r.nextInt() % 15 + 10;
    }

    @Override
    public void draw(Graphics graphics) {
        graphics.drawImage(image, center.x - image.getWidth() / 2, center.y - image.getHeight() / 2, color, null);
    }

    @Override
    public void move() {
        if (!canMove) return;  
        
        float length = (float) direction.length();      
        center.x += direction.x / length * speed;
        center.y += direction.y / length * speed;
    }

    private void readObject(ObjectInputStream stream) throws IOException, ClassNotFoundException {
        stream.defaultReadObject();
        image = ImageIO.read(new File(path));    
    }

    @Override
    public void onCollision(Point point, Vector2d normal) {      
        double velocityDotProduct = direction.dot(normal);
        direction = new Vector2d(direction.x - 2 * velocityDotProduct * normal.x, direction.y - 2 * velocityDotProduct * normal.y);
    }
}
