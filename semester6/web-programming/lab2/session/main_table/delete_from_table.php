<?php

include_once("../user_info.php");
$user = getUserInfo();
if (!$user->canChangeMainTable) {
    header("Location: ../access_denied.html");
    die();
}

header("Location: index.php");
include_once("../../../connect_to_db.php");

$id = $_GET["id"];

if (!isset($id))
    exit;

try {
    $query = "DELETE FROM cars WHERE id=" . $id;
    $result = $conn->query($query, MYSQLI_USE_RESULT);
} catch (Exception $e) {
    die('Error: ' . $e->getMessage());
}
