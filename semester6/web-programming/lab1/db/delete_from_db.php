<?php
header("Location: index.php"); 

$id = $_GET["id"];

if (!isset($id))
    exit;

try {
    $conn = new mysqli("localhost", "root", "12345");

    $db = "stolen_cars";

    if (!mysqli_select_db($conn, $db))
        die('Error select db '.$db);

    $query = "DELETE FROM cars WHERE id=".$id;
    $result = $conn->query($query, MYSQLI_USE_RESULT);
} catch (Exception $e) {
    die('Error: '.$e->getMessage());
}

