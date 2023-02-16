<!DOCTYPE html>
<html>
<style>
    @import url("../css/styles.css");
</style>

<body>
    <div style="text-align:left;">

    <?php
        $fileName = "file.txt";

        if (!file_exists($fileName))
            echo "File doesn't exist";
        if (filesize($fileName) == 0)
            echo "Empty!";
        else
            outputFile($fileName);    

        function outputFile($fileName)
        {
            $fp = fopen($fileName, "r");
     
            if (!$fp)
            {
                echo "Error open ".$fileName."!"; 
                exit;
            }
            
            while(!feof($fp))
            {
                $str = fgets($fp, 100);
                echo "<p>" . $str . "</p>";
            }
    
            fclose($fp);   
        }
    ?>
    </div>
</body>

</html>