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
        if (!$user->canChangeMainTable)
            header("Location: ../access_denied.html");

        include_once("../../../connect_to_db.php");

        echo "<form action='insert_into_table.php' METHOD=POST>";

        include("get_table_input_form.php");

        echo "<p><button style='padding: 10px 10px; width: 80px;' type='submit'>Insert</button></p>";
        echo "</form>";

        $insert = isset($_POST["number"]) && !empty($_POST["number"]);

        if ($insert) {
            $findOwnerId = "(select id from car_owners where surname = '" . $_POST["surname"] . "')";
            $findBrandId = "(select id from car_brands where name = '" . $_POST["brand"] . "')";

            $format = "insert into cars (owner_id, brand_id, state, license_plate_number) 
            values (%s, %s, '%s', '%s')";

            $query = sprintf($format, $findOwnerId, $findBrandId, $_POST["state"], $_POST["number"]);

            try {
                $conn->query($query);
            } catch (Exception $e) {
                die('Error: ' . $e->getMessage());
            }
        }
        ?>

        <a href="index.php"><h1>Назад</h1></a>
    </div>
</body>

</html>