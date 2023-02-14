<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<body>

    <?php

    $conn = new mysqli("localhost", "root", "12345");

    $db = "stolen_cars";

    if (!mysqli_select_db($conn, $db))
        die('Error select db ' . $db);

    $id = $_GET["id"];
    echo "<form action='update_db.php?id=" . $id . "' METHOD=POST>";

    include('table_form.php');

    echo "<input type='submit' value='Update'></form>";

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
</body>

</html>