<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<body>
<div style="text-align:center; margin-top: 150px;">
    <?php

    include_once "../../connect_to_db.php";

    $id = $_GET["id"];
    echo "<form action='update_db.php?id=" . $id . "' METHOD=POST>";

    include("get_db_input_form.php");

    echo "<p><button style='padding: 10px 10px; width: 80px;' type='submit'>Update</button></p>";
    echo "</form>";

    $update = isset($_POST["number"]) && !empty($_POST["number"]);

    if ($update) {
        $findOwnerId = "(select id from car_owners where surname = '" . $_POST["surname"] . "')";
        $findBrandId = "(select id from car_brands where name = '" . $_POST["brand"] . "')";
        $query = "update cars set owner_id = " . $findOwnerId . ", " .
            "brand_id = " . $findBrandId . ", " .
            "state = '" . $_POST["state"] . "', " .
            "license_plate_number = '" . $_POST["number"] . "' " .
            "where id=" . $id;

        try {
            $conn->query($query);
        } catch (Exception $e) {
            die('Error: ' . $e->getMessage());
        }

        header("Location: index.php");
    }
    ?>
    
    <a href="index.php"><h1>Назад</h1></a>
    </div>
</body>

</html>