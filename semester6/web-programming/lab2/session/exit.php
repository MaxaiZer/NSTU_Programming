<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<body>
<div style="text-align:center; margin-top: 150px;">

    <?php
    session_start();
    echo "Session:".session_id();
        session_unset(); 
        session_destroy();
        echo "Session:".session_id();
    ?>

    <a href="login.php"><h1>Вход</h1></a>
    <a href="main_table/index.php"><h1>На главную страницу</h1></a>
    </div>
</body>

</html>