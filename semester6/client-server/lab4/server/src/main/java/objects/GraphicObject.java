package objects;

import com.fasterxml.jackson.annotation.JsonSubTypes;
import com.fasterxml.jackson.annotation.JsonTypeInfo;
import java.awt.*;
import java.io.*;

//@JsonTypeInfo(use = JsonTypeInfo.Id.CLASS, include = JsonTypeInfo.As.PROPERTY, property = "type")
@JsonTypeInfo(use = JsonTypeInfo.Id.NAME, property = "type")
@JsonSubTypes({
    @JsonSubTypes.Type(value = Image.class, name = "image"),
    @JsonSubTypes.Type(value = Polygon.class, name = "polygon")
})
public abstract class GraphicObject implements Serializable {
    
    public Point center;
    public Color color;
    public boolean canMove = true;
    
    protected int width;
    protected int height;
    
    public GraphicObject() {};
}
