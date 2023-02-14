<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<body>
<div style="text-align:center; margin-top: 150px;">

<?php

$conn = new mysqli("localhost", "root", "12345");

$db = "stolen_cars";

if (!mysqli_select_db($conn, $db))
    die('Error select db '.$db);

echo "<form action='insert_into_db.php' METHOD=POST>";

include('table_form.php');

echo "<p><button style='padding: 10px 10px; width: 80px;' type='submit'>Insert</button></p>";
echo "</form>";

$insert = isset($_POST["number"]) && !empty($_POST["number"]);

if ($insert)
{
    $findOwnerId = "(select id from car_owners where surname = '".$_POST["surname"]."')";
    $findBrandId = "(select id from car_brands where name = '".$_POST["brand"]."')";

    $format = "insert into cars (owner_id, brand_id, state, license_plate_number) values (".
    "%s, %s, '%s', '%s')";

    $query = sprintf($format, $findOwnerId, $findBrandId, $_POST["state"], $_POST["number"]);

    try {
        $conn->query($query);
    } catch (Exception $e) {
        die('Error: '.$e->getMessage());
    }
}

?>
    <a href="index.php"><h1>Назад</h1></a>
</div>
</body>

</html>