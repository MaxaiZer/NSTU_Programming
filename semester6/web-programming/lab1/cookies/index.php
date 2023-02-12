<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<head>
    <p>Отзыв об обучении</p>
</head>

<body>
    <?php
     
    if(isset($_COOKIE["name"])) {
        echo "You have cookies!";
        echo "<br> Current cookie: ".$_COOKIE["name"]."</br>";
        echo "<br> File:</br>";
        readFromFile("form1.txt");
    }

    function readFromFile($fileName)
    {  
        $fp = fopen($fileName, "r");
        if (!$fp)
        {
            echo "Error open ".$fileName."!";
            exit;
        }

        echo "<table>";

        while(!feof($fp))
        {
            echo "<tr><td>";
            $str = fgets($fp, 100);
            echo $str;
            echo "</td></tr>";
        }

        fclose($fp);
        echo "</table> ";
    }

    ?>
    <form action="handler.php" METHOD=POST>
        <label>Имя</label>
        <p><input type="text" name="name" value="" placeholder="Имя"><Br>
            <input type="radio" name="isExpelled" value="true">Отчислиться?<Br>
        </p>
        <p><input type="submit" value="Отправить"></p>
    </form>
</body>

</html>