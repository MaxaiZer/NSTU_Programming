<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL & ~E_NOTICE);

try {
    $conn = new mysqli("localhost", "user213", "gun_centos_user_213");
} catch (Exception $e) {
    die ($e->getMessage());
}

$db_name = "user213";
mysqli_select_db($conn, $db_name) or die (mysqli_error($conn));