<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<?php

try {
    $conn = new mysqli("localhost", "root", "12345");
} catch (Exception $e) {
    die('Connection error: '.$e->getMessage());
}

if (!mysqli_select_db($conn, "testdb"))
    die('Select table Error');

if ($conn->connect_error) 
    die('Connect Error (' . $conn->connect_errno . ') ' . $conn->connect_error);

$result = $conn->query("SELECT * FROM testtable", MYSQLI_USE_RESULT);

$iter = $result->getIterator();

echo "<table>
<tr>
<th>Id</th>
<th>Марка</th>
<th>Номер</th>
<th>Статус</th>
<th>Фамилия владельца</th>
</tr>";

while ($iter->valid()) {
    $row = $iter->current();

    echo"<tr>";

    echo "<td>".$row["id"]."</td>".
    "<td>".$row["brand"]."</td>".
    "<td>".$row["licence_plate_number"]."</td>".
    "<td>".$row["state"]."</td>".
    "<td>".$row["owner"]."</td>";
    $iter->next();

    echo "</tr";
}

echo "</table>";
?>


<body>
    <menu type="toolbar">
    <li>
        <menu label="Файл">
        <button type="button">Новый...</button>
        <button type="button">Открыть...</button>
        <button type="button">Сохранить</button>
        </menu>
    </li>
    <li>
        <menu label="Правка">
        <button type="button">Копировать</button>
        <button type="button">Вырезать</button>
        <button type="button">Вставить</button>
        </menu>
        </li>
    </menu>
    <menu type="context" id="popup-menu">
        <menu_item>Вывести данные</menu_item>
        <menu_item>Добавить данные</menu_item>
        <menu_item>Изменить данные</menu_item>
        <menu_item>Удалить данные</menu_item>
    </menu>
    <form action="db_request_handler.php" METHOD=POST>
        <label>ДБ</label>
        <p><input type="text" name="name" value=""><Br>
        </p>
        <p><input type="submit" value="Отправить"></p>
    </form>
</body>

</html>