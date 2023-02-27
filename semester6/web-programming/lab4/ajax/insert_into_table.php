<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<head>
    <script type="text/javascript" src="../js_libs/jquery.min.js"></script>
    <script type="module" src="model_input.js"></script>
</head>

<body>
    <div style="text-align:center; margin-top: 150px;">

        <?php

        include_once("../../connect_to_db.php");

        echo "<form action='insert_into_table.php' METHOD=POST>";

        include("get_table_input_form.php");

        echo "<p><button style='padding: 10px 10px; width: 80px;' type='submit'>Insert</button></p>";
        echo "</form>";

        $insert = !empty($_POST["number"]) && !empty($_POST["brand_id"]) && !empty($_POST["model_id"]);
        if (!$insert) die();

        $format = "insert into cars_v2 (owner_id, model_id, state, license_plate_number) 
        values (%s, %s, '%s', '%s')";

        $query = sprintf($format, $_POST["owner_id"], $_POST["model_id"], $_POST["state"], $_POST["number"]);

        try {
            $conn->query($query);
        } catch (Exception $e) {
            die('Error: ' . $e->getMessage());
        }
        
        ?>

        <a href="index.php"><h1>Назад</h1></a>
    </div>
</body>

</html>