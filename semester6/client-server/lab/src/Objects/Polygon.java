package Objects;

import java.awt.*;
import java.io.*;
import static java.lang.Math.*;

public class Polygon extends GraphicObject {

    private int dots;
    private int[] dotsX;
    private int[] dotsY;
    
    private enum MoveState { Up, Down, Right, Left  };
    private MoveState[] states = {MoveState.Up, MoveState.Right, MoveState.Down, MoveState.Left };  
    private int curStateId;
    private int minX, maxX, minY, maxY = 0;
    
    public Polygon() { super();  };

    public Polygon(int x, int y, Color color, int dots, int radius) {
      
        super(x, y, color);     
        
        if (dots <= 2 || radius <= 0) throw new IllegalArgumentException();
        
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
        
        int squareSide = 40;
        minX = x - squareSide;
        maxX = x + squareSide;
        minY = y - squareSide;
        maxY = y + squareSide;
    }
    
    @Override
    public void draw(Graphics graphics) {
        graphics.setColor(this.color);
        graphics.drawPolygon(dotsX, dotsY, dots);
    }

    @Override
    public void move() {
        if (!canMove) return;      
        
        int step = 1;
        int xStep = 0, yStep = 0;
        
        switch (states[curStateId]) {
            case Up: yStep = -step; break;
            case Down: yStep = step; break;
            case Right: xStep = step; break;
            case Left: xStep = -step; break;           
        } 
        
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
        
        boolean switchState = 
        (center.x - width / 2 == minX && states[curStateId] == MoveState.Left) ||
        (center.x + width / 2 == maxX && states[curStateId] == MoveState.Right) ||
        (center.y - height / 2 == minY && states[curStateId] == MoveState.Up) ||
        (center.y + height / 2 == maxY && states[curStateId] == MoveState.Down);
        
        if (switchState)
            curStateId = (curStateId == states.length - 1 ? 0 : curStateId + 1);
    }
    
    @Override
    public void read(ObjectInputStream stream) throws IOException {
        
       // var stream = new ObjectInputStream(input);
            
        Polygon obj = null;
        
        try {
            obj = (Polygon)stream.readObject();
        } catch (ClassNotFoundException e) {
            System.out.println("class not found");
            return;
        }
        
        this.canMove = obj.canMove;
        this.center = obj.center;
        this.color = obj.color;
        this.curStateId = obj.curStateId;
        this.dots = obj.dots;
        this.dotsX = obj.dotsX;
        this.dotsY = obj.dotsY;
        this.height = obj.height;
        this.maxX = obj.maxX;
        this.maxY = obj.maxY;
        this.minX = obj.minX;
        this.minY = obj.minY;
        this.states = obj.states;
        this.width = obj.width;
        
        
        /*super.read(input);
        
        var stream = new DataInputStream(input);
        
        dots = stream.readInt();
        for (int i = 0; i < dots; i++)
            dotsX[i] = stream.readInt();
        for (int i = 0; i < dots; i++)
            dotsY[i] = stream.readInt();
*/
    }
    
    @Override
    public void write(ObjectOutputStream stream) throws IOException {
        
      //  var stream = new ObjectOutputStream(output);
        stream.writeUTF(this.getClass().getName());
        stream.writeObject(this);
        
       /* super.write(output);
        
        var stream = new DataOutputStream(output);
        
        stream.writeInt(dots);
        for (int i = 0; i < dots; i++)
            stream.writeInt(dotsX[i]);
        for (int i = 0; i < dots; i++)
            stream.writeInt(dotsY[i]);
*/
    }
    
}
