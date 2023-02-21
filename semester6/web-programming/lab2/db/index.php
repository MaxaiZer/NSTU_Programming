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
    
        include_once("../../connect_to_db.php");
        include_once("../../show_db_table.php");
      
        $query = "SELECT cars.id, car_brands.name AS brand, 
        license_plate_number, state, car_owners.surname AS owner_surname
        FROM cars
        INNER JOIN car_brands ON car_brands.id = brand_id
        INNER JOIN car_owners ON car_owners.id = owner_id";

        if (isset($_POST["brand"])) {
            if (!empty($_POST["brand"])) {
                $query .= " where car_brands.name = '".$_POST["brand"]."'";
            }
        }

        $query .= " order by id";
      
        try {  
            $result = $conn->query($query, MYSQLI_USE_RESULT);
        } catch (Exception $e) {
            die('Error: ' . $e->getMessage());
        }

        $update = new ColumnInfo("Update", "update_table.php", "update");
        $delete = new ColumnInfo("Delete", "delete_from_table.php", "delete");

        $style = 'margin-left: auto; margin-right: auto;';
        show_db_table($result, $style, $update, $delete);

        ?>
        <form action="index.php" METHOD=POST>
            <p>
                <label>Search by brand</label>
                <input type="text" name="brand" value="">
                <button style="padding:5px 5px;" type="submit">Search</button>
            </p>
        </form>

        <form action="index.php">
            <p>
                <button style="padding:10px 10px;" type="submit">Show all</button>
            </p>
        </form>

        <form action="insert_into_table.php">
            <p>
                <button style="padding:10px 10px; width:85px">Insert</button>
            </p>
        </form>

        <a href="../index.html"><h1>Назад</h1></a>
    </div>
</body>

</html>