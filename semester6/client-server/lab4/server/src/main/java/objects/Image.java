package objects;

import java.awt.image.*;
import java.io.*;

public class Image extends GraphicObject implements Serializable {

    private transient BufferedImage image;
    private String path;

    private double curAngle = 0;
    private int originalWidth = 0;
    
    public Image() { super();  };
}
