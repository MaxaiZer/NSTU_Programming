<!DOCTYPE html>
<html>
<style>
    @import url("../../../css/styles.css");
</style>

<head>
    <div style="text-align:center;">
        <b>
            <h1>Пользователи</h1>
        </b>
    </div>
</head>

<body>
    <div style="text-align:center;">
        <?php

        include_once("../user_info.php");

        $user = getUserInfo();
        if (!$user->canChangeUsersTable) {
            header("Location: ../access_denied.html");
            die();
        }

        include_once("../../../connect_to_db.php");
        include_once("../../../show_db_table.php");   
      
        $query = "SELECT id, login, role from users";

        if (!empty($_POST["login"]))
            $query .= " where login = '".$_POST["login"]."'";

        $query .= " order by id";
      
        try {  
            $result = $conn->query($query, MYSQLI_USE_RESULT);
        } catch (Exception $e) {
            die('Error: ' . $e->getMessage());
        }

        $style = 'margin-left: auto; margin-right: auto;';

        $update = new ColumnInfo("Update", "update_table.php", "update");
        $delete = new ColumnInfo("Delete", "delete_from_table.php", "delete");

        $style = 'margin-left: auto; margin-right: auto;';
        show_db_table($result, $style, $update, $delete);

        ?>

        <form action='index.php' METHOD=POST>
        <p>
            <label>Search by login</label>
            <input type='text' name='login' value=''>
            <button style='padding:5px 5px;' type='submit'>Search</button>
        </p>
        </form>

        <form action='index.php'>
        <p>
            <button style='padding:10px 10px;' type='submit'>Show all</button>
        </p>
        </form>  

        <form action='insert_into_table.php'>
        <p>
            <button style='padding:10px 10px; width:85px'>Insert</button>
        </p>
        </form>

        <a href="../exit.php"><h1>Выйти</h1></a>
        <a href="../main_table/index.php"><h1>Назад</h1></a>
    </div>
</body>

</html>