import Objects.GraphicObject;
import java.awt.*;
import java.awt.image.*;
import java.io.*;
import static java.lang.Math.*;
import java.util.Random;
import javax.imageio.ImageIO;

public class Image extends GraphicObject implements Serializable {

    private transient BufferedImage image;
    private String path;
    
    private Point circlePos;
    private double curAngle;
    private int radius;
    
    public Image() { super();  };
    
    public Image(int x, int y, Color color, String path) throws IOException {
        super(x, y, color);
        
        this.path = path;
        image = ImageIO.read(new File(path));
        
        width = image.getWidth() + 2;
        height = image.getHeight() + 2;
        
        var r = new Random();
        radius = r.nextInt() % 30 + 20;
        
        curAngle = Math.toRadians(Math.random() * 360);
        int offetX = (int) (radius * cos(curAngle));
        int offetY = (int) (radius * sin(curAngle));
        
        circlePos = new Point(center.x + offetX, center.y + offetY);  
        curAngle = 0;
    }

    @Override
    public void draw(Graphics graphics) {
       /* 
        //img = new BufferedImage(image.getWidth(), image.getHeight(), BufferedImage.TYPE_INT_RGB);
        Graphics2D g2 = image.createGraphics();
                //g2.translate(workSpace.getSize().width/2, workSpace.getSize().height/2);
        g2.rotate(Math.toRadians(10), image.getWidth()/2, image.getHeight()/2);
        g2.drawImage(image, center.x - width / 2, center.y - height / 2, color, null);
       // graphics.drawImage(image, center.x - width / 2, center.y - height / 2, color, null);
        g2.dispose();
        */
        
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
    public void read(ObjectInputStream stream) throws IOException {
        
       // var dataStream = new DataInput
      //  var stream = new ObjectInputStream(input);
            
        Image obj = null;
        
        
        try {
            obj = (Image)stream.readObject();
        } catch (ClassNotFoundException e) {
            System.out.println("class not found");
            return;
        }

        this.canMove = obj.canMove;
        this.center = obj.center; 
        this.circlePos = obj.circlePos; 
        this.color = obj.color; 
        this.curAngle = obj.curAngle; 
        this.height = obj.height; 
        this.image = ImageIO.read(new File(obj.path)); 
        this.path = obj.path;
        this.radius = obj.radius; 
        this.width = obj.width; 
        
        
        /*
        super.read(input);
        
        var stream = new DataInputStream(input);
        path = stream.readUTF();
        image = ImageIO.read(new File(path));
*/
    }
    
    @Override
    public void write(ObjectOutputStream stream) throws IOException {
        
      //  var stream = new ObjectOutputStream(output);
        stream.writeUTF(this.getClass().getName());
        stream.writeObject(this);
        
        /*
        super.write(output);
        
        var stream = new DataOutputStream(output);
        stream.writeUTF(path);
*/
    }
}
