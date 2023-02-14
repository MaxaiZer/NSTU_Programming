<?php

$conn = new mysqli("localhost", "root", "12345");

if (!mysqli_select_db($conn, "testdb")) {
    die('Select table Error');
}

if ($conn->connect_error) {
    die('Connect Error (' . $conn->connect_errno . ') ' . $conn->connect_error);
}

$name = $_POST["name"];
try {

    $stmt = $conn->prepare("SELECT * FROM REGISTRY where name LIKE ?");
    $stmt->execute(array("%$_GET[name]%"));

    $result = $conn->query("SELECT * FROM testtable", MYSQLI_USE_RESULT);
} catch (Exception $e) {
    die('Query error: ' . $e->getMessage());
}

$iter = $result->getIterator();

while ($iter->valid()) {
    $row = $iter->current();
    echo "<p>" . $row["id"] . $row["name"] . "</p>";
    $iter->next();
}
