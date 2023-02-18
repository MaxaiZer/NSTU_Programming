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
        if (!$user->canChangeUsersTable)
            header("Location: ../access_denied.html");

        include_once("../../connect_to_db.php");

        $id = $_GET["id"];

        echo "<form action='update_table.php?id=".$id."' METHOD=POST>";

        include_once("get_table_input_form.php");
        include_once("../authentication.php"); 

        echo "<p><button style='padding: 10px 10px; width: 80px;' type='submit'>Update</button></p>";
        echo "</form>";

        $login = $_POST["login"];
        $password = $_POST["password"];
        $password_again = $_POST["password_again"];

        $isUpdate = !empty($login) && !empty($password) &&
        !empty($password_again) && $password == $password_again;

        if ($isUpdate) {
            if (!updateUser($conn, $id, $login, $password, $_POST["role"]))
                echo "Invalid data";
        }
        ?>

        <a href="index.php"><h1>Назад</h1></a>
    </div>
</body>

</html>