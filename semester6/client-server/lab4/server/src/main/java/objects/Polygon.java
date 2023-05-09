package objects;

import java.io.*;

public class Polygon extends GraphicObject implements Serializable {

    private int dots;
    private int[] dotsX;
    private int[] dotsY;
    
    private enum MoveState { Up, Down, Right, Left  };
    private MoveState[] states = {MoveState.Up, MoveState.Right, MoveState.Down, MoveState.Left };  
    private int curStateId;
    private int minX, maxX, minY, maxY = 0;
    
    public Polygon() { super();  };

}
