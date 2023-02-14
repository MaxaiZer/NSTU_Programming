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

        try {
            $conn = new mysqli("localhost", "root", "12345");

            $db = "stolen_cars";

            if (!mysqli_select_db($conn, $db))
                die('Error select db ' . $db);

            $query = "SELECT cars.id, car_brands.name as brand, 
            license_plate_number, state, car_owners.surname as owner_surname
            FROM cars
            inner join car_brands on car_brands.id = brand_id
            inner join car_owners on car_owners.id = owner_id";

            $brand = $_POST["brand"];
            if (isset($brand) && !empty($brand))
                $query .= " where car_brands.name = '" . $brand . "'";

            $query .= " order by id";

            $result = $conn->query($query, MYSQLI_USE_RESULT);
        } catch (Exception $e) {
            die('Error: ' . $e->getMessage());
        }

        $iter = $result->getIterator();

        echo "<table style='margin-left: auto; margin-right: auto;'>
        <tr>
        <th>Id</th>
        <th>Марка</th>
        <th>Номер</th>
        <th>Статус</th>
        <th>Фамилия владельца</th>
        <th>Обновить</th>
        <th>Удалить</th>
        </tr>";

        while ($iter->valid()) {
            $row = $iter->current();

            echo "<tr>";

            $id = $row["id"];

            echo"<td>" . $id . "</td>" .
                "<td>" . $row["brand"] . "</td>" .
                "<td>" . $row["license_plate_number"] . "</td>" .
                "<td>" . $row["state"] . "</td>" .
                "<td>" . $row["owner_surname"] . "</td>" .
                "<td><a href=update_db.php?id=" . $id . ">Update</a></td>" .
                "<td><a href=delete_from_db.php?id=" . $id . ">Delete</a></td>";

            $iter->next();

            echo "</tr>";
        }

        echo "</table>";
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