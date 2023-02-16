<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<body>
<div style="text-align:center; margin-top: 150px;">

    <?php
        session_start();
        $adminAuth = array("login" => "tratata", "password" => "secretpassword");

        $login = $_POST["login"];
        $password = $_POST["password"];

        if (isset($login) && isset($password))
        {
            if ($login == $adminAuth["login"] && $password == $adminAuth["password"])
            {
                $_SESSION["isAdmin"] = true;
                header("Location: index.php");
            }
        }

    ?>

    <p><h1>Вход</h1></p>
    <form action="auth.php" METHOD=POST>
        <p><input type="text" name="login" value="" placeholder="Логин"></p>
        <p><input type="password" name="password" value="" placeholder="Пароль"></p>
        <p><button style="padding: 8px 14px;" type="submit">Войти</button></p>
    </form> 

    <a href="index.php"><h1>Назад</h1></a>
    </div>
</body>

</html>