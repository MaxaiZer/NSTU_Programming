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
    echo "<form action='update_table.php?id=" . $id . "' METHOD=POST>";

    include("get_table_input_form.php");

    echo "<p><button style='padding: 10px 10px; width: 80px;' type='submit'>Update</button></p>";
    echo "</form>";

    $update = isset($_POST["number"]) && !empty($_POST["number"]);

    if ($update) {
        $findOwnerId = "(select id from car_owners where surname = '" . $_POST["surname"] . "')";
        $findBrandId = "(select id from car_brands where name = '" . $_POST["brand"] . "')";

        $format = "update cars set owner_id = %s, brand_id = %s, 
        state = '%s', license_plate_number = '%s' where id = %d";
        $query = sprintf($format, $findOwnerId, $findBrandId, 
        $_POST["state"], $_POST["number"], $id);

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