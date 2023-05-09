import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import java.awt.Color;
import java.awt.Point;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import objects.GraphicObject;
import objects.Image;
import objects.Polygon;
import utils.ColorJsonConverter;
//import utils.GraphicObjectSerializer;
import utils.PointJsonConverter;
import utils.RuntimeTypeAdapterFactory;

public class ObjectContainer {
    
    private List<GraphicObject> objects;
    private final Gson gson;

    public ObjectContainer() {
        objects = new ArrayList<>();
        
        RuntimeTypeAdapterFactory<GraphicObject> runtimeTypeAdapterFactory
                = RuntimeTypeAdapterFactory
                .of(GraphicObject.class, "type")
                .registerSubtype(Image.class, "image")
                .registerSubtype(Polygon.class, "polygon");
        
        gson = new GsonBuilder()
        .setLenient()
        .registerTypeAdapterFactory(runtimeTypeAdapterFactory)  
        .registerTypeAdapter(Point.class, new PointJsonConverter())
        .registerTypeAdapter(Color.class, new ColorJsonConverter())
        .create();
    }
    
    public Gson getGson() {
        return gson;
    }
    
    public void restoreFromFile(String name) throws FileNotFoundException, IOException {
        try (FileReader reader = new FileReader(name)) {
            BufferedReader bufferedReader = new BufferedReader(reader);
            StringBuilder stringBuilder = new StringBuilder();
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                stringBuilder.append(line);
            }
            String json = stringBuilder.toString();          
            objects = gson.fromJson(json, new TypeToken<List<GraphicObject>>(){}.getType());
        }
    }
    
    public void saveToFile(String name) throws IOException {
        try (FileWriter writer = new FileWriter(name)) {
            writer.write(getObjectsAsJson());
        }     
      
    }

    public void addObject(GraphicObject object) {
        objects.add(object);
    }

    public List<String> getObjectNames() {
        List<String> names = new ArrayList<>();
        for (GraphicObject obj : objects) {
            
            String className = obj instanceof objects.Image ? "Image" : "Polygon";
            String name = String.format("%s (x: %d, y: %d)", 
                    className, obj.center.x, obj.center.y);
            
            names.add(name);
        }
        return names;
    }

    public Optional<GraphicObject> getObjectByIndex(int index) {
        GraphicObject obj = null;
        
        try { obj = objects.get(index); } 
        catch (IndexOutOfBoundsException ex) { }
        
        return Optional.ofNullable(obj);
    }

    public boolean removeObjectByIndex(int index) {
        
        if (0 <= index && index < objects.size()) {
            objects.remove(index);
            return true;
        }
        
        return false;
    }

    public String getObjectsAsJson() {
        Type listType = new TypeToken<List<GraphicObject>>() {}.getType();
        String json = gson.toJson(objects, listType);
        return json;
    }
}
