<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<body>
<div style="text-align:center; margin-top: 150px;">

    <?php
        session_start();

        $login = $_POST["login"];
        $password = $_POST["password"];

        $loggedIn = false;

        if (isset($login) && isset($password))
        {
            include_once("../../connect_to_db.php");
            include_once("authentication.php");

            if (!authenticate($conn, $login, $password))
                echo "Failed to login";
            else 
            {
                $loggedIn = true;
                echo "Добро пожаловать, ".$login."!";

                include_once("user_info.php");
                $user = getUserInfo();

                if ($user->canChangeMainTable)
                    echo "<p>Вы можете менять основную таблицу</p>";
                if ($user->canChangeUsersTable)
                    echo "<p>Вы можете менять таблицу пользователей</p>";
            }
        }

        if (!$loggedIn)
            echoInputForm();      

        function echoInputForm()
        {
            echo 
            "
            <p><h1>Вход</h1></p>
            <form action='login.php' METHOD=POST>
                <p><input type='text' name='login' value='' placeholder='Логин'></p>
                <p><input type='password' name='password' value='' placeholder='Пароль'></p>
                <p><button style='padding: 8px 14px;' type='submit'>Войти</button></p>
            </form> 
            ";
        }

    ?>

    <a href="main_table/index.php"><h1>Назад</h1></a>
    </div>
</body>

</html>