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

    <p>Запись в файл</p>
    <form action="input_handler.php" METHOD=POST>
        <p><input type="text" name="name" value="" placeholder="Имя"></p>
        <p><textarea name="sites" value="" placeholder="Сайты для управления"></textarea></p>
        <p><button style="padding: 5px 5px;" type="submit">Отправить</button></p>
    </form> 

    <a href="../index.html"><h1>Назад</h1></a>
    </div>
</body>

</html>