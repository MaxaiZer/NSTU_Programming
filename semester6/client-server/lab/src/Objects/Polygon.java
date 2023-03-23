package Objects;

import java.awt.*;
import java.io.*;
import static java.lang.Math.*;
import java.util.Random;
import javax.vecmath.Vector2d;

public class Polygon extends GraphicObject implements Serializable {

    private int dots;
    private int[] dotsX;
    private int[] dotsY;
    
    private Vector2d direction;
    private float speed;
    
    public Polygon() { super();  };

    public Polygon(int x, int y, Color color, int dots, int radius) {
      
        super(x, y, color);     
        
        if (dots < 5 || radius <= 0) throw new IllegalArgumentException();
        
        this.dots = dots;  
        width = radius * 2;
        height = radius * 2;
        
        dotsX = new int[dots];
        dotsY = new int[dots];
 
        int num = 0;
        float step = (float) (2.0 * PI / dots);
        
        for (float a = 0f; a < 2.0 * PI && num < dots; num++) {
        
            dotsX[num] = (int) (x + (radius * cos(a)));
            dotsY[num] = (int) (y + (radius * sin(a)));
            
            if (num == dots - 2)
                step /= 2;
            
            a += step; 
        }
        
        var r = new Random();
        direction = new Vector2d(r.nextInt() % 10 + 5, r.nextInt() % 10 + 5);
        speed = r.nextInt() % 15 + 10;
    }
    
    @Override
    public void draw(Graphics graphics) {
        graphics.setColor(this.color);
        
        for (int i = 0; i < dots; i += 2) { 
            int nextId = i + 2 >= dots ?  (i + 2) % dots : i + 2;
            graphics.drawLine​(dotsX[i], dotsY[i], dotsX[nextId], dotsY[nextId]);         
        }
        
        for (int i = 1; i < dots; i += 2) { 
            int nextId = i + 2 >= dots ?  (i + 2) % dots : i + 2;
            graphics.drawLine​(dotsX[i], dotsY[i], dotsX[nextId], dotsY[nextId]);         
        }
    }

    @Override
    public void move() {
        if (!canMove) return;  
        
        double length = direction.length();      
        int xStep = (int) (direction.x / length * speed);
        int yStep = (int) (direction.y / length * speed);
        
        if (yStep != 0) {
            for (int i = 0; i < dots; i++)
                dotsY[i] += yStep;
            center.y += yStep;
        }
        if (xStep != 0) {
            for (int i = 0; i < dots; i++)
                dotsX[i] += xStep;
            center.x += xStep;
        }
    }

    @Override
    public void onCollision(Point point, Vector2d normal) {
        
        double velocityDotProduct = direction.dot(normal);
        direction = new Vector2d(direction.x - 2 * velocityDotProduct * normal.x, direction.y - 2 * velocityDotProduct * normal.y);
        speed *= 0.5;
    }

}
