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
      
        $query = "SELECT cars.id, car_brands.name AS brand, 
        license_plate_number, state, car_owners.surname AS owner_surname
        FROM cars
        INNER JOIN car_brands ON car_brands.id = brand_id
        INNER JOIN car_owners ON car_owners.id = owner_id";

        $brand = $_POST["brand"];
        if (isset($brand) && !empty($brand))
            $query .= " where car_brands.name = '" . $brand . "'";

        $query .= " order by id";
      
        try {  
            $result = $conn->query($query, MYSQLI_USE_RESULT);
        } catch (Exception $e) {
            die('Error: ' . $e->getMessage());
        }
       
        echo "<table style='margin-left: auto; margin-right: auto;'>";

        $rows = $result->fetch_all(MYSQLI_ASSOC);

        $columnNames = array_keys($rows[0]);
        $columnNames[] = "Update";
        $columnNames[] = "Delete";
        echoRow($columnNames, true);

        foreach ($rows as $row) {

            echo "<tr>";       

            echoRow($row, false);

            $id = $row[$columnNames[0]];
            echo "<td><a href=update_db.php?id=".$id.">Update</a></td>";
            echo "<td><a href=delete_from_db.php?id=".$id.">Delete</a></td>";
            echo "</tr>";
        }

        echo "</table>";

        function echoRow(array $row, $isHeaders)
        {
            foreach ($row as $data)
                echo $isHeaders ? "<th>".$data."</th>" : "<td>".$data."</td>";
        }

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

        <form action="insert_into_db.php">
            <p>
                <button style="padding:10px 10px; width:85px">Insert</button>
            </p>
        </form>

        <a href="../index.html"><h1>Назад</h1></a>
    </div>
</body>

</html>