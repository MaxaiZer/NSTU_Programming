package Objects;

import java.awt.*;
import java.io.*;
import static java.lang.Math.abs;

public abstract class GraphicObject {
    
    public Point center;
    public Color color;
    public boolean canMove = true;
    
    protected int width;
    protected int height;
    
    public GraphicObject(int x, int y, Color color) {
        center = new Point(x, y);
        this.color = color;
    }
    
    public boolean contains(int x, int y) {      
        return abs(center.x - x) <= width / 2 && 
              abs(center.y - y) <= height / 2;
    }
    
    public abstract void draw(Graphics graphics);
    
    public void drawBorderRect(Graphics graphics, Color color) {
        graphics.setColor(color);
        graphics.drawRect(center.x - width / 2, center.y - height / 2, width, height);
    }
    
    public abstract void move();
    
    public void read(InputStream input) throws IOException {
        var stream = new DataInputStream(input);
        
        center.x = stream.readInt();
        center.y = stream.readInt();
        width = stream.readInt();
        height = stream.readInt();
        
        var r = stream.readInt();
        var g = stream.readInt();
        var b = stream.readInt();
        color = new Color(r, g, b);       
    }
    
    public void write(OutputStream output) throws IOException {
        var stream = new DataOutputStream(output);
        
        stream.writeInt(center.x);
        stream.writeInt(center.y);
        stream.writeInt(width);
        stream.writeInt(height);
        
        stream.writeInt(color.getRed());
        stream.writeInt(color.getGreen());
        stream.writeInt(color.getBlue());     
    }
}
