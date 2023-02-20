<!DOCTYPE html>
<html>
<style>
    @import url("../../../css/styles.css");
</style>

<body>
    <div style="text-align:center; margin-top: 150px;">

        <?php

        include_once("../user_info.php");
        $user = getUserInfo();
        if (!$user->canChangeUsersTable) {
            header("Location: ../access_denied.html");
            die();
        }

        include_once("../../connect_to_db.php");

        echo "<form action='insert_into_table.php' METHOD=POST>";

        include_once("get_table_input_form.php");
        include_once("../authentication.php"); 

        echo "<p><button style='padding: 10px 10px; width: 80px;' type='submit'>Insert</button></p>";
        echo "</form>";

        $login = $_POST["login"];
        $password = $_POST["password"];
        $password_again = $_POST["password_again"];

        $isInsert = !empty($login) && !empty($password) &&
        !empty($password_again) && $password == $password_again;

        if ($password != $password_again) echo "Passwords are not equal";

        if ($isInsert)  {
            if (!addUser($conn, $login, $password, $_POST["role"]))
                echo "User with this login already exists";
        }
        ?>

        <a href="index.php"><h1>Назад</h1></a>
    </div>
</body>

</html>