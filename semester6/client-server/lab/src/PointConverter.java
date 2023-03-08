
import com.thoughtworks.xstream.converters.Converter;
import com.thoughtworks.xstream.converters.MarshallingContext;
import com.thoughtworks.xstream.converters.UnmarshallingContext;
import com.thoughtworks.xstream.io.HierarchicalStreamReader;
import com.thoughtworks.xstream.io.HierarchicalStreamWriter;
import java.awt.Point;


public class PointConverter implements Converter {
    
    @Override
    public boolean canConvert(Class _class) {
        return _class.equals(Point.class);
    }

    @Override
    public void marshal(Object o, HierarchicalStreamWriter writer, MarshallingContext mc) {
        Point point = (Point) o;
        writer.startNode("x");
        writer.setValue("" + point.x);
        writer.endNode();
        writer.startNode("y");
        writer.setValue("" + point.y);
        writer.endNode();  
    }

    @Override
    public Object unmarshal(HierarchicalStreamReader reader, UnmarshallingContext uc) {
        Point point = new Point();
        
        reader.moveDown();
        point.x = Integer.valueOf(reader.getValue());
        reader.moveUp();
        
        reader.moveDown();
        point.y = Integer.valueOf(reader.getValue());
        reader.moveUp();
        return point;
    }
}
