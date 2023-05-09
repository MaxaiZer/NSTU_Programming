package utils;

import java.lang.reflect.Type;
import com.google.gson.*;
import java.awt.Point;

public class PointJsonConverter implements JsonSerializer<Point>, JsonDeserializer<Point> {

    @Override
    public JsonElement serialize(Point point, Type type, JsonSerializationContext context) {
        JsonObject obj = new JsonObject();
        obj.addProperty("x", point.x);
        obj.addProperty("y", point.y);
        return obj;
    }

    @Override
    public Point deserialize(JsonElement json, Type type, JsonDeserializationContext context)
            throws JsonParseException {
        JsonObject obj = json.getAsJsonObject();
        int x = obj.get("x").getAsInt();
        int y = obj.get("y").getAsInt();
        return new Point(x, y);
    }
}
