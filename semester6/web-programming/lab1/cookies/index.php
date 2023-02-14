<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<body>
    <div style="text-align:center;">
    <?php
     
    if(isset($_COOKIE["email"])) {
        echo "You have cookies!";
        echo "<br> Current cookie: ".$_COOKIE["email"]."</br>";
    }
    else{
        echo "You don't have cookies!";
    }
    ?>

    <form action="input_handler.php" METHOD=POST>
        <p></p>
        <input type="email" name="email" value="" placeholder="Email адрес">
        <p><button style="padding: 5px 5px;" type="submit">Отправить</button></p>
    </form>

    <?php
        echo "<br> File:</br>";
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
            
            echo "<table style='margin-left: auto; margin-right: auto;'>";
            
            while(!feof($fp))
            {
                $str = fgets($fp, 100);
                if (!empty($str))
                    echo "<tr><td>".$str."</tr></td>";
            }
    
            fclose($fp);   
            echo "</table> ";
        }
    ?>

    <form action="input_handler.php" METHOD=POST>
        <p><input type="text" name="name" value="" placeholder="Имя"></p>
        <p><textarea name="sites" value="" placeholder="Сайты для управления"></textarea></p>
        <p><button style="padding: 5px 5px;" type="submit">Отправить</button></p>
    </form> 

    <a href="../index.html"><h1>Назад</h1></a>
    </div>
</body>

</html>