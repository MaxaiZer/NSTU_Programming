import objects.Polygon;
import objects.GraphicObject;
import objects.Image;
import com.thoughtworks.xstream.XStream;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;

public class ObjectsPanel extends JPanel {

    public enum EditMode { None, Add, Delete, Resume, Stop }; 
    
    private java.util.List<GraphicObject> objects = new ArrayList<>(); 
    private ClickHandler panelClickHandler = (e) -> {};
    private boolean drawBorderRects = false; 
    
    @Override
    public void paint(Graphics g) {
        super.paint(g);
        
        var dim = getBounds();     
        var img = createImage(dim.width - 2, dim.height - 2);
        
        var imgGraphics = img.getGraphics();
        imgGraphics.setColor(getBackground());
        imgGraphics.fillRect(0, 0, dim.width, dim.height);
        
        for (int i = 0; i < objects.size(); i++) {
            
            Color border = (objects.get(i).canMove ? Color.GREEN : Color.GRAY);
            
            if (drawBorderRects)
                 objects.get(i).drawBorderRect(imgGraphics, border);
            
            objects.get(i).draw(imgGraphics);          
        }
        g.drawImage(img, 1, 1, this);
    }
    
    public void onAddButtonClick() {
        switchEditMode(EditMode.Add);
    }

    public void onDeleteButtonClick() {
        switchEditMode(EditMode.Delete);
    }

    public void onResumeButtonClick() {
        switchEditMode(EditMode.Resume);
    }

    public void onResumeAllButtonClick() {
        switchEditMode(EditMode.None);
        objects.forEach(obj -> obj.canMove = true);
    }

    public void onStopButtonClick() {
         switchEditMode(EditMode.Stop);
    }

    public void onStopAllButtonClick() {
        switchEditMode(EditMode.None);
        objects.forEach(obj -> obj.canMove = false);
    }

    public void addObject(GraphicObject obj) {
        objects.add(obj);
    }   
    
    public void clearObjects() {
        objects.clear();
    }

    public Optional<GraphicObject> getObjectById(int id) {
        GraphicObject obj = null;
        
        try { obj = objects.get(id); } 
        catch (IndexOutOfBoundsException ex) { }
        
        return Optional.ofNullable(obj);
    }

    public ArrayList<String> getObjectNames() {
        var names = new ArrayList<String>();
        
        objects.forEach(obj -> { 
            String className = obj instanceof Image ? "Image" : "Polygon";
            
            names.add(String.format("%s (x: %d, y: %d)", 
                    className, obj.center.x, obj.center.y)); 
        });
        
        return names;
    }

    public int getObjectsCount() {
         return objects.size();
    }
    
    public void onMouseClicked(MouseEvent evt) {
        panelClickHandler.OnClick(evt);
    }
    
    public void moveAllObjects() {
        objects.forEach(obj -> obj.move());
    }
    
    public void save(File file) throws FileNotFoundException, IOException {
        var name = file.getName();
        var stream = new FileOutputStream(file);
        
        if (name.endsWith(".xml")) {
            OutputStreamWriter writer = new OutputStreamWriter(stream);
            XStream xstream = new XStream();
            xstream.registerConverter(new PointConverter());
            
            xstream.alias("Objects.GraphicObject", GraphicObject.class);
            xstream.alias("Objects.Polygon", Polygon.class);
            xstream.alias("Objects.Image", Image.class);

            xstream.toXML(objects, writer);           
            return;       
        }        
   
        var objStream = new ObjectOutputStream(stream);
        
        objStream.writeInt(objects.size());
        for (GraphicObject obj: objects)
            objStream.writeObject(obj);
    }
    
    public void open(File file) throws FileNotFoundException, IOException, ClassNotFoundException {
        var name = file.getName();
        var stream = new FileInputStream(file);

        objects.clear();
        
        if (name.endsWith(".xml")) {
            BufferedReader reader = new BufferedReader(new InputStreamReader(stream));
            
            XStream xstream = new XStream();
            xstream.registerConverter(new PointConverter());
            
            xstream.alias("Objects.GraphicObject", GraphicObject.class);
            xstream.alias("Objects.Polygon", Polygon.class);
            xstream.alias("Objects.Image", Image.class);
            
            xstream.allowTypes(new Class[] { Polygon.class, Image.class, 
                GraphicObject.class });
            
            objects = (java.util.List)xstream.fromXML(reader);
            return;
        }
        
        var objStream = new ObjectInputStream(stream);
        
        int size = objStream.readInt();
        for (int i = 0; i < size; i++)
            objects.add((GraphicObject)objStream.readObject());
    }
    
    private void switchEditMode(EditMode newMode) {
          
        drawBorderRects = false;
        
        switch (newMode) {
            case Add:
                panelClickHandler = (e) -> spawnRandomObject(e.getPoint());
                break;
            case Delete:
                drawBorderRects = true;
                panelClickHandler = (e) -> getPickedObject(e.getPoint()).
                        ifPresent(obj -> objects.remove(obj)); 
                break;
            case Resume:
                drawBorderRects = true;
                panelClickHandler = (e) -> getPickedObject(e.getPoint()).
                        ifPresent(obj -> obj.canMove = true); 
                break;
            case Stop:
                drawBorderRects = true;
                panelClickHandler = (e) -> getPickedObject(e.getPoint()).
                        ifPresent(obj -> obj.canMove = false);           
                break;
            default:
                panelClickHandler = (e) -> {};
        }
    }
    
    private Optional<GraphicObject> getPickedObject(Point pos) {
        
        return objects.stream().
                filter(obj -> obj.contains(pos.x, pos.y)).
                findFirst();
    }
    
    private void spawnRandomObject(Point pos) {
        GraphicObject obj = null;
        
        var r = new Random();
        if (r.nextInt() % 2 == 0)
            obj = new Polygon(pos.x, pos.y, Color.BLUE, 5, 30);
        else {
            try {
                obj = new Image(pos.x, pos.y, null, "cat.jpg");
            } catch (IOException ex) {
                System.out.println("Error spawn image");
            }
        }
        
        objects.add(obj);  
    }
}
