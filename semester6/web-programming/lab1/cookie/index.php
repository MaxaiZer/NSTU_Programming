<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<body>
    <div style="text-align:center; margin-top: 10%;">
    <?php

    if(isset($_COOKIE["email"])) {
        echo "<br>"."Last visit: ".$_COOKIE["date"]."</br>";
        echo "<br> Current cookie: ".$_COOKIE["email"]."</br>";
    }
    else {
        echo "You are new here!";
    }

    ?>

    <form action="set_cookie.php" METHOD=POST>
        <p></p>
        <input type="email" name="email" value="" placeholder="Email адрес">
        <p><button style="padding: 5px 5px;" type="submit">Отправить</button></p>
    </form>

    <a href="../index.html"><h1>Назад</h1></a>
    </div>
</body>

</html>