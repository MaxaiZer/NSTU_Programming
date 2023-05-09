import com.google.gson.Gson;
import com.google.gson.JsonParseException;
import java.io.IOException;
import objects.GraphicObject;
import java.util.OptionalInt;
import spark.Spark;

public class Server {

    private ObjectContainer container = new ObjectContainer();
    private final String backupFile = "./resources/backup.json";
    private final Gson gson;
    
    public Server() throws IOException {
        
        gson = container.getGson();      
        container.restoreFromFile(backupFile);
        
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            try {
                container.saveToFile(backupFile);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }));
    }
    
    public void start() {
        Spark.port(4567);
        
        Spark.get("/objects/get", (req, res) -> container.getObjectsAsJson());
        Spark.get("/objects/names", (req, res) -> gson.toJson(container.getObjectNames()));
        Spark.get("/object/get", (req, res) -> { 
            
            OptionalInt index = stringToInt(req.queryParams("id"));
            if (index.isEmpty()) {
                 res.status(400);
                 return "Invalid id value";
            }

            var obj = container.getObjectByIndex(index.getAsInt());
          
            if (obj.isPresent()) { //костыль!!! почему то для одного объекта не добавляет type
                var container = new ObjectContainer();
                container.addObject(obj.get());
                String str = container.getObjectsAsJson();
                str = str.substring( 1, str.length() - 1);
                System.out.println("Sent object: " + str);
                return str;
             //   return gson.toJson(obj.get());
            }
            res.status(404);
            return "Object not found";
        });
        Spark.delete("/object/remove", (req, res) -> {
            OptionalInt index = stringToInt(req.queryParams("id"));
            if (index.isEmpty()) {
                 res.status(400);
                 return "Invalid id value";
            }
            
            boolean success = container.removeObjectByIndex(index.getAsInt());
            if (success) return "";
            
            res.status(404);
            return "Object not found";
        });
        Spark.post("object/add", (req, res) -> { 
            
            GraphicObject obj = null;
            
            System.out.println("Received object: " + req.body());

            try {
                obj = gson.fromJson(req.body(), GraphicObject.class);
            } catch (JsonParseException ex) {
                res.status(400);
                return "Error in serialization object";
            }
 
            container.addObject(obj);
            return "";
        });
    }

    private OptionalInt stringToInt(String str) {
        try {
            return OptionalInt.of(Integer.parseInt(str));
        } catch (NumberFormatException ex) {
            return OptionalInt.empty();
        }
    }
}