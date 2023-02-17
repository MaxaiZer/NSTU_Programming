<?php

include_once("../user_info.php");
$user = getUserInfo();
if (!$user->canChangeUsersTable)
    header("Location: ../access_denied.html");

header("Location: index.php");
include_once("../../connect_to_db.php");

$id = $_GET["id"];

if (!isset($id))
    exit;

try {
    $query = "DELETE FROM users WHERE id=" . $id;
    $result = $conn->query($query, MYSQLI_USE_RESULT);
} catch (Exception $e) {
    die('Error: ' . $e->getMessage());
}
