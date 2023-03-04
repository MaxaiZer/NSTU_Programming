
import Objects.GraphicObject;
import java.awt.*;
import java.awt.image.*;
import java.io.*;
import static java.lang.Math.*;
import java.util.Random;
import javax.imageio.ImageIO;

public class Image extends GraphicObject {

    private BufferedImage image;
    private String path;
    
    private final Point circlePos;
    private double curAngle;
    private final int radius;
    
    public Image(int x, int y, Color color, String path) throws IOException {
        super(x, y, color);
        
        this.path = path;
        image = ImageIO.read(new File(path));
        
        width = image.getWidth() + 2;
        height = image.getHeight() + 2;
        
        var r = new Random();
        radius = r.nextInt() % 30 + 1;
        
        curAngle = Math.toRadians(Math.random() * 360);
        int offetX = (int) (radius * cos(curAngle));
        int offetY = (int) (radius * sin(curAngle));
        
        circlePos = new Point(center.x + offetX, center.y + offetY);  
        curAngle = 0;
    }

    @Override
    public void draw(Graphics graphics) {
        graphics.drawImage(image, center.x - width / 2, center.y - height / 2, color, null);
    }

    @Override
    public void move() {
        if (!canMove) return;
        
        curAngle += 0.1;
        
        center.x = (int) (circlePos.x + cos(curAngle) * radius);
        center.y = (int) (circlePos.y + sin(curAngle) * radius);
    }
    
    @Override
    public void read(InputStream input) throws IOException {
        super.read(input);
        
        var stream = new DataInputStream(input);
        path = stream.readUTF();
        image = ImageIO.read(new File(path));
    }
    
    @Override
    public void write(OutputStream output) throws IOException {
        super.write(output);
        
        var stream = new DataOutputStream(output);
        stream.writeUTF(path);
    }
}
