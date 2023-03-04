
import Objects.GraphicObject;

import Objects.Polygon;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;

public class ObjectsPanel extends JPanel {
    
    private java.util.List<GraphicObject> objects = new ArrayList<>();
    
    ClickHandler panelClickHandler = (e) -> {};
    
    public enum EditMode { None, Add, Delete, Resume, Stop };
    
    boolean drawBorderRects = false;    
    
    public void onMouseClicked(MouseEvent evt) {
        panelClickHandler.OnClick(evt);
    }
    
    public void resumeAllObjects() {
        switchEditMode(EditMode.None);
        objects.forEach(obj -> obj.canMove = true);
    }
    
    public void stopAllObjects() {
        switchEditMode(EditMode.None);
        objects.forEach(obj -> obj.canMove = false);
    }
    
    public void moveAllObjects() {
        objects.forEach((obj) -> obj.move());
    }
    
    @Override
    public void paint(Graphics g) {
        super.paint(g);
        
        var dim = getBounds();     
        var img = createImage(dim.width, dim.height);
        
        var imgGraphics = img.getGraphics();
        imgGraphics.setColor(getBackground());
        imgGraphics.fillRect(0, 0, dim.width, dim.height);
      //  this.repaint();
        
        for (int i = 0; i < objects.size(); i++) {
            
            if (drawBorderRects)
                 objects.get(i).drawBorderRect(imgGraphics, Color.GRAY);
            
            objects.get(i).draw(imgGraphics);          
        }
        g.drawImage(img, -10, 14, this);
    }
    
    private Optional<GraphicObject> getPickedObject(Point pos) {
            
        GraphicObject picked = null;
        
        for(GraphicObject obj: objects) {
            if (obj.contains(pos.x, pos.y)) {
                picked = obj;
                break;
            }
        }

        return Optional.ofNullable(picked);
    }
    
    private void spawnRandomObject(Point pos) {
        GraphicObject obj = null;
        
        var r = new Random();
        if (r.nextInt() % 2 == 0)
            obj = new Polygon(pos.x, pos.y, Color.BLUE, 5, 30);
        else {
            try {
                obj = new Image(pos.x, pos.y, null, "dur1.png");
            } catch (IOException ex) {
                System.out.println("Oops!");
            }
        }
        
        objects.add(obj);  
    }
    
    public void switchEditMode(EditMode newMode) {
          
        drawBorderRects = false;
        
        switch (newMode) {
            case Add:
                panelClickHandler = ((e) -> { spawnRandomObject(e.getPoint()); } );
                break;
            case Delete:
                drawBorderRects = true;
                panelClickHandler = (e) -> { getPickedObject(e.getPoint()).
                        ifPresent((obj) -> {objects.remove(obj);}); 
                };
                break;
            case Resume:
                drawBorderRects = true;
                panelClickHandler = (e) -> { getPickedObject(e.getPoint()).
                        ifPresent((obj) -> {obj.canMove = true;}); 
                };
                break;
            case Stop:
                drawBorderRects = true;
                panelClickHandler = (e) -> { getPickedObject(e.getPoint()).
                        ifPresent((obj) -> {obj.canMove = false;}); 
                };               
                break;
            default:
                panelClickHandler = (e) -> {};
        }
    }
}
