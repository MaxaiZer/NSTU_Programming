<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<head>
    <div style="text-align:center;">
        <b>
            <h1>Базa данных об угнанных автомобилях</h1>
        </b>
    </div>
</head>

<body>
    <div style="text-align:center;">
        <?php

        include_once("../../fetch_all.php");
        include_once("../../connect_to_db.php");
        include_once("../../show_db_table.php");

        $query = "SELECT car_brands.name AS brand, count(*) as count
        FROM cars
        INNER JOIN car_brands ON car_brands.id = brand_id
        group by (brand)";

        try {
            $result = $conn->query($query);
        } catch (Exception $e) {
            die('Error: ' . $e->getMessage());
        }

        session_start();
        $_SESSION["diagram_data"] = fetch_all($result, MYSQLI_BOTH);
        $result->data_seek(0);
  
        $style = 'margin-left: auto; margin-right: auto;';
        show_db_table($result, $style, null, null);
      
        ?>
        <img src="diagram.php">
        <a href="../index.html"><h1>Назад</h1></a>
    </div>
</body>

</html>