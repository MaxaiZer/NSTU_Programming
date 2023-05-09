package utils;

import java.awt.Color;
import java.lang.reflect.Type;
import com.google.gson.*;

public class ColorJsonConverter implements JsonSerializer<Color>, JsonDeserializer<Color> {

    @Override
    public JsonElement serialize(Color color, Type type, JsonSerializationContext context) {
        JsonObject obj = new JsonObject();
        obj.addProperty("red", color.getRed());
        obj.addProperty("green", color.getGreen());
        obj.addProperty("blue", color.getBlue());
        obj.addProperty("alpha", color.getAlpha());
        return obj;
    }

    @Override
    public Color deserialize(JsonElement json, Type type, JsonDeserializationContext context)
            throws JsonParseException {
        JsonObject obj = json.getAsJsonObject();
        int red = obj.get("red").getAsInt();
        int green = obj.get("green").getAsInt();
        int blue = obj.get("blue").getAsInt();
        int alpha = obj.get("alpha").getAsInt();
        return new Color(red, green, blue, alpha);
    }
}