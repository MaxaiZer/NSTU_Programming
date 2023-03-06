import java.io.File;
import javax.swing.filechooser.FileFilter;

public class CustomFileFilter extends FileFilter {

    @Override
    public boolean accept(File file) {
        if (file.isDirectory()) return true;
                
        String name = file.getName().toLowerCase();
        String[] permitted = {".bin", ".txt", ".xml"};
                
        for (String p: permitted) {
            if (name.endsWith(p)) return true;
        }
                
        return false;
    }

    @Override
    public String getDescription() {
        return "bin, text or xml files";
    }   
    
}
